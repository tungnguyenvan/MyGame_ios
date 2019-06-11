#include "CircleLineObstacle.h"
#include "../../../../../utils/physics/CustomPhysicsBody.h"
#include "../../../../../common/definitionlevels/DefinitionLevel4.h"
#include "../../../../../common/Definition.h"

CircleLineObstacle::CircleLineObstacle(cocos2d::Scene *scene) : CoreModel(CIRCLE_LINE_OBSTACLE_NAME_PATH)
{
    Init();

    scene->addChild(mCoreSprite);
}

CircleLineObstacle::CircleLineObstacle(cocos2d::Node *node) : CoreModel(CIRCLE_LINE_OBSTACLE_NAME_PATH)
{
    Init();

    node->addChild(mCoreSprite);
}

CircleLineObstacle::~CircleLineObstacle()
{
    // Destructor
}

void CircleLineObstacle::Init()
{
    // Initialize sprite
    mCoreSprite = cocos2d::Sprite::create(mModelName);
    mCoreSprite->setTag(OBSTACLES_TAG);

    // Initialize physics
    CustomPhysicsBody::getInstance()->parseJsonFile(OBSTACLE_PHYSICS_NAME_PATH);
    mCorePhysicsBody = CustomPhysicsBody::getInstance()->bodyFormJson(mCoreSprite, CIRCLE_LINE_OBSTACLE_NAME_PHYSICS,
            cocos2d::PhysicsMaterial(1, 1, 0));

    if (mCorePhysicsBody != nullptr)
    {
        mCorePhysicsBody->setDynamic(false);
        mCorePhysicsBody->setCollisionBitmask(OBSTACLES_COLLISION_BITMASK);
        mCorePhysicsBody->setContactTestBitmask(true);

        mCoreSprite->addComponent(mCorePhysicsBody);
    }
}

void CircleLineObstacle::Update()
{
    mCoreSprite->setRotation(mCoreSprite->getRotation() - 0.4);
}
