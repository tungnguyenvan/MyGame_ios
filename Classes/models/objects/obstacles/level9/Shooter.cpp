#include "Shooter.h"
#include "../../../../models/objects/other/level9/destroying_weapons/Bullet.h"
#include "../../../../common/definitionlevels/DefinitionLevel9.h"
#include "../../../../common/Definition.h"

Shooter::Shooter(cocos2d::Scene* scene, const float& travelingSpeed, const cocos2d::Vec2& departingPosition)
	: CoreDestroyer(travelingSpeed, departingPosition, "Shooter")
{
	// The core sprite //
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level9/shooter_destroyer.png");
	mCoreSprite->setPosition(departingPosition);
	scene->addChild(mCoreSprite, 2);

	// Deactivate all related attributes at first //
	this->SetActive(false);

	// The turret sprite //	
	mExtraComponentSprite = cocos2d::Sprite::create("sprites/gameplay/level9/turret_shooter_destroyer.png");
	mExtraComponentSprite->setPosition(mCoreSprite->getContentSize().width / 2, mCoreSprite->getContentSize().height / 2);
	mCoreSprite->addChild(mExtraComponentSprite);

	// Initialize a vector of bullets for this shooter //
	for (int i = 0; i < NUMBER_OF_DESTROYING_WEAPONS_EACH_TYPE; i++)
	{
		mVectorOfDestroyingWeapons.push_back(new Bullet(scene, "Bullet"));
	}
}

void Shooter::Update(const cocos2d::Vec2& balloonPosition)
{
	// Update from parent //
	CoreDestroyer::Update(balloonPosition);

	mFrameCount++;

	// Destroy behavior trigger //
	if (IsAbleToDestroy() && mFrameCount % (FPS * 2) == 0)
	{
		mFrameCount = 0;

		this->Destroy(balloonPosition);
	}
}
