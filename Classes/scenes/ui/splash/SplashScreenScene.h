#pragma once

#include "cocos2d.h"

class SplashScreenScene : public cocos2d::Scene
{
private:
	void GoToMenuScene(float dt);
 
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SplashScreenScene);
};