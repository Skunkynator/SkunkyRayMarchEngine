#include "shader.h"
#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <unistd.h>

bool checkShader(int shader);
void checkProgram(int program);
std::stringstream PreProcessShader(std::stringstream& shaderCode);
std::string readShader(const char* filePath);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vCode = readShader(vertexPath);
    const char* vShaderCode = vCode.c_str();
    std::string fCode = readShader(fragmentPath);
    const char* fShaderCode = fCode.c_str();

    //Compile Shaders
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    if(!checkShader(vertex))
        std::cout << vCode << std::endl;

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    if(!checkShader(fragment))
        std::cout << fCode << std::endl;

    //Shader Program
    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);

    checkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),(int)value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::setMatrix4fv(const std::string &name, float* value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE,value);
}
void Shader::setVec3(const std::string& name, float xVal, float yVal, float zVal) const
{
    glUniform3f(uniformLocation(name),xVal,yVal,zVal);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
    setVec3(name,glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float* value) const
{
    glUniform3fv(uniformLocation(name),1,value);
}

void Shader::setFloatArr(const std::string& name, float* value, float size) const
{
    glUniform1fv(uniformLocation(name),size,value);
}


int Shader::uniformLocation(const std::string& name) const
{
    return glGetUniformLocation(ID, name.c_str());
}


bool checkShader(int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout << "ERROR SHADER COMPILATEION FAILED\n" << infoLog << std::endl;
    }
    return success;
}

void checkProgram(int program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program,512,NULL,infoLog);
        std::cout << "ERROR Program LINKING FAILED\n" << infoLog << std::endl;
    }
}

std::string readShader(const char* filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::cout << filePath << std::endl;
    try
    {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        // read file content into streams
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        // PreProcessIncludes
        shaderStream = PreProcessShader(shaderStream);
        // convert into string
        shaderCode   = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR SHADER FILE NOT SUCCESFULLY READ" << std::endl << e.what() << std::endl;
    }
    
    return shaderCode;
}

std::stringstream PreProcessShader(std::stringstream& shaderCode)
{
    std::stringstream out;
    std::string line;
    std::string pragma("#pragma include");
    
    while (std::getline(shaderCode, line))
    {
        if (size_t pos = line.find(pragma) != std::string::npos)
        {
            std::string include = line.substr(pos+pragma.size()+1, pos+line.size() - pragma.size()-4);
            std::cout << include << std::endl;
            out << readShader(("../Shaders/"+include).c_str()) << std::endl;
        }
        else
            out << line <<std:: endl;
    }
    return out;
}
