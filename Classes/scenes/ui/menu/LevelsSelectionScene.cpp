#include "LevelsSelectionScene.h"
#include "../../../scenes/gameplay/GamePlayScene.h"
#include "../../../scenes/ui/menu/MenuScene.h"
#include "../../../common/DefinitionUI.h"
#include "../../../utils/helper/Helper.h"

#include "ui/CocosGUI.h"

cocos2d::Scene* LevelsSelectionScene::createScene()
{
	return LevelsSelectionScene::create();
}

bool LevelsSelectionScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The background sprite //
	auto backgroundMenuSprite = cocos2d::Sprite::create("sprites/ui/levels_selection_scene/f1.png");
	backgroundMenuSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backgroundMenuSprite, 0);

	// Hack Trick open all levels button  //
	auto openAllLevelsButton = cocos2d::ui::Button::create("sprites/ui/levels_selection_scene/open_all_level_button.png",
		"sprites/ui/levels_selection_scene/open_all_level_button.png", "sprites/ui/levels_selection_scene/open_all_level_button.png");
	openAllLevelsButton->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2,
			visibleSize.height - openAllLevelsButton->getContentSize().height/2));
	this->addChild(openAllLevelsButton, 1);

	openAllLevelsButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				mCount++;
				if(mCount == 5)
				{
					mCount = 0;

					// Open all levels //
					GamePlayScene::sCurrentLevelIndex = 4;
					Helper::SetTheCurrentPassedLevelIndex();

					// Open the levels selection scene again //
					auto newScene = LevelsSelectionScene::createScene();
					cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
				}
				break;
			default:
				break;
		}
	});


	// The levels scrollview //
	auto levelsScrollView = cocos2d::ui::ScrollView::create();
	levelsScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
	levelsScrollView->setContentSize(cocos2d::Size(visibleSize.width, LEVELS_SCROLLVIEW_HEIGHT));
	levelsScrollView->setInnerContainerSize(cocos2d::Size(LEVEL_BUTTONS_WIDTH * (NUMBER_OF_LEVELS + 1), 0));
	levelsScrollView->setBounceEnabled(true);
	levelsScrollView->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));
	levelsScrollView->setScrollBarOpacity(0);
	levelsScrollView->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2
		+ LEVELS_SCROLL_VIEW_OFFSET_CENTER_SCREEN));
	this->addChild(levelsScrollView, 1);

	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		char normalForm[LEVEL_BUTTONS_PATH_MAX_CHARS];
		char clickForm[LEVEL_BUTTONS_PATH_MAX_CHARS];

		sprintf(normalForm, "sprites/ui/levels_selection_scene/normal_level_buttons/l%d.png", i + 1);
		sprintf(clickForm, "sprites/ui/levels_selection_scene/click_level_buttons/l%d.png", i + 1);

		// The level name label //
		auto levelNameLabel = cocos2d::Label::createWithTTF(Helper::GetTheLevelNameBasedOnTheIndex(i),
			"fonts/AvenirLTStd-Heavy.otf", LEVEL_NAME_FONT_SIZE);
		levelNameLabel->setPosition(cocos2d::Vec2(i * LEVEL_BUTTONS_WIDTH + LEVEL_BUTTONS_WIDTH,
			levelsScrollView->getContentSize().height - levelNameLabel->getContentSize().height/2));
		levelsScrollView->addChild(levelNameLabel, 1);
		
		// The button //
		auto levelButton = cocos2d::ui::Button::create(normalForm, clickForm, clickForm);
		levelButton->setPosition(cocos2d::Vec2(i * LEVEL_BUTTONS_WIDTH + LEVEL_BUTTONS_WIDTH,
			levelsScrollView->getContentSize().height / 2));
		levelsScrollView->addChild(levelButton, 1);

		// The level description label //
		auto levelDescriptionLabel = cocos2d::Label::createWithTTF(Helper::GetTheLevelDescriptionBasedOnTheIndex(i),
			"fonts/AvenirLTStd-Heavy.otf", LEVEL_DESCRIPTION_FONT_SIZE);
		levelDescriptionLabel->setPosition(cocos2d::Vec2(i * LEVEL_BUTTONS_WIDTH + LEVEL_BUTTONS_WIDTH,
			  levelDescriptionLabel->getContentSize().height / 2));
		levelsScrollView->addChild(levelDescriptionLabel, 1);

		// The level locking handler //
		if (i > Helper::GetTheCurrentPassedLevelIndex())
		{
			auto lockSprite = cocos2d::Sprite::create("sprites/ui/levels_selection_scene/lock_level_buttons/lock.png");
			lockSprite->setPosition(levelButton->getPosition());
			levelsScrollView->addChild(lockSprite, 2);
			levelButton->setTouchEnabled(false);
		}

		levelButton->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				OpenGamePlayScene(i + 1);
				break;
			}
		});
	}

	// The go back button //
	auto goBackButton = cocos2d::ui::Button::create("sprites/ui/levels_selection_scene/back_button_normal.png",
		"sprites/ui/levels_selection_scene/back_button_click.png", "sprites/ui/levels_selection_scene/back_button_click.png");
	goBackButton->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2,
		goBackButton->getContentSize().height/2 + GO_BACK_BUTTON_OFFSET_BOTTOM_SCREEN));
	this->addChild(goBackButton, 1);

	goBackButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			GoBackToMenuScene();
			break;
		default:
			break;
		}
	});

	return true;
}

void LevelsSelectionScene::OpenGamePlayScene(const int& levelIndex)
{
	auto newScene = GamePlayScene::createScene(levelIndex);
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
}

void LevelsSelectionScene::GoBackToMenuScene()
{
	auto newScene = MenuScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
}
