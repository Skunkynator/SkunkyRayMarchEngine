#include "Modifier.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


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
