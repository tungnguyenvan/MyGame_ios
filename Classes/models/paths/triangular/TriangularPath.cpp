#include "TriangularPath.h"

TriangularPath::TriangularPath(cocos2d::Scene* scene, const float& lengthPath,
	const std::string& pathNamePath, const std::string& balloonNamePath,
	const float& pathPositionY, const float& balloonMovingSpeed) : CorePath(pathPositionY, balloonMovingSpeed)
{
    /* Change variables here to fit your needs */
    mVisibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    mLengthPath = lengthPath;
	/*******************************************/

    // point top
    mPointTop = cocos2d::Vec2(mVisibleSize.width / 2,(int) (mLengthPath * (std::sqrt(3) / 2)));
    mPointLeft = mPointTop;
    mPointRight = mPointTop;

    // Point left
    while (mPointLeft.y > mPathPositionY)
    {
        mPointLeft = cocos2d::Vect(mPointLeft.x - mBalloonMovingSpeed, mPointLeft.y - mBalloonMovingSpeed);
    }

    // Point Right
    while (mPointRight.y > mPathPositionY)
    {
        mPointRight = cocos2d::Vect(mPointRight.x + mBalloonMovingSpeed, mPointRight.y - mBalloonMovingSpeed);
    }

	// Create path //
    mPathSprite = cocos2d::Sprite::create(pathNamePath);
	mPathSprite->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	mPathSprite->setPosition(cocos2d::Vec2(mVisibleSize.width / 2, mPathPositionY));
	scene->addChild(mPathSprite);

	// Create balloon //
    mBalloonSprite = cocos2d::Sprite::create(balloonNamePath);
    mBalloonSprite->setPosition(mPointTop);
    scene->addChild(mBalloonSprite);

    // Create Event onTouch
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(TriangularPath::OnTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(TriangularPath::OnTouchEnded, this);
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, scene);
}

TriangularPath::~TriangularPath()
{
    // Destructor
}

void TriangularPath::OnMoveToRight()
{
    if (mBalloonSprite->getPositionX() >= mPointTop.x && mBalloonSprite->getPositionY() > mPointRight.y)
    {
        ToPointRight(mIsTouchingRight);
    }
    else if (mBalloonSprite->getPositionX() > mPointLeft.x && mBalloonSprite->getPositionY() == mPointRight.y)
    {
        ToHorizontal(mIsTouchingRight);
    }
    else
    {
        ToPointLeft(mIsTouchingRight);
    }
}

void TriangularPath::OnMoveToLeft()
{
    if (mBalloonSprite->getPositionX() <= mPointTop.x && mBalloonSprite->getPositionY() > mPointRight.y)
    {
        ToPointLeft(false);
    }
    else if (mBalloonSprite->getPositionX() >= mPointLeft.x && mBalloonSprite->getPositionY() == mPointRight.y && mBalloonSprite->getPositionX() < mPointRight.x)
    {
        ToHorizontal(false);
    }
    else
    {
        ToPointRight(false);
    }
}

void TriangularPath::ToPointRight(bool isToRight)
{
    if (isToRight)
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() + mBalloonMovingSpeed, mBalloonSprite->getPositionY() - mBalloonMovingSpeed));
    }
    else
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() - mBalloonMovingSpeed, mBalloonSprite->getPositionY() + mBalloonMovingSpeed));
    }
}

void TriangularPath::ToPointLeft(bool isRight)
{
    if (isRight)
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() + mBalloonMovingSpeed, mBalloonSprite->getPositionY() + mBalloonMovingSpeed));
    }
    else
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() - mBalloonMovingSpeed, mBalloonSprite->getPositionY() - mBalloonMovingSpeed));
    }
}

void TriangularPath::ToHorizontal(bool isRight)
{
    if (isRight)
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() - mBalloonMovingSpeed, mBalloonSprite->getPositionY()));
    }
    else
    {
        mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() + mBalloonMovingSpeed, mBalloonSprite->getPositionY()));
    }
}

bool TriangularPath::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    mIsTouching = true;

    if (touch->getLocation().x >= mVisibleSize.width / 2) {
        mIsTouchingRight = true;
    }else {
        mIsTouchingRight = false;
    }

	return true;
}

void TriangularPath::OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    mIsTouching = false;
}

void TriangularPath::Update()
{
    if (mIsTouching) {
        if (mIsTouchingRight)
        {
            OnMoveToRight();
        }
        else
        {
            OnMoveToLeft();
        }
    }
}
