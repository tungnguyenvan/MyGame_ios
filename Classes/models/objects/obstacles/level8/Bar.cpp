#include "Bar.h"
#include "../../../../common/definitionlevels/DefinitionLevel8.h"

Bar::Bar(cocos2d::Scene* scene, const float& travelingDuration) : CoreObstacle(travelingDuration, "Bar")
{
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level8/bar_obstacle.png");
	scene->addChild(mCoreSprite, 3);
	 
	// Initialize the physics component //
	this->SetPhysicsBody("Bar Obstacle");
	 
	// Deactivate all related attributes at first //
	this->SetActive(false);
}

void Bar::StartTraveling(const bool& startOnTheRightSide)
{
	CoreObstacle::StartTraveling(startOnTheRightSide);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Set the starting position //
	if (startOnTheRightSide)
		this->SetPosition(origin.x + visibleSize.width / 2 + POSITION_OBSTACLES_OFFSET, visibleSize.height + POSITION_OBSTACLES_OFFSET);
	else
		this->SetPosition(origin.x + visibleSize.width / 2 - POSITION_OBSTACLES_OFFSET, visibleSize.height + POSITION_OBSTACLES_OFFSET);

	// Traveling action //
	auto barObstacleTravelingAction = cocos2d::MoveTo::create(mTravelingDuration * visibleSize.height * OBSTACLES_MOVING_TIME_MULTIPLIER,
		cocos2d::Vec2(this->GetPositionX(), -POSITION_OBSTACLES_OFFSET));

	// Callback for setting back to inactive //
	auto callbackFinishedTraveling = cocos2d::CallFunc::create([=]() {
		this->SetActive(false);
	});

	mCoreSprite->runAction(cocos2d::Sequence::create(barObstacleTravelingAction, callbackFinishedTraveling, nullptr));
}
