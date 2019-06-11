#include "Level7.h"
#include "../../../common/definitionlevels/DefinitionLevel7.h"
#include "../../../common/Definition.h"

Level7::Level7(cocos2d::Scene *scene)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto backgroundSprite = cocos2d::Sprite::create("sprites/gameplay/level5/background.png");
	backgroundSprite->setPosition(backgroundSprite->getContentSize().width / 2, visibleSize.height / 2);
	scene->addChild(backgroundSprite, -1);

	mCircleLine = new CircleLineModel(scene, CIRCLE_LINE_PATH, CircleLineModel::PATH);
	mCircleLine->SetPosition(visibleSize.width / 2, visibleSize.height / 2);

	mBarriersCreation = new BarriersCreation(scene);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level7::OnContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

Level7::~Level7()
{

}

bool Level7::OnContactBegin(cocos2d::PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	if (shapeA != nullptr && shapeB != nullptr)
	{
		if (shapeA->getNode()->getTag() == shapeB->getNode()->getTag())
		{
			// Barriers with same colors //
			if (shapeA->getCollisionBitmask() == shapeB->getCollisionBitmask())
			{
				return false;
			}

			if (shapeA->getCollisionBitmask() == 0x02)
			{
				DisappearNode(shapeA->getNode());
			}
			else
			{
				DisappearNode(shapeB->getNode());
			}
		}
		else
		{
			if (shapeA->getCollisionBitmask() != shapeB->getCollisionBitmask())
			{
				mIsGameOver = true;
			}
		}
	}

	return true;
}

void Level7::DisappearNode(cocos2d::Node * node)
{
	node->runAction(cocos2d::FadeOut::create(BARRIER_OBSTACLES_FADE_OUT_TIME));
	node->getPhysicsBody()->setEnabled(false);
}

void Level7::Init()
{
	// Initialize
}

void Level7::Update()
{
	mFrameCount++;

	mCircleLine->Update();

	mBarriersCreation->Update();

	if (mBarriersCreation->GetMode() == COMPLETE_LEVEL)
	{
		mIsCompletedLevel = true;
	}

	if (mIsGameOver)
	{
		mBarriersCreation->InactiveBarrier();
		mCircleLine->FadeOutModel(3);
	}
}
