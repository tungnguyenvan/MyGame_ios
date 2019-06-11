#pragma once

#include "cocos2d.h"

class VerticalLinePathTutotial {
private:
    cocos2d::Sprite* mLayer;
	cocos2d::Sprite* mBalloonSprite;
	cocos2d::Sprite* mTouchEffectSprite;

	bool mIsTouching;
	bool mIsTouchingRight;
	float mCenterPositionX;
	float mPathPositionY;

public:
	VerticalLinePathTutotial(cocos2d::Scene* scene);
	
	/**
	* Show firgure left
	*/
	void ShowFigureLeft();

	/**
	* Show firgure right
	*/
	void ShowFigureRight();

	/**
	* Update every single frame
	*/
	void Update();
};
