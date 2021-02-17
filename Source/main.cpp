#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<iostream>
#include<glm/glm.hpp>
#include"GLGameCore.hpp"

void onRender();

int main() {
    gameCore::SetupWindow("Ray March Testing");
    //std::cout << (sdf::Axes::x | sdf::Axes::y | sdf::Axes::z) << std::endl;
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "MAX Vertex attributes" << nrAttributes << std::endl;
        
    gameCore::StartGameLoop();
}
