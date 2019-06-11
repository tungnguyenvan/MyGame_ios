#pragma once

#include "../../../../models/objects/obstacles/level9/core/CoreDestroyer.h"

#include "cocos2d.h"

class Archer : public CoreDestroyer
{
private: 
	void PlayAnimation();

public:
	Archer(cocos2d::Scene* scene, const float& travelingSpeed, const cocos2d::Vec2& DepartingPosition);
	 
	void Update(const cocos2d::Vec2& balloonPosition) override;
};
