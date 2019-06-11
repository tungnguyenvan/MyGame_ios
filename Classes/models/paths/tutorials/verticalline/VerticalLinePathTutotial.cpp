#include "VerticalLinePathTutotial.h"

#include "ui/CocosGUI.h"

VerticalLinePathTutotial::VerticalLinePathTutotial(cocos2d::Scene *scene) {
    
	/*Set local data*/
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	mCenterPositionX = visibleSize.width / 2;
	mIsTouching = false;
	mPathPositionY = 200;

	/*create Sprite*/
    mLayer = cocos2d::Sprite::create();
    mLayer->setAnchorPoint(cocos2d::Vec2(0, 0));

    auto backgroudSprite = cocos2d::Sprite::create("sprites/gameplay/level8/background.png");
	backgroudSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->addChild(backgroudSprite);

    auto touchSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/figure.png");
    touchSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, touchSprite->getContentSize().height));

    mTouchEffectSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/touch_effect.png");
	mTouchEffectSprite->setPosition(touchSprite->getPosition() + cocos2d::Vec2(- 17, touchSprite->getContentSize().height / 2 + 20));
	mTouchEffectSprite->setVisible(false);

	mBalloonSprite = cocos2d::Sprite::create("sprites/gameplay/level8/balloon.png");
	auto verticalLineSprite = cocos2d::Sprite::create("sprites/gameplay/level8/vertical_line.png");
	
	verticalLineSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, 0));
	mBalloonSprite->setPosition(cocos2d::Vec2(
		verticalLineSprite->getPositionX() + mBalloonSprite->getContentSize().width / 2, 300));

	mLayer->addChild(touchSprite);
	mLayer->addChild(mTouchEffectSprite);
	mLayer->setVisible(false);

	scene->addChild(verticalLineSprite);
	scene->addChild(mBalloonSprite);
	scene->addChild(mLayer);

	/*Button skipp*/
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
	
	/*tutorial sequence*/
	auto changeTouchPositionSeq = cocos2d::Sequence::create(
		cocos2d::CallFunc::create([=]() {
			mLayer->setVisible(true);
			mTouchEffectSprite->setVisible(false);
			ShowFigureLeft();
			mBalloonSprite->setPosition(cocos2d::Vec2(
				verticalLineSprite->getPositionX() - mBalloonSprite->getContentSize().width / 2, 300));
	}), 
		cocos2d::DelayTime::create(1.5),
		cocos2d::CallFunc::create([=]() {
			mTouchEffectSprite->setVisible(false);
			ShowFigureRight();
			mBalloonSprite->setPosition(cocos2d::Vec2(
				verticalLineSprite->getPositionX() + mBalloonSprite->getContentSize().width / 2, 300));
	}),
		cocos2d::DelayTime::create(1.5),
	nullptr);

	mLayer->runAction(cocos2d::RepeatForever::create(changeTouchPositionSeq));
}

void VerticalLinePathTutotial::ShowFigureLeft()
{
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(-150, 0));
}

void VerticalLinePathTutotial::ShowFigureRight()
{
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(150, 0));
}

void VerticalLinePathTutotial::Update()
{
	if (mIsTouching)
	{
		if (mIsTouchingRight)
		{
			mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() + 1,
				mBalloonSprite->getPositionY()));
		}
		else
		{
			mBalloonSprite->setPosition(cocos2d::Vec2(mBalloonSprite->getPositionX() - 1,
				mBalloonSprite->getPositionY()));
		}
	}
}
