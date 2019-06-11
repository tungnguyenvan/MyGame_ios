#pragma once

#include "../../../../models/objects/other/level8and9/Creator.h"
#include "../../../../models/objects/obstacles/level8/core/CoreObstacle.h"
#include "../../../../models/paths/verticalline/VerticalLinePath.h"

#include "cocos2d.h"

class ObstaclesCreation : public Creator<CoreObstacle>
{
private:
	bool mHasReleasedAnObstacleOnTheRightSide;
	bool mHasChangeFrameCount;

	CoreObstacle* GetAnInactiveObject(const int& mapIndex) override;

public:
	ObstaclesCreation(cocos2d::Scene* scene);
	  
	void DisappearActiveObjects() override;

	/**
	 * Update every single frame
	 */
	void Update(const Stage& mStage);
};
