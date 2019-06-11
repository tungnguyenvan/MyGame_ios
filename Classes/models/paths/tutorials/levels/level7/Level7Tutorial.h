#pragma once

#include "../../../../../models/objects/obstacles/level3/circle/CircleObstacleModel.h"

#include <vector>

#include "cocos2d.h"

class Level7Tutorial {
private:
    cocos2d::Sprite* mLayer;
	cocos2d::Sprite* mTouchEffectSprite;
	cocos2d::Sprite* mCircleLineSprite;
	std::vector<cocos2d::Sprite*> mCircleObstacleModels;

	/**
	* Create circle line with 4 balloon
	*/
	void InitCircleLine();
	
	/**
	* Set Position for each balloon
	*/
	void InitPositionCircleObstacleModels();

	/**
	* Show firgure on the right side
	*/
	void ShowFigureRight();

public:
	Level7Tutorial(cocos2d::Scene* scene);
};
