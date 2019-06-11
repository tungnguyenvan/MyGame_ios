#include "CircleLineModel.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"
#include "../../../../../common/definitionlevels/DefinitionLevel7.h"
#include "../../../../../common/Definition.h"

const int CircleLineModel::OBSTACLE = 0;
const int CircleLineModel::PATH = 1;

CircleLineModel::CircleLineModel(cocos2d::Node* node, std::string name, int type) : CoreModel(name)
 {
	mType = type;
	mIsTouching = false;
	mIsTouchingRight = false;

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	Init();

	if (mType == OBSTACLE)
	{
		node->addChild(mNodeCoin);
	}
	else if (mType == PATH)
	{
		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(CircleLineModel::OnTouchBegan, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(CircleLineModel::OnTouchEnded, this);
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, node);
	}
		node->addChild(mCoreSprite);
}

CircleLineModel::~CircleLineModel()
{
    // Destructor
}

void CircleLineModel::Init()
{
    // Create circle line //
	mCoreSprite = cocos2d::Sprite::create(mModelName);

    // Init vector Circle obstacle model
    InitCircleObstacleModels(mCoreSprite);

    // Init position item of vector Circle obstacle model
    InitPositionCircleObstacleModels();

	if (mType == OBSTACLE) {
		mNodeCoin = cocos2d::Node::create();
		mNodeCoin->setContentSize(GetContentSize());
		mNodeCoin->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	}

}

void CircleLineModel::Update()
{
	if (mType == OBSTACLE)
	{
		mCoreSprite->setRotation(mCoreSprite->getRotation() + 0.5);
		mNodeCoin->setPosition(GetPosition());
	}
	else if (mType == PATH)
	{
		if (mIsTouching)
		{
			if (mIsTouchingRight)
			{
				mCoreSprite->setRotation(mCoreSprite->getRotation() + CIRCLE_SPEED);
			}
			else
			{
				mCoreSprite->setRotation(mCoreSprite->getRotation() - CIRCLE_SPEED);
			}
		}
	}
}

void CircleLineModel::InitCircleObstacleModels(cocos2d::Sprite* sprite)
{
	if (mType == OBSTACLE)
	 {
		for (int i = 0; i < COIN_MODELS_SIZE; i++)
		{
			mCircleObstacleModels.push_back(new CircleObstacleModel(CIRCLE_OBSTACLE_NAME_PATH, sprite));
		}
	}
	else if (mType == PATH)
	{
		mCircleObstacleModels.push_back(new CircleObstacleModel(BALLOON_BLUE_PATH, sprite));
		mCircleObstacleModels.push_back(new CircleObstacleModel(BALLOON_RED_PATH, sprite));
		mCircleObstacleModels.push_back(new CircleObstacleModel(BALLOON_GREEN_PATH, sprite));
		mCircleObstacleModels.push_back(new CircleObstacleModel(BALLOON_YELLOW_PATH, sprite));
		mCircleObstacleModels.push_back(new CircleObstacleModel(BALLOON_CENTER_PATH, sprite));
	}
}

void CircleLineModel::InitPositionCircleObstacleModels()
{
	float radius = GetContentSize().width / 2;
	float corner = 0;

	for (int i = 0; i < mCircleObstacleModels.size(); i++)
	{
		mCircleObstacleModels.at(i)->SetPosition(radius + cos(corner * M_PI / 180.0F) * radius,
			radius + sin(corner * M_PI / 180.0F) * radius);

		if (mType == OBSTACLE)
		{
			corner += 360 / mCircleObstacleModels.size();
		}
		else if (mType == PATH)
		{
			corner += 360 / (mCircleObstacleModels.size() - 1);
		}
	}

	if (mType == PATH)
	{
		mCircleObstacleModels.at(mCircleObstacleModels.size() - 1)->SetPosition(mCoreSprite->getContentSize().width / 2, mCoreSprite->getContentSize().height / 2);
	}
}

bool CircleLineModel::OnTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
 {
	mIsTouching = true;
	
	if (touch->getLocation().x >= SREEEN_RESOLUTION_WIDTH / 2)
	{
		mIsTouchingRight = true;
	}
	else
	{
		mIsTouchingRight = false;
	}
	
	return true;
}

void CircleLineModel::OnTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mIsTouching = false;
}

void CircleLineModel::FadeOutModel(const float& opacity)
{
	CoreModel::FadeOutModel(opacity);

	for (int i = 0; i < mCircleObstacleModels.size(); i++)
	{
		mCircleObstacleModels.at(i)->FadeOutModel(opacity);
		mCircleObstacleModels.at(i)->SetEnablePhysicsBody(false);
	}
}
