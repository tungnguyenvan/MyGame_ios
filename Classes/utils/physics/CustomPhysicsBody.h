#pragma once

#include <string>

#include "cocos2d.h"
#include "json/document.h"

class CustomPhysicsBody
{
private:
    CustomPhysicsBody();
    ~CustomPhysicsBody();
    rapidjson::Document doc;

public:
    static CustomPhysicsBody* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    cocos2d::PhysicsBody* bodyFormJson(cocos2d::Node* pNode, const std::string& name, cocos2d::PhysicsMaterial material);
};
