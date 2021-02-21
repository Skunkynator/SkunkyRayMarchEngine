#ifndef SDFBox_H
#define SDFBox_H
#include <string>
#include "SDFObject.hpp"
namespace sdf
{
    class SDFBox : public SDFObject
    {
    public:
        SDFBox(float* objectData);
        virtual float SDF(glm::vec3 p) override;
        
        SDFBox(glm::vec3 size);
        SDFBox(int sizeX, int sizeY, int sizeZ);
        std::vector<float> getFloatData() override;
        ~SDFBox() {};
    private:
        glm::vec3 size;
    };
}
#endif

