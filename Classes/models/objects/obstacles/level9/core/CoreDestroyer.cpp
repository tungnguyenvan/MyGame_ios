#include "CoreDestroyer.h"
#include "../../../../../common/definitionlevels/DefinitionLevel9.h"

CoreDestroyer::CoreDestroyer(const float& travelingSpeed, const cocos2d::Vec2& departingPosition, const std::string& name)
	: CoreModel(name)
{
	mTravelingSpeed = travelingSpeed;
	mDepartingPosition = departingPosition;

	// There is no physics body in the destroyer objects, so we do this //
	mCorePhysicsBody = nullptr;
}

void CoreDestroyer::Init()
{
	// Initialization //
}

void CoreDestroyer::Update()
{
	// Update //
}

bool CoreDestroyer::IsAbleToDestroy()
{
	return this->GetPositionY() < (cocos2d::Director::getInstance()->getVisibleSize().height - POSITION_DESTROYERS_OFFSET)
		&& this->GetPositionY() > POSITION_DESTROYERS_OFFSET;
}

void CoreDestroyer::Destroy(const cocos2d::Vec2& balloonPosition)
{
	// Iterate through the vector and return an inactive destroying weapon //
	for (int i = 0; i < mVectorOfDestroyingWeapons.size(); i++)
	{
		if (!mVectorOfDestroyingWeapons.at(i)->IsActive())
		{
			mVectorOfDestroyingWeapons.at(i)->StartOperating(this->GetPosition(), balloonPosition);
			break;
		}
	}
}

void CoreDestroyer::Disappear()
{
	// Create a fade-out effect //
	auto fadeOutAction = cocos2d::FadeOut::create(SPRITES_FADING_OUT_TIME_DURATION);

	// Apply the action //
	mCoreSprite->runAction(fadeOutAction);
	mExtraComponentSprite->runAction(fadeOutAction->clone());
}

void CoreDestroyer::Update(const cocos2d::Vec2& balloonPosition)
{
	// Move the destroyer downwards //
	mCoreSprite->setPositionY(mCoreSprite->getPositionY() - mTravelingSpeed);

	// If it reaches the position y threshold, reset it //
	if (mCoreSprite->getPositionY() < -POSITION_DESTROYERS_OFFSET)
	{
		mCoreSprite->setPosition(mDepartingPosition);
		SetActive(false);
	}

	// Set the rotation for the extra component sprite, always bias towards the balloon //
	cocos2d::Vec2 shootingDirection = balloonPosition - this->GetPosition();
	mExtraComponentSprite->setRotation(atan2(shootingDirection.x, shootingDirection.y) * (180.0F / M_PI));
}
