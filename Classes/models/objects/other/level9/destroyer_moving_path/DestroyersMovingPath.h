#pragma once

#include "cocos2d.h"

class DestroyersMovingPath
{
private:
	cocos2d::Sprite* mLeftMovingPath1Sprite;
	cocos2d::Sprite* mLeftMovingPath2Sprite;
	cocos2d::Sprite* mCenterMovingPath1Sprite;
	cocos2d::Sprite* mCenterMovingPath2Sprite;
	cocos2d::Sprite* mRightMovingPath1Sprite;
	cocos2d::Sprite* mRightMovingPath2Sprite;

public:
	DestroyersMovingPath(cocos2d::Scene* scene);

	/**
	 * Return the position of the path based on the direction
	 * @return cocos2d::Vec2
	 */
	cocos2d::Vec2 GetThePosition(const bool& isOnTheLeft);

	/**
	 * Make all of the sprites to be disappear from the scene
	 */
	void StopMoving();

	/**
	 * Update every single frame
	 */
	void Update();
};
