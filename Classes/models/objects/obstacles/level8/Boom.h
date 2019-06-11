#pragma once

#include "../../../../models/objects/obstacles/level8/core/CoreObstacle.h"

#include "cocos2d.h"

class Boom : public CoreObstacle
{
public:
	Boom(cocos2d::Scene* scene, const float& travelingDuration);

	void StartTraveling(const bool& startOnTheRightSide) override;
};
