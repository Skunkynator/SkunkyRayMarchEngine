#include "SDFModel.hpp"
#include "Primitives/SDFSphere.hpp"
#include "Primitives/SDFBox.hpp"
#include <string>
#include <fstream>
#include <iostream>

std::shared_ptr<sdf::SDFObject> createSDFObject(int ID, float * objectData);

void sdf::SDFModel::sendDataToShader(Shader shader)
{
}


float readFloat(std::ifstream * istream)
{
    float value;
    (*istream).read(reinterpret_cast<char*>(&value),sizeof(float));
    return value;
}

int readInt(std::ifstream * istream)
{
    int value;
    (*istream).read(reinterpret_cast<char*>(&value),sizeof(int));
    return value;
}

glm::vec3 readVec3(std::ifstream * istream)
{
    return glm::vec3(readFloat(istream), readFloat(istream), readFloat(istream));
}

sdf::SDFModel::SDFModel(const char* sdfPath)
{
    try
    {
        int fileVersion;
        int objectDataBytes;
        int effectDataBytes;
        std::ifstream istream(sdfPath, std::ios::binary);
        fileVersion = readInt(&istream);
        if(fileVersion != 1)
            throw std::exception();
        objectDataBytes = readInt(&istream);
        effectDataBytes = readInt(&istream);
        this->readObjects   (&istream);
        this->readModifiers (&istream);
        this->readTransforms(&istream);
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "SDF FILE NOT SUCCESFULLY READ" << std::endl << e.what() << std::endl;
    }
    catch(std::exception e)
    {
        std::cout << "File Version Incorrect" << std::endl;
    }
}

void sdf::SDFModel::readObjects(std::ifstream* istream)
{
    this->objects.resize(0);
    this->objects.reserve(400);
    int objectAmount = readInt(istream);
    int objectType;
    int objectSize;
    float* objectData;
    for(int count = 0; count < objectAmount; count++)
    {
        objectType = readInt(istream);
        objectSize = readInt(istream);
        objectData = new float [objectSize];
        for(int dataIndex = 0; dataIndex < objectSize; dataIndex++)
        {
            objectData[dataIndex] = readFloat(istream);
        }
        this->objects.push_back(createSDFObject(objectType,objectData));
        delete objectData;
    }
}

std::shared_ptr<sdf::SDFObject> createSDFObject(int ID, float * objectData)
{
    std::shared_ptr<sdf::SDFObject> returnObject;
    switch(ID)
    {
        case 0: //Sphere
            returnObject = std::shared_ptr<sdf::SDFObject>(new sdf::SDFSphere(objectData));
            break;
        case 1: //Box
            returnObject = std::shared_ptr<sdf::SDFObject>(new sdf::SDFSphere(objectData));
            break;
    }
    return returnObject;
}

void sdf::SDFModel::readModifiers(std::ifstream* istream)
{
    this->modifiers.resize(0);
    this->modifiers.reserve(400);
    int modifierAmount = readInt(istream);
    int modifierType;
    int modifierSize;
    float* modifierData;
    for(int count = 0; count < modifierAmount; count++)
    {
        modifierType = readInt(istream);
        modifierSize = readInt(istream);
        modifierData = new float [modifierSize];
        for(int dataIndex = 0; dataIndex < modifierSize; dataIndex++)
        {
            modifierData[dataIndex] = readFloat(istream);
        }
        this->modifiers.push_back(sdf::Modifier::createModifier(modifierType,modifierData));
        delete modifierData;
    }
}

void sdf::SDFModel::readTransforms(std::ifstream* istream)
{
    this->transforms.resize(0);
    this->transforms.reserve(400);
    int transformAmount = readInt(istream);
    glm::vec3 pos;
    glm::vec3 rotation;
    int parentID;
    int effectID;
    int objectID;
    int boundID;
    int connectionType;
    float smoothness;
    for(int count = 0; count < transformAmount; count++)
    {
        std::shared_ptr<sdf::Transform> parent;
        std::shared_ptr<sdf::Modifier> effect;
        std::shared_ptr<sdf::SDFObject> object;
        std::shared_ptr<sdf::SDFObject> bound;
        pos = readVec3(istream);
        rotation = readVec3(istream);
        parentID = readInt(istream);
        effectID = readInt(istream);
        objectID = readInt(istream);
        boundID = readInt(istream);
        connectionType = readInt(istream);
        smoothness = readFloat(istream);
        if(parentID >= 0 || parentID < this->transforms.size())
            parent = this->transforms[parentID];
        if(effectID >= 0 || effectID < this->modifiers.size())
            effect = this->modifiers[effectID];
        if(objectID >= 0 || objectID < this->objects.size())
            object = this->objects[objectID];
        if(boundID >= 0 || boundID < this->objects.size())
            bound = this->objects[boundID];
        this->transforms.push_back(std::make_shared<sdf::Transform>(
            object,pos,rotation,connectionType,parent,bound,smoothness));
    }
}
