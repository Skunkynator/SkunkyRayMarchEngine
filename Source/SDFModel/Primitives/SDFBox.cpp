#include "SDFBox.hpp"
#include <glm/glm.hpp>
glm::vec3 readVectorData(float* data,int position)
{
    return glm::vec3(data[position],data[position + 1],data[position + 2]);
}
sdf::SDFBox::SDFBox(int sizeX, int sizeY, int sizeZ)
{
    this->size = glm::vec3(sizeX,sizeY,sizeZ);
}

sdf::SDFBox::SDFBox(glm::vec3 size)
{
    this->size = size;
}

std::vector<float> sdf::SDFBox::getFloatData()
{
    std::vector<float> SDFData = std::vector<float>(3);
    SDFData[0] = this->size.x;
    SDFData[1] = this->size.y;
    SDFData[2] = this->size.z;
    return SDFData;
}


float sdf::SDFBox::SDF(glm::vec3 p)
{
    p = glm::abs(p) - size;
    return length(glm::max(p,glm::vec3(0))) + glm::min(glm::max(p.x,glm::max(p.y,p.z)),0.0f);
}

sdf::SDFBox::SDFBox(float* objectData)
{
    this->size = readVectorData(objectData,0);
}
