#include "SplashScreenScene.h"
#include "../../../scenes/ui/menu/MenuScene.h"
#include "../../../common/DefinitionUI.h"

cocos2d::Scene* SplashScreenScene::createScene()
{
	return SplashScreenScene::create();
}

bool SplashScreenScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto background = cocos2d::Sprite::create("sprites/ui/splash_screen_scene/background.png");
	background->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(background, -1);

	auto logoSprite = cocos2d::Sprite::create("sprites/ui/splash_screen_scene/logo.png");
	logoSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, background->getContentSize().height / 2 + 50));
	background->addChild(logoSprite, 1);

	auto gameloftSprite = cocos2d::Sprite::create("sprites/ui/splash_screen_scene/name.png");
	gameloftSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, background->getContentSize().height / 2 - 50));
	background->addChild(gameloftSprite, 1);

	// Called only once to go to the menu scene after a specified duration of time //
	this->scheduleOnce(schedule_selector(SplashScreenScene::GoToMenuScene), SCENE_OPENING_DELAY_TIME);

	return true; 
}

void SplashScreenScene::GoToMenuScene(float dt)
{
	auto scene = MenuScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, scene));
}
