#include "Level3Frame2.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"

Level3Frame2::Level3Frame2(cocos2d::Scene *scene)
{
	// Initialize local variable
	mSpeed = LEVEL_SPEED;

    Init();
    scene->addChild(mGroupNode);
}

Level3Frame2::~Level3Frame2()
{
    // Destructor
}

void Level3Frame2::Init()
{
    mGroupNode = cocos2d::Node::create();
    mGroupNode->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    mGroupNode->setPositionY(cocos2d::Director::getInstance()->getVisibleSize().height);

    mCircleLineModel = new CircleLineModel(mGroupNode, CIRCLE_LINE_NAME_PATH, CircleLineModel::OBSTACLE);
    mCircleLineModel->SetPosition(mGroupNode->getContentSize().width / 2, mGroupNode->getContentSize().height * 0.4);

	// Init horizontal line //
	int rand = cocos2d::RandomHelper::random_int(0, 10);
	if (rand % 2 == 0)
	{
		mHorizontalLine = new HorizontalLine(mGroupNode, HorizontalLine::MODE_TRIANGULAR);
		mHorizontal = new HorizontalLine(mGroupNode, HorizontalLine::MODE_CIRCLE);
	}
	else if (rand % 2 != 0)
	{
		mHorizontalLine = new HorizontalLine(mGroupNode, HorizontalLine::MODE_CIRCLE);
		mHorizontal = new HorizontalLine(mGroupNode, HorizontalLine::MODE_TRIANGULAR);
	}
    mHorizontalLine->SetPosition(mGroupNode->getContentSize().width / 2, mGroupNode->getContentSize().height * 0.8);
	mHorizontal->SetPosition(mGroupNode->getContentSize().width / 2, 0);
}

void Level3Frame2::Update()
{
	mFrameCount++;
	if (mFrameCount % 10 == 0)
	{
		mSpeed += 0.2;
		mFrameCount = 0;
	}

	mGroupNode->setPositionY(mGroupNode->getPositionY() - LEVEL_SPEED);

    mCircleLineModel->Update();
    mHorizontalLine->Update();
	mHorizontal->Update();

	if (mGroupNode->getPositionY()  <= - cocos2d::Director::getInstance()->getVisibleSize().height - 100)
	{
		mHasFinishMoving = true;
	}else
	{
		mHasFinishMoving = false;
	}
}

bool Level3Frame2::HasFinishedMoving()
{
    return mHasFinishMoving;
}

void Level3Frame2::FadeOutFrame(const float& opacity)
{
	CoreLevelFrame::FadeOutFrame(opacity);

	mCircleLineModel->FadeOutModel(opacity);
	mHorizontalLine->FadeOutModel(opacity);
	mHorizontal->FadeOutModel(opacity);
}
