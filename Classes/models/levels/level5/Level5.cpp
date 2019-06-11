#include "Level5.h"

Level5::Level5(cocos2d::Scene *scene)
{
	/* Set local data */
	mMode = EASY_MODE;
	mFrameCount = 0;
	mIndexPath = cocos2d::random(1, 4);
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	mRandomTimeLerpColor = cocos2d::random(LINE_FRAME_LERP_COLOR_TIME_MIN, LINE_FRAME_LERP_COLOR_TIME_MAX);

	/* generate color */
	mListOfColors.push_back(cocos2d::Color3B(115,158,60));
	mListOfColors.push_back(cocos2d::Color3B(245,148,83));
	mListOfColors.push_back(cocos2d::Color3B(170, 0, 255));
	mListOfColors.push_back(cocos2d::Color3B(40,54,84));
	mListOfColors.push_back(cocos2d::Color3B(0, 184, 212));
	mListOfColors.push_back(cocos2d::Color3B(0, 200, 83));
	mListOfColors.push_back(cocos2d::Color3B(255, 109, 0));
	mListOfColors.push_back(cocos2d::Color3B(255, 214, 0));
	mListOfColors.push_back(cocos2d::Color3B(250,110,88));
	mListOfColors.push_back(cocos2d::Color3B(75,63,83));
	mListOfColors.push_back(cocos2d::Color3B(250,64,50));
	mListOfColors.push_back(cocos2d::Color3B(35,27,18));
	mListOfColors.push_back(cocos2d::Color3B(37,92,0));
	mListOfColors.push_back(cocos2d::Color3B(18,129,119));

    mCurrentColorIndex = cocos2d::random(0, 13);

	/* Background sprite */
	auto backgroundSprite = cocos2d::Sprite::create(BACKGROUND_PATH);
	backgroundSprite->setPosition(backgroundSprite->getContentSize().width / 2, visibleSize.height / 2);
	scene->addChild(backgroundSprite, -1);

	/* Generate Horizontal line path */
	mHorizontalLinePath = new HorizontalLinePath(scene, HORIZONTAL_LINE_PATH, BALLOON_NAME_PATH, HORIZONTAL_LINE_START_POSITION_Y, BALLOON_MOVING_SPEED);

	/*init line frame */
	mFirstLine = new LineFrame(scene, "sprites/gameplay/level5/line/line_frame_0.png");
	mFirstLine->SetPhysicsBody(0);
	mFirstLine->SetPosition(cocos2d::Vec2(mFirstLine->GetContentSize().width / 2, visibleSize.height / 2));

	mSecondLine = new LineFrame(scene, GetLineFramePath());
	mSecondLine->SetPhysicsBody(mIndexPath);
	mSecondLine->SetPosition(cocos2d::Vec2(mFirstLine->GetPositionX(),
		mFirstLine->GetPositionY() + mFirstLine->GetContentSize().height));

	mThirdLine = new LineFrame(scene, GetLineFramePath());
	mThirdLine->SetPhysicsBody(mIndexPath);
	mThirdLine->SetPosition(cocos2d::Vec2(mSecondLine->GetPositionX(),
		mSecondLine->GetPositionY() + mSecondLine->GetContentSize().height));

	LerpColor();

	/* Collision detection */
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level5::OnContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

Level5::~Level5()
{
	// Destructor
}

void Level5::MoveLine()
{
	/*active and change physics body related to texture of line frame*/
	if (!mFirstLine->IsActive())
	{
		mFirstLine->setTexture(GetLineFramePath());
		mFirstLine->SetPhysicsBody(mIndexPath);
		mFirstLine->SetPosition(mThirdLine->GetPosition() +
			cocos2d::Vec2(0, mThirdLine->GetContentSize().height));
	}
	if (!mSecondLine->IsActive())
	{
		mSecondLine->setTexture(GetLineFramePath());
		mSecondLine->SetPhysicsBody(mIndexPath);
		mSecondLine->SetPosition(mFirstLine->GetPosition() +
			cocos2d::Vec2(0, mSecondLine->GetContentSize().height));
	}
	if (!mThirdLine->IsActive())
	{
		mThirdLine->setTexture(GetLineFramePath());
		mThirdLine->SetPhysicsBody(mIndexPath);
		mThirdLine->SetPosition(mSecondLine->GetPosition() +
			cocos2d::Vec2(0, mThirdLine->GetContentSize().height));
	}
}

std::string Level5::GetLineFramePath()
{
	char linePath[50];
	sprintf(linePath, LINE_FRAME_NAME_PATH_FORMAT, mIndexPath);

	return linePath;
}

void Level5::LerpColor()
{
	mFirstLine->LerpColor(mListOfColors.at(mCurrentColorIndex));
	mSecondLine->LerpColor(mListOfColors.at(mCurrentColorIndex));
	mThirdLine->LerpColor(mListOfColors.at(mCurrentColorIndex));

	mRandomTimeLerpColor = cocos2d::random(LINE_FRAME_LERP_COLOR_TIME_MIN, LINE_FRAME_LERP_COLOR_TIME_MAX);
}

bool Level5::OnContactBegin(cocos2d::PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	if ((shapeA->getNode()->getTag() == BALLOON_TAG && shapeB->getNode()->getTag() == OBSTACLES_TAG) ||
		(shapeB->getNode()->getTag() == BALLOON_TAG && shapeA->getNode()->getTag() == OBSTACLES_TAG))
	{
		if (shapeA->getTag() == BALLOON_TAG)
		{
			DisappearBalloon(shapeA->getNode());

			mIsGameOver = true;
		}
		else
		{
			DisappearBalloon(shapeB->getNode());

			mIsGameOver = true;
		}
	}

	return true;
}

void Level5::DisappearBalloon(cocos2d::Node* node)
{
	auto BalloonExplosion = cocos2d::ParticleSystemQuad::create(BALLOON_EXPLOSION_PATH);

	node->addChild(BalloonExplosion, 1000);
	BalloonExplosion->setPosition(0, 0);

	node->setOpacity(0);
	node->removeComponent(node->getPhysicsBody());
}

void Level5::Init()
{
	// Initialize
}

void Level5::Update()
{
	mFrameCount++;

	if (mFrameCount % FPS == 0)
	{
		MoveLine();
	}

	if (mFrameCount % (FPS * mRandomTimeLerpColor) == 0)
	{
		LerpColor();
		mCurrentColorIndex++;

		if (mCurrentColorIndex >= mListOfColors.size())
		{
			mCurrentColorIndex = 0;
		}
	}

	mHorizontalLinePath->Update();

	mFirstLine->Update();
	mSecondLine->Update();
	mThirdLine->Update();

	// change mode //
	if (mFrameCount >= (FPS * EASY_MODE))
	{
		mMode = NORMAL_MODE;
	}
	if (mFrameCount >= (FPS * NORMAL_MODE))
	{
		mMode = HARD_MODE;
	}
	if (mFrameCount >= (FPS * COMPLETED_LEVEL))
	{
		mIsCompletedLevel = true;
	}

	/* Change speed during speed change */
	if (mMode == EASY_MODE)
	{
		mIndexPath = cocos2d::random(LINE_FRAME_EASY_MODE_MIN_SIZE, LINE_FRAME_EASY_MODE_MAX_SIZE);
	}

	if (mMode == NORMAL_MODE)
	{
		mIndexPath = cocos2d::random(LINE_FRAME_NORMAL_MODE_MIN_SIZE, LINE_FRAME_NORMAL_MODE_MAX_SIZE);

		mHorizontalLinePath->setBalloonMovingSpeed(BALLOON_MOVING_SPEED_NORMAL);
	}

	if (mMode == HARD_MODE)
	{
		mIndexPath = cocos2d::random(LINE_FRAME_HARD_MODE_MIN_SIZE, LINE_FRAMES_SIZE);

		mHorizontalLinePath->setBalloonMovingSpeed(BALLOON_MOVING_SPEED_HARD);
	}

	// game over fade out transition
	if (mIsGameOver || mIsCompletedLevel)
	{
		mFirstLine->FadeOutModel(FADE_OUT_STEP_OPACITY);
		mFirstLine->SetEnablePhysicsBody(false);
		mSecondLine->FadeOutModel(FADE_OUT_STEP_OPACITY);
		mSecondLine->SetEnablePhysicsBody(false);
		mThirdLine->FadeOutModel(FADE_OUT_STEP_OPACITY);
		mThirdLine->SetEnablePhysicsBody(false);
	}

}
