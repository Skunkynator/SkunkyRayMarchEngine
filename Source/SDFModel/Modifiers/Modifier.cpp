#include "Modifier.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

glm::vec3 readVectorData(float* data,int position)
{
    return glm::vec3(data[position],data[position + 1],data[position + 2]);
}

glm::vec3 readVectorData(std::vector<float> data,int position)
{
    return glm::vec3(data[position],data[position + 1],data[position + 2]);
}

std::vector<float> writeVectorData(std::vector<float> data, glm::vec3 vector, int position)
{
    data[position] = vector.x;
    data[position + 1] = vector.y;
    data[position + 2] = vector.z;
    return data;
}

glm::vec3 sdf::Modifier::vecModifier(glm::vec3 pos)
{
    return pos;
}

float sdf::Modifier::distModifier(float distance)
{
    return distance;
}

std::vector<float> sdf::Modifier::getData()
{
    return std::vector<float>(0);
}
void sdf::Modifier::setData(std::vector<float> modifierData)
{
    
}

sdf::FiniteRepetition::FiniteRepetition(float* data)
{
    density = readVectorData(data,0);
    amount  = readVectorData(data,3);
}
sdf::FiniteRepetition::FiniteRepetition(glm::vec3 density, glm::vec3 amount)
{
    this->density = density;
    this->amount  = amount;
}
void sdf::FiniteRepetition::setData(std::vector<float> modifierData)
{
    density = readVectorData(modifierData,0);
    amount  = readVectorData(modifierData,3);
}
std::vector<float> sdf::FiniteRepetition::getData()
{
    std::vector<float> modifierData(6);
    modifierData = writeVectorData(modifierData, density, 0);
    modifierData = writeVectorData(modifierData, amount , 0);
    return modifierData;
}
glm::vec3 sdf::FiniteRepetition::vecModifier(glm::vec3 pos)
{
    return pos - density * glm::clamp(glm::round(pos/density),-amount,amount);
}

sdf::InfinitRepetition::InfinitRepetition(glm::vec3 density)
{
    this->density = density;
}

sdf::InfinitRepetition::InfinitRepetition(float* data)
{
    density = readVectorData(data, 0);
}

void sdf::InfinitRepetition::setData(std::vector<float> modifierData)
{
    density = readVectorData(modifierData, 0);
}

std::vector<float> sdf::InfinitRepetition::getData()
{
    std::vector<float> data(3);
    return writeVectorData(data,density,0);
}

glm::vec3 sdf::InfinitRepetition::vecModifier(glm::vec3 pos)
{
    return glm::mod(pos + 0.5f * density,density) - 0.5f * density;
}
sdf::Symmetry::Symmetry(sdf::Axes axes)
{
    this->axes = axes;
}

sdf::Symmetry::Symmetry(float* data)
{
    axes = static_cast<Axes>(((int*)data)[0]);
}

void sdf::Symmetry::setData(std::vector<float> modifierData)
{
    axes = static_cast<Axes>(*(int*)&(modifierData[0]));
}

std::vector<float> sdf::Symmetry::getData()
{
    std::vector<float> data(1);
    data[0] = *(int*) &axes;
    return data;
}

glm::vec3 sdf::Symmetry::vecModifier(glm::vec3 pos)
{
    if(axes & Axes::x)
        pos.x = glm::abs(pos.x);
    if(axes & Axes::y)
        pos.y = glm::abs(pos.y);
    if(axes & Axes::z)
        pos.z = glm::abs(pos.z);
    return pos;
}

sdf::UniformScale::UniformScale(float scale)
{
    this->scale = scale;
}

sdf::UniformScale::UniformScale(float* data)
{
    this->scale = data[0];
}

void sdf::UniformScale::setData(std::vector<float> modifierData)
{
    this->scale = modifierData[0];
}

std::vector<float> sdf::UniformScale::getData()
{
    std::vector<float> data(1);
    data[0] = scale;
    return data;
}

glm::vec3 sdf::UniformScale::vecModifier(glm::vec3 pos)
{
    return pos / scale;
}

float sdf::UniformScale::distModifier(float distance)
{
    return distance * scale;
}
