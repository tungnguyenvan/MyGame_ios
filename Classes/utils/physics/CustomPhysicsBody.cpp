#include "CustomPhysicsBody.h"

CustomPhysicsBody::CustomPhysicsBody()
{
    // Constructor
}

CustomPhysicsBody::~CustomPhysicsBody()
{
    // Destructor
}

CustomPhysicsBody* CustomPhysicsBody::getInstance()
{
    static CustomPhysicsBody* sg_ptr = nullptr;
    if (nullptr == sg_ptr)
    {
        sg_ptr = new CustomPhysicsBody();
    }
    return sg_ptr;
}

bool CustomPhysicsBody::parse(unsigned char *buffer, long length)
{
    bool result = false;
    std::string js((const char*)buffer, length);
    doc.Parse<0>(js.c_str());
    if(!doc.HasParseError())
    {
        result = true;
    }
    return result;
}

void CustomPhysicsBody::clearCache()
{
    doc.SetNull();
}

bool CustomPhysicsBody::parseJsonFile(const std::string& pFile)
{
    auto content = cocos2d::FileUtils::getInstance()->getDataFromFile(pFile);
    bool result = parse(content.getBytes(), content.getSize());
    return result;
}

cocos2d::PhysicsBody* CustomPhysicsBody::bodyFormJson(cocos2d::Node *pNode, const std::string& name, cocos2d::PhysicsMaterial material)
{
    cocos2d::PhysicsBody* body = nullptr;
    rapidjson::Value &bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {
        for (int i=0; i<bodies.Size(); ++i)
        {
            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    body = cocos2d::PhysicsBody::create();
                    float width = pNode->getContentSize().width;
                    float offx = - pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = - pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    cocos2d::Point origin( bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];
                    for (int i = 0; i<polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        cocos2d::Point* points = new cocos2d::Point[pcount];
                        for (int pi = 0; pi<pcount; ++pi)
                        {
                            points[pi].x = offx + width * polygons[i][pcount-1-pi]["x"].GetDouble();
                            points[pi].y = offy + width * polygons[i][pcount-1-pi]["y"].GetDouble();
                        }
                        body->addShape(cocos2d::PhysicsShapePolygon::create(points, pcount, material));
                        delete [] points;
                    }
                }
                else
                {
                    CCLOG("body: %s not found!", name.c_str());
                }
                break;
            }
        }
    }
    return body;
}