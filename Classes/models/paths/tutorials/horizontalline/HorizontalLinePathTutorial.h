#pragma once

#include "cocos2d.h"

class HorizontalLinePathTutorial {
private:
    cocos2d::Sprite* mLayer;
	cocos2d::Sprite* mBalloonSprite;
	cocos2d::Sprite* mTouchEffectSprite;

	bool mIsTouching;
	bool mIsTouchingRight;
	float mCenterPositionX;
	float mPathPositionY;

	/**
	* Show firgure left
	*/
	void ShowFigureLeft();

	/**
	* Show firgure right
	*/
	void ShowFigureRight();

public:
	HorizontalLinePathTutorial(cocos2d::Scene* scene);
	
	/**
	* Update every single frame
	*/
	void Update();
};
