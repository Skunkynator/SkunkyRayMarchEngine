#ifndef SDFTransform_H
#define SDFTransform_H
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include "Primitives/SDFObject.hpp"

namespace sdf {
    class Transform {
        enum ConnectionType {
            intersection = 1,
            subtract = 2,
            smooth = 4
        };
    public:
        Transform(std::shared_ptr<SDFObject> object, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot,
                  ConnectionType type, std::shared_ptr<Transform> parent, std::shared_ptr<SDFObject> bounding, float smooth);
        float distance(float xPos, float yPos, float zPos);
        float distance(glm::vec3);
    private:
        int ID;
        glm::vec3 position = glm::vec3(0.0);
        glm::quat rotation = glm::identity<glm::quat>();
        std::shared_ptr<Transform> parent = NULL;
        std::vector<std::shared_ptr<Transform>> children = std::vector<std::shared_ptr<Transform>>(0);
        std::shared_ptr<SDFObject> obj = NULL;
        std::shared_ptr<SDFObject> bounding = NULL;
        ConnectionType connectType;
        float smoothness;
    };
}

#endif
