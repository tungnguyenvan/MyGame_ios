#include "Cannon.h"
#include "../../../../models/objects/other/level9/destroying_weapons/Missle.h"
#include "../../../../common/definitionlevels/DefinitionLevel9.h"
#include "../../../../common/Definition.h"

Cannon::Cannon(cocos2d::Scene* scene, const float& travelingSpeed, const cocos2d::Vec2& departingPosition, const bool& isDepartingOnTheRight)
	: CoreDestroyer(travelingSpeed, departingPosition, "Cannon")
{
	// The core sprite //
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level9/cannon_destroyer.png");
	mCoreSprite->setPosition(departingPosition);
	scene->addChild(mCoreSprite, 2);
	 
	// Deactivate all related attributes at first //
	this->SetActive(false);

	// The head cannon sprite //	
	mExtraComponentSprite = cocos2d::Sprite::create("sprites/gameplay/level9/head_cannon_destroyer.png");
	mExtraComponentSprite->setPosition(mCoreSprite->getContentSize().width / 2, mCoreSprite->getContentSize().height / 2);
	mCoreSprite->addChild(mExtraComponentSprite);

	if(!isDepartingOnTheRight)
	{
		mExtraComponentSprite->setFlippedX(true);
	}

	// Initialize a vector of missles for this cannon //
	for (int i = 0; i < NUMBER_OF_DESTROYING_WEAPONS_EACH_TYPE; i++)
	{
		mVectorOfDestroyingWeapons.push_back(new Missle(scene, "Missle"));
	}
}

void Cannon::Update(const cocos2d::Vec2& balloonPosition)
{
	// Update from parent //
	CoreDestroyer::Update(balloonPosition);

	mFrameCount++;

	// Destroy behavior trigger //
	if (IsAbleToDestroy() && mFrameCount % (int(FPS * 2 * 0.85F)) == 0)
	{
		mFrameCount = 0;

		this->Destroy(balloonPosition);
	}
}
