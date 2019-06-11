#pragma once
 
#include "../../models/levels/core/corelevel/CoreLevel.h"

#include "cocos2d.h"

class GamePlayScene : public cocos2d::Scene
{
private:
	int mFrameCount;
	CoreLevel* mCurrentLevel;
	bool mHasVibrated;

	/**
	* Show a panel when the balloon hit something (die)
	*/
	void ShowGameOverPanel();
	 
	/**
	* Show a panel when the player completed a level
	*/
	void ShowLevelCompletionPanel();

	/**
	* Update every second
	*/
	void update(float dt);


public:
	static int sCurrentLevelIndex;

	static cocos2d::Scene* createScene(const int& levelIndex);
	virtual bool init();
	CREATE_FUNC(GamePlayScene);
};
