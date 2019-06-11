#include "CircleObstacleModel.h"
#include "../../../../../utils/physics/CustomPhysicsBody.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"
#include "../../../../../common/definitionlevels/DefinitionLevel7.h"
#include "../../../../../common/Definition.h"

const int CircleObstacleModel::MODE_NONE = 0;
const int CircleObstacleModel::MODE_MOVE_HORIZONTAL = 1;

CircleObstacleModel::CircleObstacleModel(const std::string& name, cocos2d::Sprite* sprite, int mode) : CoreModel(name)
{
	mMode = mode;
	Init();

	sprite->addChild(mCoreSprite);
}

CircleObstacleModel::CircleObstacleModel(const std::string& name, cocos2d::Node* node, int mode) : CoreModel(name)
{
	mMode = mode;
	Init();

	node->addChild(mCoreSprite);
}

CircleObstacleModel::~CircleObstacleModel()
{
	// Destructor
}

void CircleObstacleModel::Init()
{
	mCoreSprite = cocos2d::Sprite::create(mModelName);

	mCorePhysicsBody = cocos2d::PhysicsBody::createCircle(this->GetContentSize().width / 2 - 5);

	mCorePhysicsBody->setDynamic(false);

	if (mModelName == BALLOON_BLUE_PATH)
	{
		mCoreSprite->setTag(BLUE_BALLOON_TAG);
	}
	else if (mModelName == BALLOON_RED_PATH)
	{
		mCoreSprite->setTag(RED_BALLOON_TAG);
	}
	else if (mModelName == BALLOON_GREEN_PATH)
	{
		mCoreSprite->setTag(GREEN_BALLOON_TAG);
	}
	else if (mModelName == BALLOON_YELLOW_PATH)
	{
		mCoreSprite->setTag(YELLOW_BALLOON_TAG);
	}
	else
	{
		mCoreSprite->setTag(OBSTACLES_TAG);
	}

	mCorePhysicsBody->setCategoryBitmask(0x01);
	mCorePhysicsBody->setCollisionBitmask(0x01);
	mCorePhysicsBody->setContactTestBitmask(true);
	mCoreSprite->setPhysicsBody(mCorePhysicsBody);
}

void CircleObstacleModel::Update()
{
	if (mMode == MODE_MOVE_HORIZONTAL && IsActive())
	{
		SetPosition(cocos2d::Vec2(GetPositionX() - 1, GetPositionY()));
		if (GetPositionX() <= -GetContentSize().width / 2)
		{
			SetActive(false);
			SetPosition(cocos2d::Director::getInstance()->getVisibleSize().width
				+ mCoreSprite->getContentSize().width, GetPositionY());
		}
	}
}
