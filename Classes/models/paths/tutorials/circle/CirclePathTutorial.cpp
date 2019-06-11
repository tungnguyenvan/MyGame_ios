#include "CirclePathTutorial.h"

#include "ui/CocosGUI.h"

CirclePathTutorial::CirclePathTutorial(cocos2d::Scene *scene) {
    
	/*Set local data*/
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	mCurrentAngle = 90.0F;
	mCenterPositionX = visibleSize.width / 2;
	mIsTouching = false;
	mCirclePathRadius = 100;
	mPathPositionY = 200;

	/*Create sprite and set position for them*/
    mLayer = cocos2d::Sprite::create();
    mLayer->setAnchorPoint(cocos2d::Vec2(0, 0));

    auto backgroudSprite = cocos2d::Sprite::create("sprites/gameplay/level5/background.png");
	backgroudSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	scene->addChild(backgroudSprite);

    auto touchSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/figure.png");
    touchSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, touchSprite->getContentSize().height));

    mTouchEffectSprite = cocos2d::Sprite::create("sprites/gameplay/tutorial/touch_effect.png");
	mTouchEffectSprite->setPosition(touchSprite->getPosition() + cocos2d::Vec2(- 17, touchSprite->getContentSize().height / 2 + 20));
	mTouchEffectSprite->setVisible(false);

	mBalloonSprite = cocos2d::Sprite::create("sprites/gameplay/balloon/balloon.png");
	auto circleLineSprite = cocos2d::Sprite::create("sprites/gameplay/level3/circle/circle_path.png");
	
	circleLineSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, mPathPositionY));
	mBalloonSprite->setPosition(visibleSize.width / 2, circleLineSprite->getContentSize().height / 2 + circleLineSprite->getPositionY());

	mLayer->addChild(touchSprite);
	mLayer->addChild(mTouchEffectSprite);

	scene->addChild(circleLineSprite);
	scene->addChild(mBalloonSprite);
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

	/*change toch position sequence*/
	auto changeTouchPositionSeq = cocos2d::Sequence::create(
		cocos2d::CallFunc::create([=]() {
			mTouchEffectSprite->setVisible(false);
			mIsTouching = true;
			ShowFigureLeft();
	}), 
		cocos2d::DelayTime::create(3),
		cocos2d::CallFunc::create([=]() {
			mTouchEffectSprite->setVisible(false);
			ShowFigureRight();
	}),
		cocos2d::DelayTime::create(3),
	nullptr);

	mLayer->runAction(cocos2d::RepeatForever::create(changeTouchPositionSeq));
}

void CirclePathTutorial::ShowFigureLeft()
{
	mIsTouchingRight = false;
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(-150, 0));
}

void CirclePathTutorial::ShowFigureRight()
{
	mIsTouchingRight = true;
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(150, 0));
}

void CirclePathTutorial::Update()
{
	if (mIsTouching)
	{
		if (mIsTouchingRight)
			mCurrentAngle -= 2;
		else
			mCurrentAngle += 2;

		mBalloonSprite->setPosition(mCenterPositionX + cos(mCurrentAngle * M_PI / 180.0F) * mCirclePathRadius,
			mPathPositionY + sin(mCurrentAngle * M_PI / 180.0F) * mCirclePathRadius);
	}
}
