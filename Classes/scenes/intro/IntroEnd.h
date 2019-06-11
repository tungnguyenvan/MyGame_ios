#pragma once


#include "cocos2d.h"

class IntroEnd : public cocos2d::Scene
{
private:
	void update(float dt);
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntroEnd);
};
