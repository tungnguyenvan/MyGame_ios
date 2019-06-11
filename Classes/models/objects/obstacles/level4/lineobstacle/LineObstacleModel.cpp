#include "LineObstacleModel.h"
#include "../../../../../common/definitionlevels/DefinitionLevel4.h"
#include "../../../../../utils/physics/CustomPhysicsBody.h"
#include "../../../../../common/Definition.h"

LineObstacleModel::LineObstacleModel(cocos2d::Scene *scene) : CoreModel(LINE_OBSTACLE_NAME_PATH)
{
    mIsRun = false;
    Init();

    scene->addChild(mCoreSprite);
}

LineObstacleModel::LineObstacleModel(cocos2d::Node *node) : CoreModel(LINE_OBSTACLE_NAME_PATH)
{
    mIsRun = false;
    Init();

    node->addChild(mCoreSprite);
}

LineObstacleModel::~LineObstacleModel()
{
    // Destructor
}

void LineObstacleModel::Init()
{
    // Initialize mCoreSprite
    mCoreSprite = cocos2d::Sprite::create(mModelName);
    mCoreSprite->setTag(OBSTACLES_TAG);
    mCoreSprite->setPositionX(cocos2d::Director::getInstance()->getVisibleSize().width / 2);

    CustomPhysicsBody::getInstance()->parseJsonFile(OBSTACLE_PHYSICS_NAME_PATH);
    mCorePhysicsBody = CustomPhysicsBody::getInstance()->bodyFormJson(mCoreSprite, LINE_OBSTACLE_NAME_PHYSICS,
            cocos2d::PhysicsMaterial(1, 1, 0));

    if (mCorePhysicsBody != nullptr)
    {
        mCorePhysicsBody->setDynamic(false);
        mCorePhysicsBody->setContactTestBitmask(OBSTACLES_COLLISION_BITMASK);
        mCorePhysicsBody->setContactTestBitmask(true);

        mCoreSprite->addComponent(mCorePhysicsBody);
    }
}

void LineObstacleModel::Update()
{
    // Update function
}

void LineObstacleModel::Rotate()
{
    float rotate = cocos2d::RandomHelper::random_int(25, 35);
    int randLeftRight = cocos2d::RandomHelper::random_int(1, 20);

    if (randLeftRight % 2 == 0)
    {
        mCoreSprite->setRotation(rotate);
    } else
    {
        mCoreSprite->setRotation(-rotate);
    }
}

float LineObstacleModel::GetRotate()
{
    return mCoreSprite->getRotation();
}
