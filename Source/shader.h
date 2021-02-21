#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glm/glm.hpp>
class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float xVal,float yVal,float zVal) const;
    void setVec3(const std::string &name, float* value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setFloatArr(const std::string &name, float* value,float size) const;
    void setMatrix4fv(const std::string &name, float* value) const;
private:
    int uniformLocation(const std::string &name) const;
};
#endif

