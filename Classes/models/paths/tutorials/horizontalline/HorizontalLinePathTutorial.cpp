#include "HorizontalLinePathTutorial.h"

#include "ui/CocosGUI.h"

HorizontalLinePathTutorial::HorizontalLinePathTutorial(cocos2d::Scene *scene) {
    
	/*Set local data*/
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	mCenterPositionX = visibleSize.width / 2;
	mIsTouching = false;
	mPathPositionY = 200;

	/*create Sprite*/
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
	auto horizontalLineSprite = cocos2d::Sprite::create("sprites/gameplay/paths/horizontal_line_path.png");
	
	horizontalLineSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, mPathPositionY));
	mBalloonSprite->setPosition(visibleSize.width / 2, horizontalLineSprite->getPositionY());

	mLayer->addChild(touchSprite);
	mLayer->addChild(mTouchEffectSprite);

	scene->addChild(horizontalLineSprite);
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
			mTouchEffectSprite->setVisible(false);
			mIsTouching = true;
			ShowFigureLeft();
	}), 
		cocos2d::DelayTime::create(1.5),
		cocos2d::CallFunc::create([=]() {
			mTouchEffectSprite->setVisible(false);
			ShowFigureRight();
	}),
		cocos2d::DelayTime::create(1.5),
	nullptr);

	mLayer->runAction(cocos2d::RepeatForever::create(changeTouchPositionSeq));
}

void HorizontalLinePathTutorial::ShowFigureLeft()
{
	mIsTouchingRight = false;
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(-150, 0));
}

void HorizontalLinePathTutorial::ShowFigureRight()
{
	mIsTouchingRight = true;
	mTouchEffectSprite->setVisible(true);
	mLayer->setPosition(cocos2d::Vec2(150, 0));
}

void HorizontalLinePathTutorial::Update()
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
