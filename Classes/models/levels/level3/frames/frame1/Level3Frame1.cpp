#include "Level3Frame1.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"

Level3Frame1::Level3Frame1(cocos2d::Scene* scene) : CoreLevelFrame()
{
    // Initialize local variable
    mSpeed = LEVEL_SPEED;

    Init();
    scene->addChild(mGroupNode);
}

Level3Frame1::~Level3Frame1()
{

}

void Level3Frame1::Init()
{
    mGroupNode = cocos2d::Node::create();
    mGroupNode->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    mGroupNode->setPositionY(cocos2d::Director::getInstance()->getVisibleSize().height);

    InitHorizontalLines();
}

void Level3Frame1::Update()
{
    mFrameCount++;
    if (mFrameCount % 10 == 0)
    {
        mSpeed += 0.2;
        mFrameCount = 0;
    }

	mGroupNode->setPositionY(mGroupNode->getPositionY() - LEVEL_SPEED);

    for (int i = 0; i < HORIZONTAL_LINE_SIZE; i++)
    {
        mHorizontalLines.at(i)->Update();
    }

    if (mGroupNode->getPositionY()  <= - cocos2d::Director::getInstance()->getVisibleSize().height - 100)
    {
        mHasFinishMoving = true;
    }else
    {
        mHasFinishMoving = false;
    }
}

bool Level3Frame1::HasFinishedMoving()
{
    return mHasFinishMoving;
}

void Level3Frame1::InitHorizontalLines()
{
    for (int i = 0; i < HORIZONTAL_LINE_SIZE; i++)
    {
		int rand = cocos2d::RandomHelper::random_int(0, 10);
		if (rand % 2 == 0)
		{
			mHorizontalLines.push_back(new HorizontalLine(mGroupNode, HorizontalLine::MODE_TRIANGULAR));
		}
		else if (rand % 2 != 0)
		{
			mHorizontalLines.push_back(new HorizontalLine(mGroupNode, HorizontalLine::MODE_CIRCLE));
		}
    }

    // Set position of line //
    int positionY = 64; // position y of horizontal line

    for (int i =0; i < HORIZONTAL_LINE_SIZE; i++)
    {
        mHorizontalLines.at(i)->SetPosition(mGroupNode->getContentSize().width / 2,  positionY);
        positionY += 192;
    }
}

void Level3Frame1::FadeOutFrame(const float& opacity)
{
    CoreLevelFrame::FadeOutFrame(opacity);

    for (int i = 0; i < mHorizontalLines.size(); i ++) {
        mHorizontalLines.at(i)->FadeOutModel(opacity);
    }
}
