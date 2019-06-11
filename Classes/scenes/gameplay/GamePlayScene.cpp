#include "GamePlayScene.h"
#include "../../models/levels/level3/Level3.h"
#include "../../models/levels/level4/Level4.h"
#include "../../models/levels/level5/Level5.h"
#include "../../models/levels/level7/Level7.h"
#include "../../models/levels/level8/Level8.h"
#include "../../models/levels/level9/Level9.h"
#include "../../scenes/ui/panels/gameover/GameOverPanel.h"
#include "../../scenes/ui/panels/level_completion/LevelCompletionPanel.h"
#include "../../common/Definition.h"
#include "../../common/DefinitionUI.h"

int GamePlayScene::sCurrentLevelIndex = 0;

cocos2d::Scene* GamePlayScene::createScene(const int& levelIndex)
{
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_NONE);

	sCurrentLevelIndex = levelIndex - 1;

	auto layer = GamePlayScene::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlayScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Set local data //
	mFrameCount = 0;
    mHasVibrated = false;

	// Assign the right level based on the index //
	switch (sCurrentLevelIndex)
	{
	case 0:
		mCurrentLevel = new Level3(this);
		break;
	case 1:
		mCurrentLevel = new Level4(this);
		break;
	case 2:
		mCurrentLevel = new Level5(this);
		break;
	case 3:
		mCurrentLevel = new Level7(this);
		break;
	case 4:
		mCurrentLevel = new Level8(this);
		break;
	case 5:
		mCurrentLevel = new Level9(this);
		break;
	case 6:
		mCurrentLevel = new Level9(this);
		break;
	case 7:
		mCurrentLevel = new Level9(this);
		break;
	case 8:
		mCurrentLevel = new Level9(this);
		break;
	} 

	this->scheduleUpdate();

	return true;
}

void GamePlayScene::ShowGameOverPanel()
{
	new GameOverPanel(this);
}

void GamePlayScene::ShowLevelCompletionPanel()
{ 
	new LevelCompletionPanel(this);
}

void GamePlayScene::update(float dt)
{
	mCurrentLevel->Update();

	if (mCurrentLevel->IsGameOver() || mCurrentLevel->IsCompletedLevel())
	{
		if (mCurrentLevel->IsGameOver() && !mHasVibrated)
		{
            mHasVibrated = true;
            
			cocos2d::Device::vibrate(0.3f);
		}

		mFrameCount++;

		if (mFrameCount >= FPS * TIME_DELAY_BEFORE_OPENING_PANELS)
		{
			if(mCurrentLevel->IsGameOver())
			{
				ShowGameOverPanel();
			}
			else
			{
				ShowLevelCompletionPanel();
			}

			this->unscheduleUpdate();
		}
	}
}
