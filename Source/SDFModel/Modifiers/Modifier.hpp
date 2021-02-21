#ifndef SDFModifiers_H
#define SDFModifiers_H
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace sdf {
    enum ModifierID {
        uniformScale = 0,
        symmetry,
        infinitRepetition,
        finiteRepetition, 
        nonUniformScale = 100, //(performance hit!!!) 
        //unstable:
        twist = 200,
        distortion,
        bend
    };
    enum Axes {
        x = 0b001,
        y = 0b010,
        z = 0b100
    };
    class Modifier {
    public:
        int TypeID = -1;
        virtual float    distModifier(float distance);
        virtual glm::vec3 vecModifier(glm::vec3 pos);
        virtual void setData(std::vector<float> modifierData);
        virtual std::vector<float> getData();
        virtual ~Modifier() {};
        //virtual float*    vecModifier(float*    pos);
        static std::shared_ptr<Modifier> createModifier(int type, float* modifierData);
    };
    class UniformScale : public Modifier {
    public:
        UniformScale(float scale);
        UniformScale(float* data);
        virtual float distModifier(float distance) override;
        virtual glm::vec3 vecModifier(glm::vec3 pos) override;
        virtual std::vector<float> getData() override;
        virtual void setData(std::vector<float> modifierData) override;
    private:
        float scale;
    };
    class Symmetry : public Modifier {
    public:
        Symmetry(Axes axes);
        Symmetry(float* data);
        virtual glm::vec3 vecModifier(glm::vec3 pos) override;
        virtual void setData(std::vector<float> modifierData) override;
        virtual std::vector<float> getData() override;
    private:
        Axes axes;
    };
    class InfinitRepetition : public Modifier {
    public:
        InfinitRepetition(glm::vec3 density);
        InfinitRepetition(float* data);
        virtual glm::vec3 vecModifier(glm::vec3 pos) override;
        virtual void setData(std::vector<float> modifierData) override;
        virtual std::vector<float> getData() override;
    private:
        glm::vec3 density;
    };
    class FiniteRepetition : public Modifier {
    public:
        FiniteRepetition(glm::vec3 density, glm::vec3 amount);
        FiniteRepetition(float* data);
        virtual glm::vec3 vecModifier(glm::vec3 pos) override;
        virtual void setData(std::vector<float> modifierData) override;
        virtual std::vector<float> getData() override;
    private:
        glm::vec3 density;
        glm::vec3 amount;
    };
}

#endif
