#pragma once

#include "../../../models/paths/core/CorePath.h"

#include "cocos2d.h"

 class SquarePath : public CorePath
 {
 private:
	 cocos2d::Vec2 mTouchLocation;
	 cocos2d::Vec2 mPoint1;
	 cocos2d::Vec2 mPoint2;
	 cocos2d::Vec2 mPoint3;
	 cocos2d::Vec2 mPoint4;

	 int mLength;
	 int mDirection;

	 /*Change variables here to fit your needs*/	 
	 int mSquareWidthSize; // corresponding to your picture's width and height
	 int mSquareHeightSize; // corresponding to your picture's width and height
	 /**************************************/

	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

 public:
	 SquarePath(cocos2d::Scene* scene, const int& squareWidthSize, 
		 const std::string& pathNamePath, const std::string& balloonNamePath,
		 const float& pathPositionY, const float& ballooonMovingSpeed);

	 /**
	 *change the balloon direction when it's moving clockwise
	 *
	 */
	 void ClockwiseDirection();

	 /**
	 *change the balloon direction when it's moving counter clockwise
	 *
	 */
	 void CounterClockwiseDirection();

	 /**
	 *move the balloon
	 *
	 */
	 void moveBalloon(int speed);
	
	/**
	 *  Update every single frame
	 */
	 void Update() override; 
 };
