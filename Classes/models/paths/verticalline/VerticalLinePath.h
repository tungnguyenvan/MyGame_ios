#pragma once

#include "../../../models/paths/core/CorePath.h"

#include "cocos2d.h"
 
enum Stage
{
	STAGE_1_MOVE_DOWN,
	STAGE_2_IDLE,
	STAGE_2_IDLE_AGAIN,
	STAGE_3_MOVE_UP,
	STAGE_4_IDLE,
	STAGE_4_IDLE_AGAIN,
	STAGE_5_MOVE_UP_AND_DOWN,
	STAGE_6_IDLE,
	STAGE_7_MOVE_ARBITRARY,
	STAGE_8_DISAPPEAR,
	DONE
};
 
class VerticalLinePath : public CorePath
{
private:
	bool mIsMovingDown; 
	int mFrameCount;
	Stage mCurrentStage;

	/* Change variables here to fit your needs */
	float mDistanceBetweenBaloonAndThePath; // Corresponding to your picture's width and height
	float mPathMovingSpeed;
	float mThresholdMovingDistance;
	/*******************************************/

	/**
	 *  Move the path with pre-defined directions
	 */
	void MoveThePath();

	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

public:
	VerticalLinePath(cocos2d::Scene* scene, const float& distanceBetweenBaloonAndThePath,
		const float& pathMovingSpeed, const float& thresholdMovingDistance,
		const std::string& balloonNamePath, const std::string& pathNamePath,
		const float& pathPositionY);

	/**
	 *  Update every single frame
	 */
	void Update() override;

	/**
	* Get the current stage of the path
	* @return Stage
	*/
	Stage GetTheCurrentStage();

	/**
	* Stop all operations when the balloon is exploded
	*/ 
	void Disappear() override;
};
