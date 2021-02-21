#ifndef SDFSphere_H
#define SDFSphere_H
#include <string>
#include "SDFObject.hpp"
namespace sdf
{
    class SDFSphere : public SDFObject
    {
    public:
        SDFSphere(float* objectData);
        SDFSphere(float radius);
        virtual float SDF(glm::vec3 p) override;
        ~SDFSphere() {};
        std::vector<float> getFloatData() override;
    private:
        float radius;
    };
}
#endif

