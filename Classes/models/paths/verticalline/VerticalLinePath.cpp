#include "VerticalLinePath.h"
#include "../../../common/Definition.h"
#include "../../../common/definitionlevels/DefinitionLevel8.h"
#include "../../../common/definitionpaths/verticalline/DefinitionVerticalLine.h";

VerticalLinePath::VerticalLinePath(cocos2d::Scene* scene, const float& distanceBetweenBaloonAndThePath,
	const float& pathMovingSpeed, const float& thresholdMovingDistance,
	const std::string& balloonNamePath, const std::string& pathNamePath,
	const float& pathPositionY) : CorePath(pathPositionY, 0)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Set local data // 
	mIsMovingDown = true;
	mFrameCount = 0;
	mCurrentStage = STAGE_1_MOVE_DOWN;

	/* Change variables here to fit your needs */
	mDistanceBetweenBaloonAndThePath = distanceBetweenBaloonAndThePath;
	mPathMovingSpeed = pathMovingSpeed;
	mThresholdMovingDistance = thresholdMovingDistance;
	/*******************************************/

	// The line path sprite //
	mPathSprite = cocos2d::Sprite::create(pathNamePath);
	mPathSprite->setPosition(origin.x + visibleSize.width / 2, mPathPositionY);
	scene->addChild(mPathSprite, 1);

	// The balloon sprite //
	mBalloonSprite = cocos2d::Sprite::create(balloonNamePath);
	mBalloonSprite->setPosition(mPathSprite->getContentSize().width / 2 + mDistanceBetweenBaloonAndThePath,
		mPathSprite->getContentSize().height / 2);
	mBalloonSprite->setTag(BALLOON_TAG);

	// The balloon physics body //
	auto mBalloonPhysicsBody = cocos2d::PhysicsBody::createCircle(mBalloonSprite->getContentSize().width / 2 - COLLISION_OFFSET_RADIUS);
	mBalloonPhysicsBody->setGravityEnable(false);
	mBalloonPhysicsBody->setCategoryBitmask(0x01);
	mBalloonPhysicsBody->setContactTestBitmask(true);
	mBalloonPhysicsBody->setRotationEnable(false);
	mBalloonSprite->setPhysicsBody(mBalloonPhysicsBody);

	mPathSprite->addChild(mBalloonSprite, 2);

	// Called automatically when users manipulate the screen for the balloon's movement //
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(VerticalLinePath::OnTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(VerticalLinePath::OnTouchEnded, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, scene);
}

void VerticalLinePath::MoveThePath()
{
	if (mIsMovingDown)
	{
		mPathSprite->setPosition(mPathSprite->getPosition().x,
			mPathSprite->getPosition().y - mPathMovingSpeed);

		if (mPathSprite->getPosition().y <= mPathPositionY - mThresholdMovingDistance)
		{
			mIsMovingDown = false;
		}
	}
	else
	{
		mPathSprite->setPosition(mPathSprite->getPosition().x,
			mPathSprite->getPosition().y + mPathMovingSpeed);

		if (mPathSprite->getPosition().y >= mPathPositionY + mThresholdMovingDistance)
		{
			mIsMovingDown = true;
		}
	}
}

bool VerticalLinePath::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	mIsTouching = true;

	if (touch->getLocation().x >= SREEEN_RESOLUTION_WIDTH / 2)
		mIsTouchingRight = true;
	else
		mIsTouchingRight = false;

	return true;
}

void VerticalLinePath::OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	mIsTouching = false;
}

void VerticalLinePath::Update()
{
	// Stage 1: Move the path down and stop at a particular position //
	if (mCurrentStage == STAGE_1_MOVE_DOWN)
	{
		mPathSprite->setPosition(mPathSprite->getPosition().x,
			mPathSprite->getPosition().y - mPathMovingSpeed);

		if (mPathSprite->getPosition().y <= mPathPositionY - mThresholdMovingDistance)
		{
			mCurrentStage = STAGE_2_IDLE;
		}
	}
	// Stage 2: Stay idly for a specified period of time //
	else if (mCurrentStage == STAGE_2_IDLE)
	{
		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_2)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_2_IDLE_AGAIN;
		}
	}
	// Stage 2: Stay idly again a bit more //
	else if (mCurrentStage == STAGE_2_IDLE_AGAIN)
	{
		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_2_EXTRA)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_3_MOVE_UP;
		}
	}
	// Stage 3: Move the path up to a new position and stay there //
	else if (mCurrentStage == STAGE_3_MOVE_UP)
	{
		mPathSprite->setPosition(mPathSprite->getPosition().x,
			mPathSprite->getPosition().y + mPathMovingSpeed);

		if (mPathSprite->getPosition().y >= mPathPositionY + mThresholdMovingDistance)
		{
			mCurrentStage = STAGE_4_IDLE;
		}
	}
	// Stage 4: Stay idly for a specified period of time //
	else if (mCurrentStage == STAGE_4_IDLE)
	{
		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_4)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_4_IDLE_AGAIN;
		}
	}
	// Stage 4: Stay idly again a bit more //
	else if (mCurrentStage == STAGE_4_IDLE_AGAIN)
	{
		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_4_EXTRA)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_5_MOVE_UP_AND_DOWN;
		}
	}
	// Stage 5: Move the path up and down to increase the difficulty //
	else if (mCurrentStage == STAGE_5_MOVE_UP_AND_DOWN)
	{
		MoveThePath();

		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_5)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_6_IDLE;
		}
	}
	// Stage 6: Stay idly for a specified period of time //
	else if (mCurrentStage == STAGE_6_IDLE)
	{
		mFrameCount++;

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_6)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_7_MOVE_ARBITRARY;
		}
	}
	// Stage 7: Move the path arbitrarily to increase the difficulty //
	else if (mCurrentStage == STAGE_7_MOVE_ARBITRARY)
	{
		MoveThePath();

		mFrameCount++;

		if (mFrameCount % (int(FPS * TIME_RUNNING_STAGE_7_PER_TURN)) == 0)
		{
			mIsMovingDown = cocos2d::random(1, 2) % 2 == 0 ? mIsMovingDown : !mIsMovingDown;
		}

		if (mFrameCount == FPS * TIME_RUNNING_STAGE_7)
		{
			mFrameCount = 0;

			mCurrentStage = STAGE_8_DISAPPEAR;
		}
	}
	// Stage 8: Fade the path and balloon sprites, make it disappear after a specified duration of time //
	else if (mCurrentStage == STAGE_8_DISAPPEAR)
	{
		auto fadeOutAction = cocos2d::FadeOut::create(SPRITES_FADING_OUT_TIME_DURATION);

		CorePath::Disappear();

		mCurrentStage = DONE;
	}

	// The ball movement //
    	if (mCurrentStage != DONE)
	{
		if (mIsTouching)
		{
			if (mIsTouchingRight)
			{
				mBalloonSprite->setPosition(mPathSprite->getContentSize().width / 2 + mDistanceBetweenBaloonAndThePath,
					mPathSprite->getContentSize().height / 2);
			}
			else
			{
				mBalloonSprite->setPosition(mPathSprite->getContentSize().width / 2 - mDistanceBetweenBaloonAndThePath,
					mPathSprite->getContentSize().height / 2);
			}
		}
	}
}

Stage VerticalLinePath::GetTheCurrentStage()
{
	return mCurrentStage;
}

void VerticalLinePath::Disappear()
{
	mBalloonSprite->setOpacity(1);

	mPathSprite->runAction(cocos2d::FadeOut::create(1));
	mBalloonSprite->removeComponent(mBalloonSprite->getPhysicsBody());

	mCurrentStage = DONE;
}
