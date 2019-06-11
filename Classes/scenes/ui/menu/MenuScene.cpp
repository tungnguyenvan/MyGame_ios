#include "MenuScene.h"
#include "../../../scenes/ui/menu/LevelsSelectionScene.h"
#include "../../../scenes/intro/IntroStart.h"
#include "../../../common/DefinitionUI.h"
#include "../../../utils/helper/Helper.h"

#include "ui/CocosGUI.h"

cocos2d::Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The background sprite //
	auto backgroundMenuSprite = cocos2d::Sprite::create("sprites/ui/menu_scene/f1.png");
	backgroundMenuSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backgroundMenuSprite, 0);

	// The balloon sprite //
	auto balloonMenuSprite = cocos2d::Sprite::create("sprites/ui/menu_scene/f2.png");
	balloonMenuSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - visibleSize.height);
	this->addChild(balloonMenuSprite, 1);
	auto balloonSpriteMovingAction = cocos2d::MoveBy::create(2, cocos2d::Vec2(0, visibleSize.height));
	balloonMenuSprite->runAction(balloonSpriteMovingAction);

	// The title 1 sprite //
	auto titleMenu1Sprite = cocos2d::Sprite::create("sprites/ui/menu_scene/f3.png");
	titleMenu1Sprite->setPosition(origin.x + visibleSize.width / 2 - visibleSize.width, origin.y + visibleSize.height / 2);
	this->addChild(titleMenu1Sprite, 1);
	auto titleSprite1MovingAction = cocos2d::MoveBy::create(0.6F, cocos2d::Vec2(visibleSize.width, 0));
	titleMenu1Sprite->runAction(titleSprite1MovingAction->clone());
	 
	// The title 2 sprite //
	auto titleMenu2Sprite = cocos2d::Sprite::create("sprites/ui/menu_scene/f4.png");
	titleMenu2Sprite->setPosition(origin.x + visibleSize.width / 2 - visibleSize.width, origin.y + visibleSize.height / 2);
	this->addChild(titleMenu2Sprite, 1);
	auto titleSprite2MovingAction = cocos2d::MoveBy::create(1, cocos2d::Vec2(visibleSize.width, 0));
	titleMenu2Sprite->runAction(titleSprite2MovingAction);

	// Called only once to make buttons transition after a specified duration of time //
	this->scheduleOnce(schedule_selector(MenuScene::ButtonsTransition), 2);

	return true;
}

void MenuScene::ButtonsTransition(float dt)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The play game button //
	auto playButton = cocos2d::ui::Button::create("sprites/ui/menu_scene/play_button_normal.png",
		"sprites/ui/menu_scene/play_button_click.png", "sprites/ui/menu_scene/play_button_click.png");
	playButton->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2 + visibleSize.width,
		origin.y + visibleSize.height / 2 - visibleSize.height / 4));
	this->addChild(playButton, 1);
	auto playButtonMovingAction = cocos2d::MoveBy::create(0.5F, cocos2d::Vec2(-visibleSize.width, 0));
	playButton->runAction(playButtonMovingAction);

	playButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			Play();
			break;
		default:
			break;
		}
	});

	// The share game button //
	auto shareButton = cocos2d::ui::Button::create("sprites/ui/menu_scene/share_button_normal.png",
		"sprites/ui/menu_scene/share_button_click.png", "sprites/ui/menu_scene/share_button_click.png");
	shareButton->setPosition(cocos2d::Vec2(playButton->getPositionX(),
		playButton->getPositionY() - DISTANCE_BETWEEN_BUTTONS_MENU_SCENE));
	this->addChild(shareButton, 1);
	auto shareButtonMovingAction = cocos2d::MoveBy::create(0.7F, cocos2d::Vec2(-visibleSize.width, 0));
	shareButton->runAction(shareButtonMovingAction);

	shareButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			Share();
			break;
		default:
			break;
		}
	});
}

void MenuScene::Play()
{
	if (Helper::HasSkippedTheIntroScene())
	{
		auto newScene = LevelsSelectionScene::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
	}
	else
	{
		auto newScene = IntroStart::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
	}
}

void MenuScene::Share()
{
	cocos2d::Application::getInstance()->openURL("http://www.gameloft.com/en/games");
}
