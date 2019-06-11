#pragma once

#include <vector>

#include "../../../../models/objects/obstacles/level7/Barrier.h"

#include "cocos2d.h"

class BarriersCreation
{
private:
	std::vector<Barrier*> mBarriers;
	std::vector<Barrier*> mCounterBarriers;
	int mFrameCount;
	int mIndexListBarrier;
	int mMode;
	int mBarrierObstacleSpawnTime;

	/**
	 * Active barrier if not active
	 */
	void ActiveBarrier();

public:
	BarriersCreation(cocos2d::Scene* scene);

	/**
	* Get mode to check is completed level
	*/
	int GetMode();

	/**
	* Inactive barrier when it's game over or completed level
	*/
	void InactiveBarrier();

	/**
	 * Update every single frame
	 */
	void Update();
};
