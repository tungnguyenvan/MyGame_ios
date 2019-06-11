#pragma once
 
#include "cocos2d.h"
#include "json/document.h"
 
class MyBodyParser 
{
private:
    MyBodyParser(){}
    rapidjson::Document doc;

public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
	cocos2d::PhysicsBody* bodyFormJson(cocos2d::Node* pNode, const std::string& name, cocos2d::PhysicsMaterial material);
};