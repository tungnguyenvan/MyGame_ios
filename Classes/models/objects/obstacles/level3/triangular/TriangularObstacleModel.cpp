#include "TriangularObstacleModel.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"
#include "../../../../../common/Definition.h"
#include "../../../../../utils/physics/CustomPhysicsBody.h"

const int TriangularObstacleModel::MOVE_VERTICAL = 0;
const int TriangularObstacleModel::MOVE_HORIZONTAL = 1;

TriangularObstacleModel::TriangularObstacleModel(cocos2d::Scene* scene, int move) : CoreModel(TRIANGULAR_NAME_PATH)
{
    mMoveType = move;

    Init();
    scene->addChild(mCoreSprite);
}

TriangularObstacleModel::TriangularObstacleModel(cocos2d::Node* node, int move) : CoreModel(TRIANGULAR_NAME_PATH)
{
    mMoveType = move;

    Init();
    node->addChild(mCoreSprite);
}

TriangularObstacleModel::~TriangularObstacleModel()
{
    // Destructor
}

void TriangularObstacleModel::Init()
{
    mCoreSprite = cocos2d::Sprite::create(mModelName);
    mCoreSprite->setTag(OBSTACLES_TAG);

    // Create physics
	CustomPhysicsBody::getInstance()->parseJsonFile(TRIANGULAR_PHYSICS_JSON);
    mCorePhysicsBody = CustomPhysicsBody::getInstance()->bodyFormJson(mCoreSprite, TRIANGULAR_PHYSICS_NAME,
            cocos2d::PhysicsMaterial(1, 1, 0));
    if (mCorePhysicsBody != nullptr)
    {
        mCorePhysicsBody->setDynamic(false);
        mCorePhysicsBody->setCollisionBitmask(OBSTACLES_COLLISION_BITMASK);
        mCorePhysicsBody->setContactTestBitmask(true);

        mCoreSprite->addComponent(mCorePhysicsBody);
    }

    // create local vatialbe
    mIsGoAhead = true;
    mIsMoveToRight = true;
    mIsRotateHasFinish = true;
    mCountStep = 0;

    if (mMoveType == MOVE_HORIZONTAL)
    {
        mCoreSprite->setRotation(90);
    }
}

void TriangularObstacleModel::Update()
{
    // Move vertical
    if (mMoveType == MOVE_VERTICAL) {
        // Move triangular
        if (mIsGoAhead) {
            mCoreSprite->setPositionY(GetPositionY() + 1);
            mCountStep += 1;
        } else {
            mCoreSprite->setPositionY(GetPositionY() - 1);
            mCountStep -= 1;
        }

        // Check triangular move to ahead
        if (mCountStep >= GetContentSize().height / 2) {
            mIsGoAhead = false;
        } else if (mCountStep <= -GetContentSize().height / 2) {
            mIsGoAhead = true;
        }
    }
    // Move horizontal
    else if (mMoveType == MOVE_HORIZONTAL)
    {
        // Rotate triangular
        RotateTriangularObstacle();

        // Move triangular
        if (mIsMoveToRight)
        {
            mCoreSprite->setPositionX(mCoreSprite->getPositionX() + 1);
        }
        else
        {
            mCoreSprite->setPositionX(mCoreSprite->getPositionX() - 1);
        }

        // Check move triangular
        if (GetPositionX() <= mCoreSprite->getContentSize().width / 2)
        {
            mIsMoveToRight = true;
        }
        else if (GetPositionX() >=  (cocos2d::Director::getInstance()->getVisibleSize().width)
                                    - (mCoreSprite->getContentSize().width / 2))
        {
            mIsMoveToRight = false;
        }
    }
}

void TriangularObstacleModel::RotateTriangularObstacle()
{
    mCoreSprite->setRotation(mCoreSprite->getRotation() + 2);
}
