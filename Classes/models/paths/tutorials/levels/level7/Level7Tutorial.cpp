#include "Level7Tutorial.h"
#include "../../../../../common/definitionlevels/DefinitionLevel7.h"

#include "ui/CocosGUI.h"

Level7Tutorial::Level7Tutorial(cocos2d::Scene *scene) {
    
	/*Set local data*/
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	/*Create sprite and set position for them*/
    mLayer = cocos2d::Sprite::create();
    mLayer->setAnchorPoint(cocos2d::Vec2(0, 0));

    auto backgroudSprite = cocos2d::Sprite::create("sprites/gameplay/level5/background.png");
	backgroudSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->addChild(backgroudSprite, -1);

    auto touchSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/figure.png");
    touchSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, touchSprite->getContentSize().height));

    mTouchEffectSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/touch_effect.png");
	mTouchEffectSprite->setPosition(touchSprite->getPosition() + cocos2d::Vec2(- 17, touchSprite->getContentSize().height / 2 + 20));
	mTouchEffectSprite->setVisible(false);

	/* circle line*/
	InitCircleLine();

	mCircleLineSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));

	/*barrier*/
	auto barrierSprite = cocos2d::Sprite::create(BARRIER_GREEN_OBSTACLE_PATH);
	
	barrierSprite->setPosition(cocos2d::Vec2(barrierSprite->getContentSize().width / 2, 
		visibleSize.height + BARRIER_OFFSET));

	mLayer->setVisible(false);
	mLayer->addChild(touchSprite);
	mLayer->addChild(mTouchEffectSprite);

	scene->addChild(barrierSprite);
	scene->addChild(mCircleLineSprite);
	scene->addChild(mLayer);

	/*Button to skip the tutorial*/
	auto skipButton = cocos2d::ui::Button::create("sprites/gameplay/tutorial/button_skip.png");
	skipButton->setPosition(cocos2d::Vec2(visibleSize.width - skipButton->getContentSize().width / 2, visibleSize.height - skipButton->getContentSize().height / 2));
	scene->addChild(skipButton);

	skipButton->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			// scene transition
			break;
		}
	});

	/* Tutorial sequence */
	auto tutorialSeq = cocos2d::Sequence::create(	
		/*move barrier*/
		cocos2d::CallFunc::create([=]() {
			barrierSprite->setVisible(true);
			barrierSprite->runAction(cocos2d::MoveTo::create(2, cocos2d::Vec2(0, 600)));
	}), cocos2d::DelayTime::create(2),
		
		/*show figure*/
		cocos2d::CallFunc::create([=]() {
			ShowFigureRight();
	}), cocos2d::DelayTime::create(0.5),
		
		/*rotate circle*/
		cocos2d::CallFunc::create([=]() {
			mCircleLineSprite->runAction(cocos2d::RotateTo::create(1, 90));
	}), cocos2d::DelayTime::create(1),
		
		/*remove touch*/
		cocos2d::CallFunc::create([=]() {
		mLayer->setVisible(false);
	}), cocos2d::DelayTime::create(1),

		/*move barrier*/
		cocos2d::CallFunc::create([=]() {
			barrierSprite->runAction(cocos2d::MoveTo::create(1, cocos2d::Vec2(0, 490)));
	}), cocos2d::DelayTime::create(1),

		/*remove barrier*/
		cocos2d::CallFunc::create([=]() {
		barrierSprite->setVisible(false);
	}), cocos2d::DelayTime::create(1),

		/*restore tutorial*/
		cocos2d::CallFunc::create([=]() {
		barrierSprite->setPosition(cocos2d::Vec2(barrierSprite->getContentSize().width / 2,
			visibleSize.height + BARRIER_OFFSET));
		mCircleLineSprite->setRotation(-90);
	}), cocos2d::DelayTime::create(1),
		nullptr);


	scene->runAction(cocos2d::RepeatForever::create(tutorialSeq));
}

void Level7Tutorial::InitCircleLine()
{
	mCircleLineSprite = cocos2d::Sprite::create(CIRCLE_LINE_PATH);

	auto sprite = cocos2d::Sprite::create(BALLOON_BLUE_PATH);
	auto sprite1 = cocos2d::Sprite::create(BALLOON_RED_PATH);
	auto sprite2 = cocos2d::Sprite::create(BALLOON_GREEN_PATH);
	auto sprite3 = cocos2d::Sprite::create(BALLOON_YELLOW_PATH);

	mCircleObstacleModels.push_back(sprite);
	mCircleObstacleModels.push_back(sprite1);
	mCircleObstacleModels.push_back(sprite2);
	mCircleObstacleModels.push_back(sprite3);

	mCircleLineSprite->addChild(sprite);
	mCircleLineSprite->addChild(sprite1);
	mCircleLineSprite->addChild(sprite2);
	mCircleLineSprite->addChild(sprite3);

	InitPositionCircleObstacleModels();
}

void Level7Tutorial::InitPositionCircleObstacleModels()
{
	float radius = mCircleLineSprite->getContentSize().width / 2;
	float corner = 0;

	for (int i = 0; i < mCircleObstacleModels.size(); i++)
	{
		mCircleObstacleModels.at(i)->setPosition(radius + cos(corner * M_PI / 180.0F) * radius,
			radius + sin(corner * M_PI / 180.0F) * radius);
		corner += 360 / mCircleObstacleModels.size();
	}
}

void Level7Tutorial::ShowFigureRight()
{
	mLayer->setVisible(true);
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(150, 0));
}
