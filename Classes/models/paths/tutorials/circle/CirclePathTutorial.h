#pragma once

#include "cocos2d.h"

class CirclePathTutorial {
private:
    cocos2d::Sprite* mLayer;
	cocos2d::Sprite* mBalloonSprite;
	cocos2d::Sprite* mTouchEffectSprite;

	bool mIsTouching;
	bool mIsTouchingRight;
	float mCurrentAngle;
	float mCenterPositionX;
	float mCirclePathRadius;
	float mPathPositionY;

public:
	CirclePathTutorial(cocos2d::Scene* scene);
	
	/**
	* Show firgure on the left side
	*/
	void ShowFigureLeft();

	/**
	* Show firgure on the right side
	*/
	void ShowFigureRight();

	/**
	* Update every single frame
	*/
	void Update();
};
