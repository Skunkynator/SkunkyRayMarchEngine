#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLGameCore.hpp"
#include <string>
#include <iostream>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>

namespace gameCore {
    GLFWwindow* mainWindow;
    float yaw = 45, pitch = 35;
    glm::vec3 movementDir = glm::vec3(-1,0,0);
    glm::vec3 position = glm::vec3(0,2,0);
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 forward = glm::vec3(0,0,-1);
    glm::mat4 upDir = glm::mat4(1);
    float deltaTime;
    float time = 0;
    float speed = 1;
    std::unique_ptr<Shader> screenshader;
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void checkInput(GLFWwindow* window);
    void onRender();
    
    void StartGameLoop()
    {
        up = glm::normalize(up);
        std::cout << glm::to_string(glm::normalize(glm::cross(glm::vec3(1),glm::vec3(1)))) << std::endl;
        float Quad[] = {
            -1,-1,
             1,-1,
            -1, 1,
            
             1,-1,
            -1, 1,
             1, 1,
            
        };
        unsigned int VBO,VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(Quad),Quad,GL_STATIC_DRAW);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        glm::mat4 viewDir = glm::mat4(1);
        screenshader = std::unique_ptr<Shader>(new Shader("../Shaders/Default.vs","../Shaders/RayMarch.fs"));
        screenshader->use();
        screenshader->setFloat("fovDist",1);
        screenshader->setFloat("aspectRatio", 4/3.0f);
        while(!glfwWindowShouldClose(mainWindow))
        {
            deltaTime = glfwGetTime() - time;
            time += deltaTime;
            onRender();
            
            viewDir = glm::mat4(1);
            viewDir = glm::rotate(viewDir,glm::radians(yaw),glm::vec3(0,1,0));
            viewDir = glm::rotate(viewDir,glm::radians(pitch),glm::vec3(-1,0,0));
            upDir = glm::inverse(glm::lookAt(glm::vec3(0),forward,up));
            viewDir = upDir * viewDir;
            
            checkInput(mainWindow);
            
            screenshader->setMatrix4fv("camRotation",glm::value_ptr(viewDir));
            screenshader->setVec3("origin",glm::value_ptr(position));
            screenshader->setFloat("time",time);
            //screenshader->setFloat("fovDist",1/speed);
            glDrawArrays(GL_TRIANGLES,0,6);
            std::cout << glm::to_string(position) << std::endl;
            glfwSwapBuffers(mainWindow);
            glfwPollEvents();
        }
    }
    
    void onRender()
    {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        //glClear(GL_DEPTH_BUFFER_BIT);
    }
    
    void checkInput(GLFWwindow* window) {
        if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window,true);
            
        const float cameraSpeed = speed * deltaTime;
        
        glm::vec3 movement = upDir * glm::vec4(movementDir,1);
        //std::cout << glm::to_string(movement) << " : " << glm::to_string(glm::cross(movement,up)) << std::endl;
        
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += cameraSpeed * movement;
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= cameraSpeed * movement;
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position += glm::normalize(glm::cross(movement,up)) * cameraSpeed;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position -= glm::normalize(glm::cross(movement,up)) * cameraSpeed;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * cameraSpeed;
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position -= up * cameraSpeed;
    }


    void SetupWindow(const char* name)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
        glfwWindowHint(GLFW_DECORATED, true);
        //glfwWindowHint(GLFW_CURSOR_HIDDEN,true);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        GLFWwindow* window = glfwCreateWindow(800, 600, name, NULL, NULL);

        if(window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            
            glfwTerminate();
            return;
        }
        
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window,scroll_callback);
        
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "faild to initialize GLAD" << std::endl;
            return;
        }
        mainWindow = window;
    }
    void SetupWindow(std::string name)
    {
        SetupWindow(name.c_str());
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0,0,width,height);
        screenshader->setFloat("aspectRatio",width / (float)height);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        
        int height, width;
        float sensitivity = 0.05f;
        glfwGetWindowSize(window, &width, &height);
        
        xpos -= width / 2;
        ypos -= height / 2;
        xpos *=  sensitivity;
        ypos *= -sensitivity;
        
        yaw += xpos;
        pitch += ypos;
            
        if(pitch > 89.9f)
            pitch = 89.9f;
        if(pitch < -89.9f)
            pitch = -89.9f;
        movementDir = 
        glm::normalize(glm::vec3( 
            sin(glm::radians(yaw)), 0,
            cos(glm::radians(yaw))
        ));
        glfwSetCursorPos(window,width/2,height/2);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        /* 
        float fov = 0;
        fov -= yoffset;
        if(fov < 1)
            fov = 1;
        if(fov > 90)
            fov = 90;
        */
        speed *= yoffset < 0 ? 0.95:1.05;
    }
}
