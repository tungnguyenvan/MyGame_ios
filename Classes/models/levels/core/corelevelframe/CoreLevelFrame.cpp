#include "CoreLevelFrame.h"

CoreLevelFrame::CoreLevelFrame()
{
	mFrameCount = 0;
	mIsBelowCenter = false;
	mHasFinishMoving = false;
}

CoreLevelFrame::~CoreLevelFrame()
{
	// Destructor
}

void CoreLevelFrame::Update()
{
	if (!HasFinishedMoving())
	{
		mGroupNode->setPosition(mGroupNode->getPosition().x, mGroupNode->getPosition().y - 1);
	}

	if (mGroupNode->getPositionY() < -cocos2d::Director::getInstance()->getVisibleSize().height)
	{
		mHasFinishMoving = true;
	}

	if (mGroupNode->getPositionY() <= cocos2d::Director::getInstance()->getVisibleSize().height / 2)
	{
		mIsBelowCenter = true;
	}
}

bool CoreLevelFrame::IsBelowCenter()
{
	return mIsBelowCenter;
}

void CoreLevelFrame::SetPositionY(float y)
{
    mGroupNode->setPositionY(y);
}

void CoreLevelFrame::FadeOutFrame(const float& opacity)
{
	mGroupNode->setOpacity(mGroupNode->getOpacity() - opacity);
}
