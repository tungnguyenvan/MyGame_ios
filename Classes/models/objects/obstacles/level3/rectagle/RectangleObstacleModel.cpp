#include "RectangleObstacleModel.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"
#include "../../../../../common/Definition.h"

RectangleObstacleModel::RectangleObstacleModel(cocos2d::Scene* scene, std::string name) : CoreModel(name)
{
    Init();
    scene->addChild(mCoreSprite);
}

RectangleObstacleModel::RectangleObstacleModel(cocos2d::Node* node, std::string name) : CoreModel(name)
{
    Init();
    node->addChild(mCoreSprite);
}

RectangleObstacleModel::~RectangleObstacleModel()
{

}

void RectangleObstacleModel::Init()
{
    mCoreSprite = cocos2d::Sprite::create(mModelName);
    mCoreSprite->setTag(OBSTACLES_TAG);

    // Create physics for sprite
    mCorePhysicsBody = cocos2d::PhysicsBody::createBox(GetContentSize());
    if (mCorePhysicsBody != nullptr)
    {
        mCorePhysicsBody->setDynamic(false);
        mCorePhysicsBody->setCollisionBitmask(OBSTACLES_COLLISION_BITMASK);
        mCorePhysicsBody->setContactTestBitmask(true);

        mCoreSprite->addComponent(mCorePhysicsBody);
    }

    mIsRotateToRight = false;
}

void RectangleObstacleModel::Update()
{
    // Rotate sprite
    if (mIsRotateToRight)
    {
        mCoreSprite->setRotation(mCoreSprite->getRotation() + 1);
    } else
    {
        mCoreSprite->setRotation(mCoreSprite->getRotation() - 1);
    }

    // Set rotate to right or to left
    if (mCoreSprite->getRotation() > 45)
    {
        mIsRotateToRight = false;
    } else if (mCoreSprite->getRotation() < -45)
    {
        mIsRotateToRight = true;
    }
}
