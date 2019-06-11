#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
private:
	void ButtonsTransition(float dt);

	void Play();
	void Share();
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);
};
