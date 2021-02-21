#ifndef SDFMODEL_H
#define SDFMODEL_H
#include <string>
#include "Primitives/SDFObject.hpp"
#include "Modifiers/Modifier.hpp"
#include "SDFTransform.hpp"
#include <vector>
namespace sdf
{
    class SDFModel
    {
    public:
        unsigned int ID;
        SDFModel(const char* sdfPath);
        void safeAsFile(const char* sdfPath);
    private:
        std::vector<std::shared_ptr<SDFObject>> objects;
        std::vector<std::shared_ptr<Modifier>>  modifiers;
        std::vector<std::shared_ptr<Transform>> transforms;
        void readObjects   (std::ifstream* istream);
        void readModifiers (std::ifstream* istream);
        void readTransforms(std::ifstream* istream);
    };
}
#endif

