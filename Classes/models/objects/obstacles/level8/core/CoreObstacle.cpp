#include "CoreObstacle.h"
#include "../../../../../common/Definition.h"
#include "../../../../../common/definitionlevels/DefinitionLevel8.h"

#include "../../../../../utils/physics/MyBodyParser.h"

CoreObstacle::CoreObstacle(const float& travelingDuration, const std::string& name) : CoreModel(name)
{
	mTravelingDuration = travelingDuration;
}

void CoreObstacle::Init()
{
	// Initialization //
}

void CoreObstacle::Update()
{
	// Update //
}

void CoreObstacle::SetPhysicsBody(const std::string& physicsBodyName)
{
	// Set tag for the core sprite //
	mCoreSprite->setTag(OBSTACLES_TAG);

	// Set the physics body for the core sprite //
	mCorePhysicsBody = MyBodyParser::getInstance()->bodyFormJson(mCoreSprite, physicsBodyName, cocos2d::PhysicsMaterial(1, 0, 0));
	mCorePhysicsBody->setDynamic(false);
	mCorePhysicsBody->setCollisionBitmask(0x02);
	mCorePhysicsBody->setContactTestBitmask(true);
	mCoreSprite->setPhysicsBody(mCorePhysicsBody);
}

void CoreObstacle::Disappear()
{
	auto fadeOutAction = cocos2d::FadeOut::create(SPRITES_FADING_OUT_TIME_DURATION / 2);
	mCoreSprite->runAction(fadeOutAction);
}

void CoreObstacle::StartTraveling(const bool& startOnTheRightSide)
{
	this->SetActive(true);
}
