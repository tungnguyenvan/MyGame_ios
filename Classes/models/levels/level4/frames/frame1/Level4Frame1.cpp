#include "Level4Frame1.h"
#include "../../../../../common/definitionlevels/DefinitionLevel4.h"

Level4Frame1::Level4Frame1(cocos2d::Scene *scene) : CoreLevelFrame()
{
    // Initialize local variable
    mSpeed = LEVEL_SPEED;
    Init();

    scene->addChild(mGroupNode);
}

Level4Frame1::~Level4Frame1()
{
    // Destructor
}

void Level4Frame1::Init()
{
    // Initialize local variable
    mPosY = 0;
    mIndexRectangleObstacle = 0;

    mGroupNode = cocos2d::Node::create();

    mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));
    mRectangleObstacleModels.at(0)->SetActive(false);

    while (mPosY < cocos2d::Director::getInstance()->getVisibleSize().height)
    {
        RandomRectangle();
    }
}

void Level4Frame1::Update()
{
    mFrameCount++;
    if (mFrameCount >= 200)
    {
        mSpeed += 0.1;
        mFrameCount = 0;
    }

    mGroupNode->setPositionY(mGroupNode->getPositionY() - mSpeed);

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

bool Level4Frame1::HasFinishedMoving()
{
    return mHasFinishMoving;
}

void Level4Frame1::RandomRectangle()
{
    int randCountRec = cocos2d::RandomHelper::random_int(1, 3);
    auto obstacleSize = mRectangleObstacleModels.at(0)->GetContentSize();
    mIndexRectangleObstacle++;
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    mPosY = mPosY + 100 + obstacleSize.height;

    if (randCountRec == 1)
    {
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));

        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
    }else if (randCountRec == 2)
    {
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));

        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2 - obstacleSize.width / 2 - obstacleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
        mIndexRectangleObstacle++;
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2 + obstacleSize.width / 2 + obstacleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
    }else
    {
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mGroupNode, RECTANGLE_NAME_PATH));

        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2 - 90 - obstacleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
        mIndexRectangleObstacle++;
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
        mIndexRectangleObstacle++;
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetPosition(visibleSize.width / 2 + 90 + obstacleSize.width / 2, mPosY);
        mRectangleObstacleModels.at(mIndexRectangleObstacle)->SetActive(true);
    }
}

void Level4Frame1::AliveObstacle(bool alive)
{
    for (int i = 1; i < mRectangleObstacleModels.size(); i++)
    {
        mRectangleObstacleModels.at(i)->SetActive(alive);
    }
}

void Level4Frame1::FadeOutFrame(const float& opacity)
{
    CoreLevelFrame::FadeOutFrame(opacity);

    for (int i = 0; i < mRectangleObstacleModels.size(); i++)
    {
        mRectangleObstacleModels.at(i)->FadeOutModel(opacity);
        mRectangleObstacleModels.at(i)->SetEnablePhysicsBody(false);
    }
}
