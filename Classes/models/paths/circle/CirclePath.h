#pragma once

#include "../../../models/paths/core/CorePath.h"

#include "cocos2d.h"

class CirclePath : public CorePath
{
private: 
	float mCurrentAngle;
	float mCenterPositionX;

	/* Change variables here to fit your needs */ 
	float mCirclePathRadius; // Corresponding to your picture's width and height
	/*******************************************/

	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

public:
	CirclePath(cocos2d::Scene* scene, const float& circlePathRadius,
	const std::string& balloonNamePath, const std::string& pathNamePath,
	const float& pathPositionY, const float& ballooonMovingSpeed);

	void TurnOffPhysics();

	/**
	 *  Update every single frame
	 */ 
	void Update() override;

	/**
	 * Get the balloon's current position
	 * @return cocos2d::Vec2 
	 */
	cocos2d::Vec2 GetTheBalloonPosition();
};
