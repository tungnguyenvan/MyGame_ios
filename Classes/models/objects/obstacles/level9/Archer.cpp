#include "Archer.h"
#include "../../../../models/objects/other/level9/destroying_weapons/Arrow.h"
#include "../../../../utils/levels/level9/Level9Helper.h"
#include "../../../../common/definitionlevels/DefinitionLevel9.h"
#include "../../../../common/Definition.h"

Archer::Archer(cocos2d::Scene* scene, const float& travelingSpeed, const cocos2d::Vec2& departingPosition)
	: CoreDestroyer(travelingSpeed, departingPosition, "Archer")
{
	// The core sprite //
	mCoreSprite = cocos2d::Sprite::create("sprites/gameplay/level9/archer_destroyer.png");
	mCoreSprite->setPosition(departingPosition);
	scene->addChild(mCoreSprite, 2);

	// Deactivate all related attributes at first //
	this->SetActive(false);

	// The bow sprite //	
	mExtraComponentSprite = cocos2d::Sprite::create("sprites/gameplay/level9/bow archer destroyer/bow p1.png");
	mExtraComponentSprite->setPosition(mCoreSprite->getContentSize().width / 2, mCoreSprite->getContentSize().height / 2);
	mCoreSprite->addChild(mExtraComponentSprite);

	// Initialize a vector of arrows for this archer //
	for (int i = 0; i < NUMBER_OF_DESTROYING_WEAPONS_EACH_TYPE; i++)
	{
		mVectorOfDestroyingWeapons.push_back(new Arrow(scene, "Arrow"));
	}

	// Load sources //
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/gameplay/level9/bow archer destroyer/bow.plist");
}

void Archer::PlayAnimation()
{
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames = Level9Helper::GetAVectorOfSpriteFramesByCache("bow p%d.png",
		NUMBER_OF_BOW_ARCHER_FRAMES);
	mExtraComponentSprite->runAction(cocos2d::Animate::create(cocos2d::Animation::createWithSpriteFrames(animFrames, 0.5f /
		NUMBER_OF_BOW_ARCHER_FRAMES)));
}

void Archer::Update(const cocos2d::Vec2& balloonPosition)
{
	// Update from parent //
	CoreDestroyer::Update(balloonPosition);

	mFrameCount++;

	// Destroy behavior trigger //
	if (IsAbleToDestroy() && mFrameCount % (int(FPS * 2 * 0.9F)) == 0)
	{
		mFrameCount = 0;

		this->PlayAnimation();
		this->Destroy(balloonPosition);
	}
}
