#include "Missle.h" 
#include "../../../../../common/Definition.h"
#include "../../../../../common/definitionlevels/DefinitionLevel9.h"

Missle::Missle(cocos2d::Scene* scene, const std::string& name) : DestroyingWeapon(name)
{
	// The core sprite //
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level9/destroying weapons/missle.png");
	scene->addChild(mCoreSprite, 3);

	// Set tag for the core sprite //
	mCoreSprite->setTag(OBSTACLES_TAG);

	// Set the physics body for the core sprite //
	mCorePhysicsBody = cocos2d::PhysicsBody::createCircle(mCoreSprite->getContentSize().width / 2);
	mCorePhysicsBody->setDynamic(false);
	mCorePhysicsBody->setCollisionBitmask(OBSTACLES_COLLISION_BITMASK);
	mCorePhysicsBody->setContactTestBitmask(true);
	mCoreSprite->setPhysicsBody(mCorePhysicsBody);

	// Deactivate all related attributes at first //
	this->SetActive(false);
}

void Missle::StartOperating(const cocos2d::Vec2& originPosition, const cocos2d::Vec2& destinationPosition)
{
	// Show the sprite //
	this->SetActive(true);

	auto rotatingAction = cocos2d::RotateBy::create(1, 360);
	mCoreSprite->runAction(cocos2d::RepeatForever::create(rotatingAction));

	// Set the departing position //
	this->SetPosition(originPosition + (destinationPosition - originPosition).getNormalized()
		* MISSLE_POSITION_OFFSET_NORMALIZE);
	 
	// Traveling action //
	auto travelingAction = cocos2d::MoveTo::create
	(1.0F/originPosition.getDistance(destinationPosition) * MISSLE_TRAVELING_TIME_DURATION_MULTIPLIER,
		originPosition + (destinationPosition - originPosition).getNormalized() * MISSLE_TRAVELING_PATH_NORMALIZE);

	// Callback for setting back to inactive //
	auto callbackFinishedTraveling = cocos2d::CallFunc::create([=]() {
		this->SetActive(false);
	});

	mCoreSprite->runAction(cocos2d::Sequence::create(travelingAction, callbackFinishedTraveling, nullptr));
}
