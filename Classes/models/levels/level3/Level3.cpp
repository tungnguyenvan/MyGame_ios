#include "Level3.h"
#include "../../../common/Definition.h"
#include "../../../common/definitionlevels/DefinitionLevel3.h"

Level3::Level3(cocos2d::Scene *scene) : CoreLevel()
{
	mIndex = 0;
	mPosY = cocos2d::Director::getInstance()->getVisibleSize().height;

	// background
	auto background = cocos2d::Sprite::create(BACKGROUND_NAME_PATH);
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->addChild(background, -1);

	float visibleSizeHight = cocos2d::Director::getInstance()->getVisibleSize().height;

	mCoreLevelFrame.push_back(new Level3Frame1(scene));
	mCoreLevelFrame.push_back(new Level3Frame3(scene));
	mCoreLevelFrame.push_back(new Level3Frame4(scene));
	mCoreLevelFrame.push_back(new Level3Frame2(scene));

	for (int i = 0; i < mCoreLevelFrame.size(); i++)
	{
		mCoreLevelFrame.at(i)->SetPositionY(mPosY);
		mPosY += cocos2d::Director::getInstance()->getVisibleSize().height + 80;
	}

	mPosY -= 2 * (cocos2d::Director::getInstance()->getVisibleSize().height + 80);

	mCirclePath = new CirclePath(scene, BALLOON_RADIUS, BALLOON_NAME_PATH, BALLOON_PATH_NAME_PATH, POSITION_Y_OF_PATH, BALLOON_SPEED);

	// Create physics contact
	mPhysicsContact = cocos2d::EventListenerPhysicsContact::create();
	mPhysicsContact->onContactBegin = CC_CALLBACK_1(Level3::OnContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mPhysicsContact, scene);
}

Level3::~Level3()
{

}

void Level3::Init()
{

}

void Level3::Update()
{
	mFrameCount++;
	if (mFrameCount >= FPS * LEVEL_TIME)
	{
		mIsCompletedLevel = true;
	}

	for (int i = 0; i < mCoreLevelFrame.size(); i++)
	{
		mCoreLevelFrame.at(i)->Update();

		if (mCoreLevelFrame.at(i)->HasFinishedMoving())
		{
			mCoreLevelFrame.at(i)->SetPositionY(mPosY);
		}
	}

	mCirclePath->Update();

	// Fadeout
	if (mIsCompletedLevel || mIsGameOver) {
		for (int i = 0; i < mCoreLevelFrame.size(); i++) {
			mCoreLevelFrame.at(i)->FadeOutFrame(FADE_OUT_STEP);
		}

		mCirclePath->Disappear(FADE_OUT_STEP);
	}
}

bool Level3::OnContactBegin(cocos2d::PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA()->getBody()->getNode();
	auto shapeB = contact.getShapeB()->getBody()->getNode();

	if (shapeA != nullptr && shapeB != nullptr)
	{
		if ((shapeA->getTag() == BALLOON_TAG && shapeB->getTag() == OBSTACLES_TAG) ||
			shapeB->getTag() == BALLOON_TAG && shapeA->getTag() == OBSTACLES_TAG)
		{
			auto balloonExplosion = cocos2d::ParticleSystemQuad::create(BALLOON_EXPLOSION_NAME_PATH);
			balloonExplosion->setPosition(cocos2d::Vec2(0, 0));

			if (shapeA->getTag() == BALLOON_TAG)
			{
				shapeA->getPhysicsBody()->setEnabled(false);
				shapeA->setOpacity(0);
				shapeA->addChild(balloonExplosion);

				mIsGameOver = true;
			}
			else if (shapeB->getTag() == BALLOON_TAG)
			{
				shapeB->getPhysicsBody()->setEnabled(false);
				shapeB->setOpacity(0);
				shapeB->addChild(balloonExplosion);

				mIsGameOver = true;
			}
		}
		else if ((shapeA->getTag() == BALLOON_TAG && shapeB->getTag() == COIN_TAG) ||
			(shapeA->getTag() == COIN_TAG && shapeB->getTag() == BALLOON_TAG))
		{
			if (shapeA->getTag() == COIN_TAG)
			{
				shapeA->getPhysicsBody()->setEnabled(false);
				shapeA->removeFromParent();
			}
			else if (shapeB->getTag() == COIN_TAG)
			{
				shapeB->getPhysicsBody()->setEnabled(false);
				shapeB->removeFromParent();
			}

		}
	}

	return true;
}
