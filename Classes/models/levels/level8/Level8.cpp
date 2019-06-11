#include "Level8.h"
#include "../../../common/definitionpaths/verticalline/DefinitionVerticalLine.h";
#include "../../../common/Definition.h"

#include "../../../utils/physics/MyBodyParser.h"

Level8::Level8(cocos2d::Scene *scene)
{
	// Physics sources loading //
	MyBodyParser::getInstance()->parseJsonFile("sprites/gameplay/level8/obstacles.json");

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The background sprite //
	auto backgroundSprite = cocos2d::Sprite::create("sprites/gameplay/level8/background.png");
	backgroundSprite->setPosition(cocos2d::Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	scene->addChild(backgroundSprite, 0);

	// The vertical line path controller //
	mVerticalLinePath = new VerticalLinePath(scene, DISTANCE_BETWEEN_BALLOON_AND_THE_PATH,
		PATH_MOVING_SPEED, THRESHOLD_MOVING_DISTANCE, "sprites/gameplay/level8/balloon.png",
		"sprites/gameplay/level8/vertical_line.png", origin.y + visibleSize.height / 2);

	// The obstacles creation controller //
	mObstaclesCreation = new ObstaclesCreation(scene);

	// Set local data //
	mIsGameOver = false;

	// Called automatically when there is a collision between objects: For checking collisions
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level8::OnContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

Level8::~Level8()
{
	// Destructor //
}

bool Level8::OnContactBegin(const cocos2d::PhysicsContact& contact)
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

				// Create an explosion effect right at the balloon's position //
				auto balloonExplosion = cocos2d::ParticleSystemQuad::create("sprites/gameplay/level8/Ball Particle.plist");
				balloonNode->getNode()->addChild(balloonExplosion, 4);
				balloonExplosion->setPosition(0, 0);

				// Make the balloon disappear from the scene //
				mVerticalLinePath->Disappear(); 

				// Make the active obstacles disappear from the scene as well //
				mObstaclesCreation->DisappearActiveObjects();

				// Set the game state //
				mIsGameOver = true;
			}
		}
	}

	return false;
}

void Level8::Init()
{
	// Initialization //
}

void Level8::Update()
{
	if (!mIsGameOver && !mIsCompletedLevel)
	{
		// Update the path controller //
		mVerticalLinePath->Update();

		// Update the obstacles creation controller//
		mObstaclesCreation->Update(mVerticalLinePath->GetTheCurrentStage());

		if(mVerticalLinePath->GetTheCurrentStage() == DONE)
		{
			mIsCompletedLevel = true;
		}
	}
}
