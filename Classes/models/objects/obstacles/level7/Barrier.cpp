#include "Barrier.h"
#include "../../../../common/definitionlevels/DefinitionLevel7.h"
#include "../../../../common/Definition.h"

const int Barrier::MODE_MOVE_TOP_TO_BOTTOM = 0;
const int Barrier::MODE_MOVE_BOTTOM_TO_TOP = 1;
const int Barrier::MODE_MOVE_TOP_LEFT_TO_BOTTOM_RIGHT = 2;
const int Barrier::MODE_MOVE_BOTTOM_RIGHT_TO_TOP_LEFT = 3;
const int Barrier::MODE_MOVE_TOP_RIGHT_TO_BOTTOM_LEFT = 4;
const int Barrier::MODE_MOVE_BOTTOM_LET_TO_TOP_RIGHT = 5;

const int Barrier::COLOR_BLUE = 0;
const int Barrier::COLOR_RED = 1;
const int Barrier::COLOR_GREEN = 2;
const int Barrier::COLOR_YELLOW = 3;

Barrier::Barrier(cocos2d::Scene* scene, std::string name, int mode, int color) : CoreModel(name)
{
	/* Set local data */
	mMode = mode;
	mColor = color;
	mBarrierMovingSpeed = BARRIER_OBSTACLES_MOVING_SPEED_EASY;

	mStartPosition = cocos2d::Vec2().ZERO;
	mEndPosition = cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
		cocos2d::Director::getInstance()->getVisibleSize().height / 2);

	/* Create sprite */
	mCoreSprite = cocos2d::Sprite::create(name);

	mCorePhysicsBody = nullptr;
	SetPhysicsBody();
	SetActive(false);

	scene->addChild(mCoreSprite);
}

Barrier::~Barrier()
{
	// Destructor
}

void Barrier::SetPhysicsBody()
{ 
	mCorePhysicsBody = cocos2d::PhysicsBody::createBox(mCoreSprite->getContentSize());
	mCorePhysicsBody->setDynamic(false);
		
	switch (mColor)
	{
	case Barrier::COLOR_BLUE:
		mCoreSprite->setTag(BLUE_BARRIER_OBSTACLES_TAG);
		break;
	case Barrier::COLOR_RED:
		mCoreSprite->setTag(RED_BARRIER_OBSTACLES_TAG);
		break;
	case Barrier::COLOR_GREEN:
		mCoreSprite->setTag(GREEN_BARRIER_OBSTACLES_TAG);
		break;
	default:
		mCoreSprite->setTag(YELLOW_BARRIER_OBSTACLES_TAG);
		break;
	}

	mCorePhysicsBody->setCollisionBitmask(0x02);
	mCorePhysicsBody->setContactTestBitmask(true);
	mCoreSprite->addComponent(mCorePhysicsBody);
}

void Barrier::Init()
{
	SetActive(true);

	mCurrentDistance = 0;

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	switch (mMode)
	{
	case MODE_MOVE_TOP_TO_BOTTOM:
		mStartPosition = cocos2d::Vec2(GetContentSize().width / 2, 
			visibleSize.height + visibleSize.height / 2);
		break;

	case MODE_MOVE_BOTTOM_TO_TOP:
		mStartPosition = cocos2d::Vec2(GetContentSize().width / 2, -visibleSize.height / 2);
		break;

	case MODE_MOVE_TOP_LEFT_TO_BOTTOM_RIGHT:
		SetRotation(-45);
		mStartPosition = cocos2d::Vec2(-visibleSize.width / 2, 
			visibleSize.height + visibleSize.height / 2
		);
		break;

	case MODE_MOVE_BOTTOM_RIGHT_TO_TOP_LEFT:
		SetRotation(-45);
		mStartPosition = cocos2d::Vec2(visibleSize.width + visibleSize.width / 2,
			-visibleSize.height / 2
		);
		break;

	case MODE_MOVE_TOP_RIGHT_TO_BOTTOM_LEFT:
		SetRotation(45);
		mStartPosition = cocos2d::Vec2(visibleSize.width + visibleSize.width / 2,
			visibleSize.height + visibleSize.height / 2
		);
		break;
	default:
		SetRotation(45);
		mStartPosition = cocos2d::Vec2(-visibleSize.width / 2,
			-visibleSize.height / 2
		);
		break;
	}
	SetPosition(mStartPosition);
}

void Barrier::Update()
{
	mFrameCount++;

	if (mFrameCount >= (FPS  * EASY_MODE))
	{
		mBarrierMovingSpeed = BARRIER_OBSTACLES_MOVING_SPEED_NORMAL;
	}
	if (mFrameCount >= (FPS * NORMAL_MODE))
	{
		mBarrierMovingSpeed = BARRIER_OBSTACLES_MOVING_SPEED_HARD;
	}

	if (IsActive())
	{
		mCurrentDistance += mBarrierMovingSpeed;
			
		if (mCurrentDistance >= mEndPosition.getDistance(mStartPosition))
		{
			SetActive(false);
		}

		SetPosition(mStartPosition + (mEndPosition - mStartPosition).getNormalized() * mCurrentDistance);
	}
}
