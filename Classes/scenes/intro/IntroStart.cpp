#include "IntroStart.h"
#include "../../scenes/ui/menu/LevelsSelectionScene.h"
#include "../../common/DefinitionUI.h"
#include "../../utils/helper/Helper.h"

#include "ui/CocosGUI.h"

cocos2d::Scene* IntroStart::createScene()
{
	return IntroStart::create();
}

bool IntroStart::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// The animation intro initialization // 
	mFirstAnimationSprite = cocos2d::Sprite::create("sprites/ui/intro_scene/animation_frames/p1.png");
	mFirstAnimationSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(mFirstAnimationSprite, 0);
	mFirstAnimationSprite->setOpacity(SPRITES_MAX_OPACITY);

	mSecondAnimationSprite = cocos2d::Sprite::create("sprites/ui/intro_scene/animation_frames/p1.png");
	mSecondAnimationSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(mSecondAnimationSprite, 0);
	mSecondAnimationSprite->setOpacity(0);

	// The snow emitter //
	auto emitter = cocos2d::ParticleSnow::create();
	emitter->setPosition(origin.x + visibleSize.width / 2, visibleSize.height);
	emitter->setSpeed(100);
	this->addChild(emitter, 1);

	// The skip intro button //
	auto skipIntroButton = cocos2d::ui::Button::create("sprites/ui/intro_scene/buttons/skip_button_normal.png",
		"sprites/ui/intro_scene/buttons/skip_button_click.png", "sprites/ui/intro_scene/buttons/skip_button_click.png");
	skipIntroButton->setPosition(cocos2d::Vec2(skipIntroButton->getContentSize().width / 2, skipIntroButton->getContentSize().height / 2));
	this->addChild(skipIntroButton, 2);

	skipIntroButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			SkipIntro();
			break;
		default:
			break;
		}
	});

	// The animate next frame button //
	auto animateNextFrameButton = cocos2d::ui::Button::create("sprites/ui/intro_scene/buttons/next_button_normal.png",
		"sprites/ui/intro_scene/buttons/next_button_click.png", "sprites/ui/intro_scene/buttons/next_button_click.png");
	animateNextFrameButton->setPosition(cocos2d::Vec2(visibleSize.width
		- animateNextFrameButton->getContentSize().width / 2, animateNextFrameButton->getContentSize().height / 2));
	this->addChild(animateNextFrameButton, 2);

	animateNextFrameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			AnimateNextFrame();
			break;
		default:
			break;
		}
	});

	// Set local data //
	mAnimationFramesNames = Helper::GetAVectorOfAnimationFramesNames("sprites/ui/intro_scene/animation_frames/p%d.png",
		NUMBER_OF_ANIMATION_FRAMES_INTRO);

	mAnimationCurrentFrameIndex = 0;

	return true;
}

void IntroStart::AnimateNextFrame()
{
	// Change the sprites //
	mFirstAnimationSprite->setSpriteFrame(cocos2d::SpriteFrame::create(mAnimationFramesNames[mAnimationCurrentFrameIndex],
		cocos2d::Rect(0, 0, mFirstAnimationSprite->getContentSize().width, mFirstAnimationSprite->getContentSize().height)));
	mSecondAnimationSprite->setSpriteFrame(cocos2d::SpriteFrame::create(mAnimationFramesNames[mAnimationCurrentFrameIndex + 1],
		cocos2d::Rect(0, 0, mSecondAnimationSprite->getContentSize().width, mSecondAnimationSprite->getContentSize().height)));

	mFirstAnimationSprite->setOpacity(SPRITES_MAX_OPACITY);
	mSecondAnimationSprite->setOpacity(0);

	auto fadeOutAction = cocos2d::FadeOut::create(ANIMATION_TIME_FOR_ONE_CHANGE);
	auto fadeInAction = cocos2d::FadeIn::create(ANIMATION_TIME_FOR_ONE_CHANGE);

	mFirstAnimationSprite->runAction(fadeOutAction);
	mSecondAnimationSprite->runAction(fadeInAction);

	mAnimationCurrentFrameIndex++;

	// If all of the animation frames have been projected, open the levels selection scene //
	if (mAnimationCurrentFrameIndex == mAnimationFramesNames.size() - 1)
	{
		auto newScene = LevelsSelectionScene::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
	}
}

void IntroStart::SkipIntro()
{
	Helper::SkipTheIntroScene();

	auto newScene = LevelsSelectionScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_TIME, newScene));
}
