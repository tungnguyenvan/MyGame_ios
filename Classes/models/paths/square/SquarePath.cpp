#include "SquarePath.h"
#include "../../../common/Definition.h"
 
enum Direction
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

SquarePath::SquarePath(cocos2d::Scene* scene, const int& squareWidthSize,
	const std::string& pathNamePath, const std::string& balloonNamePath,
	const float& pathPositionY, const float& ballooonMovingSpeed) : CorePath(pathPositionY, ballooonMovingSpeed)
{
	/*Change variables here to fit your needs*/
	mSquareWidthSize = squareWidthSize;
	mSquareHeightSize = squareWidthSize - 2;
	/*****************************************/

	mPathSprite = cocos2d::Sprite::create(pathNamePath);
	mPathSprite->setPosition(cocos2d::Vec2(SREEEN_RESOLUTION_WIDTH / 2, mPathPositionY));
	mBalloonSprite = cocos2d::Sprite::create(balloonNamePath);
	mBalloonSprite->setPosition(cocos2d::Vec2(SREEEN_RESOLUTION_WIDTH / 2,
		mSquareHeightSize / 2 + mPathSprite->getPositionY()));

	scene->addChild(mPathSprite);
	scene->addChild(mBalloonSprite);
	
	/*rectangle point*/
	mPoint1 = cocos2d::Vec2(mPathSprite->getPositionX() - mSquareWidthSize / 2, 
		(mSquareHeightSize / 2 + mPathSprite->getPositionY()));
	mLength = (mSquareWidthSize / 2 + mPathSprite ->getPositionX())  - mPoint1.x;
	mPoint2 = cocos2d::Vec2(mPoint1.x + mLength, mPoint1.y);
	mPoint3 = cocos2d::Vec2(mPoint2.x, mPoint2.y - mLength);
	mPoint4 = cocos2d::Vec2(mPoint1.x, mPoint3.y);

	mBalloonSprite->setPosition(mPoint1);

	mDirection = TOP;

	auto listenner = cocos2d::EventListenerTouchOneByOne::create();
	listenner->setSwallowTouches(true);
	listenner->onTouchBegan = CC_CALLBACK_2(SquarePath::OnTouchBegan, this);
	listenner->onTouchEnded = CC_CALLBACK_2(SquarePath::OnTouchEnded, this); 
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenner, scene); 
}

void SquarePath::ClockwiseDirection()
{
	if (mBalloonSprite->getPositionX() >= mPoint1.x&&
		mBalloonSprite->getPositionX() < mPoint2.x &&
		mBalloonSprite->getPositionY() == mPoint2.y
		)
	{
		mDirection = TOP;
	}
	else if (mBalloonSprite->getPositionY() <= mPoint2.y &&
		mBalloonSprite->getPositionY() > mPoint3.y &&
		mBalloonSprite->getPositionX() == mPoint3.x
		)
	{
		mDirection = RIGHT;
	}
	else if (mBalloonSprite->getPositionX() <= mPoint3.x &&
		mBalloonSprite->getPositionX() > mPoint4.x &&
		mBalloonSprite->getPositionY() == mPoint4.y
		)
	{
		mDirection = BOTTOM;
	}
	else
	{
		mDirection = LEFT;
	}
}

void SquarePath::CounterClockwiseDirection()
{
	if (mBalloonSprite->getPositionX() > mPoint1.x &&
		mBalloonSprite->getPositionY() == mPoint1.y
		)
	{
		mDirection = TOP;
	}
	else if (mBalloonSprite->getPositionY() <= mPoint1.y &&
		mBalloonSprite->getPositionY() > mPoint4.y &&
		mBalloonSprite->getPositionX() == mPoint4.x
		)
	{
		mDirection = LEFT;
	}
	else if (mBalloonSprite->getPositionX() >= mPoint4.x &&
		mBalloonSprite->getPositionX() < mPoint3.x &&
		mBalloonSprite->getPositionY() == mPoint4.y
		)
	{
		mDirection = BOTTOM;
	}
	else
	{
		mDirection = RIGHT;
	}
}

void SquarePath::moveBalloon(int speed)
{
	if (mDirection == TOP)
	{
		mBalloonSprite->setPositionX(mBalloonSprite->getPositionX() + speed);
	}
	else if (mDirection == BOTTOM)
	{
		mBalloonSprite->setPositionX(mBalloonSprite->getPositionX() - speed);
	}
	else if (mDirection == RIGHT)
	{
		mBalloonSprite->setPositionY(mBalloonSprite->getPositionY() - speed);
	}
	else
	{
		mBalloonSprite->setPositionY(mBalloonSprite->getPositionY() + speed);
	}
}

void SquarePath::Update()
{
	if (mIsTouching)
	{
		if (mTouchLocation.x > SREEEN_RESOLUTION_WIDTH / 2)
		{
			cocos2d::log("sprite : %f -- %f", mBalloonSprite->getPositionX(), mBalloonSprite->getPositionY());
			ClockwiseDirection();
			moveBalloon(mBalloonMovingSpeed);
		}
		else
		{
			CounterClockwiseDirection();
			moveBalloon(-mBalloonMovingSpeed);
		}
	}
}

bool SquarePath::OnTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mIsTouching = true;
	mTouchLocation = touch->getLocation();

	return true;
}

void SquarePath::OnTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mIsTouching = false;
}
