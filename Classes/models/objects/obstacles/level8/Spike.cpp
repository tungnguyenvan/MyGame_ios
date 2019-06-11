#include "Spike.h"
#include "../../../../common/definitionlevels/DefinitionLevel8.h"

Spike::Spike(cocos2d::Scene* scene, const float& travelingDuration) : CoreObstacle(travelingDuration, "Spike")
{
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level8/spike_obstacle.png");
	scene->addChild(mCoreSprite, 3);

	// Initialize the physics component //
	this->SetPhysicsBody("Spike Obstacle");

	// Deactivate all related attributes at first //
	this->SetActive(false);
}

void Spike::StartTraveling(const bool& startOnTheRightSide)
{
	// Exceptional case //	
	if (startOnTheRightSide)
	{
		mCoreSprite->removeComponent(mCorePhysicsBody);
		this->SetPhysicsBody("Spike Obstacle Inverted");
	}
	else
	{
		mCoreSprite->removeComponent(mCorePhysicsBody);
		this->SetPhysicsBody("Spike Obstacle");
	}

	CoreObstacle::StartTraveling(startOnTheRightSide);

	// Flip the sprite in the right direction //
	mCoreSprite->setFlipX(startOnTheRightSide);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Set the starting position //
	if (startOnTheRightSide)
		this->SetPosition(origin.x + visibleSize.width / 2 + POSITION_OBSTACLES_OFFSET, -POSITION_OBSTACLES_OFFSET);
	else
		this->SetPosition(origin.x + visibleSize.width / 2 - POSITION_OBSTACLES_OFFSET, -POSITION_OBSTACLES_OFFSET);

	// Traveling action //
	auto spikeObstacleTravelingAction = cocos2d::MoveTo::create(mTravelingDuration * visibleSize.height * OBSTACLES_MOVING_TIME_MULTIPLIER,
		cocos2d::Vec2(this->GetPositionX(), visibleSize.height + POSITION_OBSTACLES_OFFSET));

	// Callback for setting back to inactive //
	auto callbackFinishedTraveling = cocos2d::CallFunc::create([=]() {
		this->SetActive(false);
	});

	mCoreSprite->runAction(cocos2d::Sequence::create(spikeObstacleTravelingAction, callbackFinishedTraveling, nullptr));
}
