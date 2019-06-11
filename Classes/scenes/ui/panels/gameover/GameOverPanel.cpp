#include "GameOverPanel.h"
#include "../../../../scenes/ui/menu/MenuScene.h"
#include "../../../../scenes/gameplay/GamePlayScene.h"
#include "../../../../common/DefinitionUI.h"

#include "ui/CocosGUI.h"

GameOverPanel::GameOverPanel(cocos2d::Scene* scene)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The background sprite //
	char str[100];
	sprintf(str, "sprites/ui/panels/l%d.png", GamePlayScene::sCurrentLevelIndex + 1);
	auto backgroundSprite = cocos2d::Sprite::create(str);
	backgroundSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	scene->addChild(backgroundSprite, 10);
	backgroundSprite->setOpacity(0);
	auto backgroundFadingAction = cocos2d::FadeIn::create(0.5F);
	backgroundSprite->runAction(backgroundFadingAction);

	// The gameover title sprite //
	auto gameoverTitleSprite = cocos2d::Sprite::create("sprites/ui/panels/gameover/gameover_title.png");
	gameoverTitleSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width,
		visibleSize.height - GAMEOVER_TITLE_OFFSET_SCREEN_TOP));
	scene->addChild(gameoverTitleSprite, 11);
	auto gameoverTitleMovingAction = cocos2d::MoveBy::create(0.5F, cocos2d::Vec2(-visibleSize.width, 0));
	gameoverTitleSprite->runAction(gameoverTitleMovingAction);

	// The board sprite //
	auto boardSprite = cocos2d::Sprite::create("sprites/ui/panels/gameover/board.png");
	boardSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width,
		gameoverTitleSprite->getPositionY() - boardSprite->getContentSize().height / 2
		- GAMEOVER_TITLE_OFFSET_SCREEN_TOP));
	scene->addChild(boardSprite, 11);
	auto boardMovingAction = cocos2d::MoveBy::create(0.7F, cocos2d::Vec2(-visibleSize.width, 0));
	boardSprite->runAction(boardMovingAction);

	// The share button //
	auto shareButton = cocos2d::ui::Button::create("sprites/ui/panels/gameover/share_button_normal.png",
		"sprites/ui/panels/gameover/share_button_click.png", "sprites/ui/panels/gameover/share_button_click.png");
	shareButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width,
		boardSprite->getPositionY() - boardSprite->getContentSize().height / 2 - shareButton->getContentSize().height));
	scene->addChild(shareButton, 11);
	auto shareButtonMovingAction = cocos2d::MoveBy::create(0.9F, cocos2d::Vec2(-visibleSize.width, 0));
	shareButton->runAction(shareButtonMovingAction);

	shareButton->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Share();
		}
	});

	// The menu button //
	auto menuButton = cocos2d::ui::Button::create("sprites/ui/panels/gameover/menu_button_normal.png",
		"sprites/ui/panels/gameover/menu_button_click.png", "sprites/ui/panels/gameover/menu_button_click.png");
	menuButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width,
		shareButton->getPositionY() - shareButton->getContentSize().height - DISTANCE_BETWEEN_GAMEOVER_BUTTONS));
	scene->addChild(menuButton, 11);
	auto menuButtonMovingAction = cocos2d::MoveBy::create(1.1F, cocos2d::Vec2(-visibleSize.width, 0));
	menuButton->runAction(menuButtonMovingAction);

	menuButton->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Menu();
		}
	});

	// The try again button //
	auto tryAgainButton = cocos2d::ui::Button::create("sprites/ui/panels/gameover/try_again_button_normal.png",
		"sprites/ui/panels/gameover/try_again_button_click.png", "sprites/ui/panels/gameover/try_again_button_click.png");
	tryAgainButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width,
		menuButton->getPositionY() - menuButton->getContentSize().height - DISTANCE_BETWEEN_GAMEOVER_BUTTONS));
	scene->addChild(tryAgainButton, 11);
	auto tryAgainButtonMovingAction = cocos2d::MoveBy::create(1.3F, cocos2d::Vec2(-visibleSize.width, 0));
	tryAgainButton->runAction(tryAgainButtonMovingAction);

	tryAgainButton->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			TryAgain();
		}
	});
}

void GameOverPanel::Share()
{
	cocos2d::Application::getInstance()->openURL("http://www.gameloft.com/en/games");
}

void GameOverPanel::Menu()
{
	auto newScene = MenuScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
}

void GameOverPanel::TryAgain()
{
	auto newScene = GamePlayScene::createScene(GamePlayScene::sCurrentLevelIndex + 1);
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
}
