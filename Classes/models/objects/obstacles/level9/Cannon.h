#pragma once

#include "../../../../models/objects/obstacles/level9/core/CoreDestroyer.h"

#include "cocos2d.h"

class Cannon : public CoreDestroyer
{
public:
	Cannon(cocos2d::Scene* scene, const float& travelingSpeed, const cocos2d::Vec2& DepartingPosition, const bool& isDepartingOnTheRight);
	 
	void Update(const cocos2d::Vec2& balloonPosition) override;
};
