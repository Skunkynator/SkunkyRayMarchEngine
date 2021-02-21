#include "SDFSphere.hpp"
#include <glm/glm.hpp>

sdf::SDFSphere::SDFSphere(float radius)
{
    this->radius = radius;
}

float sdf::SDFSphere::SDF(glm::vec3 p)
{
    return glm::length(p) - radius;
}

std::vector< float > sdf::SDFSphere::getFloatData()
{
    std::vector<float> SDFData = std::vector<float>(1);
    SDFData[0] = this->radius;
    return SDFData;
}

sdf::SDFSphere::SDFSphere(float* objectData)
{
    this->radius = objectData[0];
}

