#ifndef SDFSphere_H
#define SDFSphere_H
#include <string>
#include "SDFObject.hpp"
namespace sdf
{
    class SDFSphere : public SDFObject
    {
    public:
        virtual float SDF(glm::vec3 p) override;
        ~SDFSphere() {};
        SDFSphere(float radius);
        std::vector<float> getFloatData() override;
    private:
        float radius;
    };
}
#endif

