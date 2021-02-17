#ifndef SDFObject_H
#define SDFObject_H
#include <string>
#include <glm/vec3.hpp>
#include <vector>
namespace sdf
{
    class SDFObject
    {
    public:
        virtual float SDF(glm::vec3 p) = 0;
        virtual std::vector<float> getFloatData() = 0;
        virtual ~SDFObject() {};
    private:
    };
}
#endif

