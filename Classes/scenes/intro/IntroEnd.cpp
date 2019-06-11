#include "IntroEnd.h"

cocos2d::Scene* IntroEnd::createScene()
{
	return IntroEnd::create();
}

bool IntroEnd::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	return true;
}

void IntroEnd::update(float dt)
{
	
}
