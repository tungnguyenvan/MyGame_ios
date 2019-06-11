#include "Level4Frame2.h"
#include "../../../../../common/definitionlevels/DefinitionLevel4.h"

Level4Frame2::Level4Frame2(cocos2d::Scene *scene) : CoreLevelFrame()
{
    // Initialize local variable
    mSpeed = LEVEL_SPEED;
    mPositionY = cocos2d::Director::getInstance()->getVisibleSize().height / 3;

    Init();

    scene->addChild(mGroupNode);
}

Level4Frame2::~Level4Frame2()
{
    // Destructor
}

void Level4Frame2::Init()
{
    mGroupNode = cocos2d::Node::create();
    mGroupNode->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    mGroupNode->setAnchorPoint(cocos2d::Vec2(0, 0));

    // Initialize LineObstacle
    mLineObstacleModel = new LineObstacleModel(mGroupNode);
    mLineObstacleModel->Rotate();
    mLineObstacleModel->SetPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
            mLineObstacleModel->GetContentSize().height / 2 + 96);

    // Initialize CircleLineObstacle
    mCircleLineObstacle = new CircleLineObstacle(mGroupNode);
    mCircleLineObstacle->SetPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
            cocos2d::Director::getInstance()->getVisibleSize().height - mCircleLineObstacle->GetContentSize().height / 2 + 64);
}

void Level4Frame2::Update()
{
    mFrameCount++;
    if (mFrameCount >= 200)
    {
        mSpeed += 0.1;
        mFrameCount = 0;
    }

    mCircleLineObstacle->Update();

    mGroupNode->setPositionY(mGroupNode->getPositionY() - mSpeed);

    if (mGroupNode->getPositionY()  <= - cocos2d::Director::getInstance()->getVisibleSize().height - 100)
    {
        mHasFinishMoving = true;
    }else
    {
        mHasFinishMoving = false;
    }

    if (mGroupNode->getPositionY()  <= - cocos2d::Director::getInstance()->getVisibleSize().height - 120)
    {
        mHasFinishMoving = true;
    }else
    {
        mHasFinishMoving = false;
    }

    if (mGroupNode->getPositionY()  > cocos2d::Director::getInstance()->getVisibleSize().height) {
        AliveObstacle(false);
    }
    else
    {
        AliveObstacle(true);
    }
}

bool Level4Frame2::HasFinishedMoving()
{
    return mHasFinishMoving;
}

void Level4Frame2::AliveObstacle(bool alive)
{
    mLineObstacleModel->SetActive(alive);
    mCircleLineObstacle->SetActive(alive);
}

void Level4Frame2::FadeOutFrame(const float& opacity)
{
    CoreLevelFrame::FadeOutFrame(opacity);

    mLineObstacleModel->FadeOutModel(opacity);
    mLineObstacleModel->SetEnablePhysicsBody(false);

    mCircleLineObstacle->FadeOutModel(opacity);
    mCircleLineObstacle->SetEnablePhysicsBody(false);
}
