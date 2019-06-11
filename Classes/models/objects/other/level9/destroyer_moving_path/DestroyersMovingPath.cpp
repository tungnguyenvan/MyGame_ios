#include "DestroyersMovingPath.h" 
#include "../../../../../common/definitionlevels/DefinitionLevel9.h"

DestroyersMovingPath::DestroyersMovingPath(cocos2d::Scene* scene)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The moving path sprites on the left //
	mLeftMovingPath1Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_path.png");
	mLeftMovingPath1Sprite->setPosition(origin.x + mLeftMovingPath1Sprite->getContentSize().width / 2,
		origin.y + visibleSize.height / 2);
	scene->addChild(mLeftMovingPath1Sprite, 1);

	mLeftMovingPath2Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_path.png");
	mLeftMovingPath2Sprite->setPosition(origin.x + mLeftMovingPath2Sprite->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + visibleSize.height);
	scene->addChild(mLeftMovingPath2Sprite, 1);

	// The moving path sprites on the center //
	mCenterMovingPath1Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_background.png");
	mCenterMovingPath1Sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	scene->addChild(mCenterMovingPath1Sprite, 0);

	mCenterMovingPath2Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_background.png");
	mCenterMovingPath2Sprite->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + visibleSize.height);
	scene->addChild(mCenterMovingPath2Sprite, 0);

	// The moving path sprites on the right //
	mRightMovingPath1Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_path.png");
	mRightMovingPath1Sprite->setPosition(visibleSize.width - mRightMovingPath1Sprite->getContentSize().width / 2,
		origin.y + visibleSize.height / 2);
	scene->addChild(mRightMovingPath1Sprite, 1);

	mRightMovingPath2Sprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroyer_moving_path.png");
	mRightMovingPath2Sprite->setPosition(visibleSize.width - mRightMovingPath2Sprite->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + visibleSize.height);
	scene->addChild(mRightMovingPath2Sprite, 1);

	// Create a sliding action and make the paths to move downwards //
	auto slidingAction = cocos2d::RepeatForever::create(
		cocos2d::MoveBy::create(DESTROYERS_MOVING_PATH_SLIDING_TIME_DURATION,
			cocos2d::Vec2(0, -visibleSize.height)));

	// Apply the action for all of the sprites //
	mLeftMovingPath1Sprite->runAction(slidingAction);
	mLeftMovingPath2Sprite->runAction(slidingAction->clone());
	mCenterMovingPath1Sprite->runAction(slidingAction->clone());
	mCenterMovingPath2Sprite->runAction(slidingAction->clone());
	mRightMovingPath1Sprite->runAction(slidingAction->clone());
	mRightMovingPath2Sprite->runAction(slidingAction->clone());
}

cocos2d::Vec2 DestroyersMovingPath::GetThePosition(const bool& isOnTheLeft)
{
	if (isOnTheLeft)
		return cocos2d::Vec2(this->mLeftMovingPath1Sprite->getPositionX(),
			this->mLeftMovingPath1Sprite->getPositionY() * 2 + POSITION_DESTROYERS_OFFSET);
	else
		return cocos2d::Vec2(this->mRightMovingPath1Sprite->getPositionX(),
			this->mRightMovingPath1Sprite->getPositionY() * 2 + POSITION_DESTROYERS_OFFSET);
}

void DestroyersMovingPath::StopMoving()
{
	mLeftMovingPath1Sprite->stopAllActions();
	mLeftMovingPath2Sprite->stopAllActions();
	mRightMovingPath1Sprite->stopAllActions();
	mRightMovingPath2Sprite->stopAllActions();
	mCenterMovingPath1Sprite->stopAllActions();
	mCenterMovingPath2Sprite->stopAllActions();
}

void DestroyersMovingPath::Update()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Paths on the left //
	if (mLeftMovingPath1Sprite->getPosition().y <= -visibleSize.height / 2)
		mLeftMovingPath1Sprite->setPosition(origin.x + mLeftMovingPath1Sprite->getContentSize().width / 2,
			origin.y + visibleSize.height / 2);

	if (mLeftMovingPath2Sprite->getPosition().y <= visibleSize.height / 2)
		mLeftMovingPath2Sprite->setPosition(origin.x + mLeftMovingPath2Sprite->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 + visibleSize.height);

	// Paths on the center //
	if (mCenterMovingPath1Sprite->getPosition().y <= -visibleSize.height / 2)
		mCenterMovingPath1Sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	if (mCenterMovingPath2Sprite->getPosition().y <= visibleSize.height / 2)
		mCenterMovingPath2Sprite->setPosition(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2 + visibleSize.height);

	// Paths on the right //
	if (mRightMovingPath1Sprite->getPosition().y <= -visibleSize.height / 2)
		mRightMovingPath1Sprite->setPosition(visibleSize.width - mRightMovingPath1Sprite->getContentSize().width / 2,
			origin.y + visibleSize.height / 2);

	if (mRightMovingPath2Sprite->getPosition().y <= visibleSize.height / 2)
		mRightMovingPath2Sprite->setPosition(visibleSize.width - mRightMovingPath1Sprite->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 + visibleSize.height);
}
