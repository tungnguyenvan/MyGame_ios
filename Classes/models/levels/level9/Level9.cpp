#include "Level9.h"
#include "../../../common/definitionlevels/DefinitionLevel9.h"
#include "../../../common/Definition.h"

#include "../../../utils/physics/MyBodyParser.h"

Level9::Level9(cocos2d::Scene *scene)
{
	// The circle path controller //  
	mCirclePath = new CirclePath(
		scene,
		CIRCLE_LINE_RADIUS,
		"sprites/gameplay/level9/balloon.png",
		"sprites/gameplay/level9/circle_line.png",
		cocos2d::Director::getInstance()->getVisibleOrigin().y + cocos2d::Director::getInstance()->getVisibleSize().height / 2,
		BALL_MOVING_SPEED);

	// The destroyers creation controller //
	mDestroyersCreation = new DestroyersCreation(scene);

	// Called automatically when there is a collision between objects: For checking collisions
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level9::OnContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

Level9::~Level9()
{
	// Destructor //
}

bool Level9::OnContactBegin(const cocos2d::PhysicsContact& contact)
{
	cocos2d::PhysicsBody* bodyA = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* bodyB = contact.getShapeB()->getBody();

	if (bodyA->getNode() && bodyB->getNode())
	{
		if (bodyA->getNode()->getTag() == BALLOON_TAG &&
			bodyB->getNode()->getTag() == OBSTACLES_TAG ||
			bodyA->getNode()->getTag() == OBSTACLES_TAG &&
			bodyB->getNode()->getTag() == BALLOON_TAG)
		{
			if (bodyA->getNode()->getTag() == BALLOON_TAG || bodyB->getNode()->getTag() == BALLOON_TAG)
			{
				auto balloonNode = bodyA->getNode()->getTag() == BALLOON_TAG ? bodyA : bodyB;
				auto destroyingWeaponNode = bodyA->getNode()->getTag() == OBSTACLES_TAG ? bodyA : bodyB;

				// Create an explosion effect right at the balloon's position //
				auto balloonExplosion = cocos2d::ParticleSystemQuad::create("sprites/gameplay/level9/Ball Particle.plist");
				balloonNode->getNode()->addChild(balloonExplosion, 4);
				balloonExplosion->setPosition(0, 0);

				// Remove the destroying weapon from the scene //
				destroyingWeaponNode->getNode()->removeFromParent();

				// Make the balloon disappear from the scene //
				mCirclePath->Disappear();

				// Make all the objects disappear also //
				mDestroyersCreation->DisappearActiveObjects();

				// Set the game state //
				mIsGameOver = true;
			}
		}
	}

	return false;
}

void Level9::Init()
{
	// Initialization //
}

void Level9::Update()
{
	if (!mIsGameOver)
	{
		// Update the path controller //
		mCirclePath->Update();
	}

	if (!mIsGameOver && !mIsCompletedLevel)
	{
		// Update the destroyers creation controller//
		mDestroyersCreation->Update(mCirclePath->GetTheBalloonPosition());

		if(mDestroyersCreation->GetCreationStage() == CREATION_STAGE_DONE)
		{
			// Make the balloon disappear from the scene //
			mCirclePath->TurnOffPhysics();

			mIsCompletedLevel = true;
		}
	}
}
