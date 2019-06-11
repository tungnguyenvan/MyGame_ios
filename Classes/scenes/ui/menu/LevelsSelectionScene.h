#pragma once

#include "cocos2d.h"

class LevelsSelectionScene : public cocos2d::Scene
{
private:
	int mCount;
	void OpenGamePlayScene(const int& levelIndex);
	void GoBackToMenuScene();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelsSelectionScene);
};
