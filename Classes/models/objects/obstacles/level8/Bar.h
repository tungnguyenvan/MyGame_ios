#pragma once

#include "../../../../models/objects/obstacles/level8/core/CoreObstacle.h"

#include "cocos2d.h"

class Bar : public CoreObstacle
{
public:
	Bar(cocos2d::Scene* scene, const float& travelingDuration);

	void StartTraveling(const bool& startOnTheRightSide) override;
};
