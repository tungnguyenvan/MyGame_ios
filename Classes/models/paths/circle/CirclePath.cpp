#include "CirclePath.h"
#include "../../../common/Definition.h"
#include "../../../common/definitionlevels/DefinitionLevel9.h"

#include "cocos2d.h"

CirclePath::CirclePath(cocos2d::Scene* scene, const float& circlePathRadius,
	const std::string& balloonNamePath, const std::string& pathNamePath,
	const float& pathPositionY, const float& ballooonMovingSpeed) : CorePath(pathPositionY, ballooonMovingSpeed)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Set local data // 
	mCurrentAngle = 90.0F;
	mCenterPositionX = origin.x + visibleSize.width / 2; 

	/* Change variables here to fit your needs */
	mCirclePathRadius = circlePathRadius;
	/*******************************************/

	// The circle path sprite //
	mPathSprite = cocos2d::Sprite::create(pathNamePath);
	mPathSprite->setPosition(mCenterPositionX, mPathPositionY);
	scene->addChild(mPathSprite, 1);

	// The balloon sprite //
	mBalloonSprite = cocos2d::Sprite::create(balloonNamePath);
	mBalloonSprite->setPosition(mCenterPositionX, mPathPositionY + mCirclePathRadius);
	scene->addChild(mBalloonSprite, 2);

	mBalloonSprite->setTag(BALLOON_TAG);

	auto balloonPhysics = cocos2d::PhysicsBody::createCircle(mBalloonSprite->getContentSize().width / 2
		- BALLOON_COLLISION_OFFSET_RADIUS);
	balloonPhysics->setDynamic(false);
	balloonPhysics->setCollisionBitmask(BALLOON_COLLISION_BITMASK);
	balloonPhysics->setContactTestBitmask(true);
	mBalloonSprite->addComponent(balloonPhysics);

	// Called automatically when users manipulate the screen for the balloon's movement //
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CirclePath::OnTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CirclePath::OnTouchEnded, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, scene);
}

bool CirclePath::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	mIsTouching = true;

	if (touch->getLocation().x >= SREEEN_RESOLUTION_WIDTH / 2)
		mIsTouchingRight = true;
	else
		mIsTouchingRight = false;

	return true;
}

void CirclePath::OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	mIsTouching = false;
}

void CirclePath::TurnOffPhysics()
{
	mBalloonSprite->removeComponent(mBalloonSprite->getPhysicsBody());
}

void CirclePath::Update()
{
	if (mIsTouching)
	{
		if (mIsTouchingRight)
			mCurrentAngle -= mBalloonMovingSpeed;
		else
			mCurrentAngle += mBalloonMovingSpeed;

		mBalloonSprite->setPosition(mCenterPositionX + cos(mCurrentAngle * M_PI / 180.0F) * mCirclePathRadius,
			mPathPositionY + sin(mCurrentAngle * M_PI / 180.0F) * mCirclePathRadius);
	}
}

cocos2d::Vec2 CirclePath::GetTheBalloonPosition()
{
	return mBalloonSprite->getPosition();
}
