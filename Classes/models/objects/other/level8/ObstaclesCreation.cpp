#include "ObstaclesCreation.h"
#include "../../../../models/objects/obstacles/level8/Bar.h"
#include "../../../../models/objects/obstacles/level8/Spike.h"
#include "../../../../models/objects/obstacles/level8/Boom.h"
#include "../../../../models/objects/obstacles/level8/Rock.h"
#include "../../../../common/Definition.h"
#include "../../../../common/definitionlevels/DefinitionLevel8.h"
#include "../../../../common/definitionpaths/verticalline/DefinitionVerticalLine.h";

ObstaclesCreation::ObstaclesCreation(cocos2d::Scene* scene) : Creator()
{
	// Set local data //
	mHasReleasedAnObstacleOnTheRightSide = true;
	mHasChangeFrameCount = false;

	// Create initial obstacles and store it in the map // 
	for (int i = 0; i < NUMBER_OF_INTIAL_OBSTACLES_PER_TYPE; i++)
	{
		mMapOfObjects[0].push_back(new Bar(scene, 2));
		mMapOfObjects[1].push_back(new Spike(scene, 2));
		mMapOfObjects[2].push_back(new Boom(scene, 2));
		mMapOfObjects[3].push_back(new Rock(scene, 2));
	}
}

CoreObstacle* ObstaclesCreation::GetAnInactiveObject(const int& mapIndex)
{
	for (int i = 0; i < mMapOfObjects[mapIndex].size(); i++)
	{
		if (!mMapOfObjects[mapIndex].at(i)->IsActive())
			return mMapOfObjects[mapIndex].at(i);
	}

	return nullptr;
}

void ObstaclesCreation::DisappearActiveObjects()
{
	std::vector<CoreObstacle*> vectorOfActiveObjects;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < mMapOfObjects[i].size(); j++)
		{
			if (mMapOfObjects[i].at(j)->IsActive())
				vectorOfActiveObjects.push_back(mMapOfObjects[i].at(j));
		}
	}

	// Make the objects disappear// 
	for (int i = 0; i < vectorOfActiveObjects.size(); i++)
	{
		vectorOfActiveObjects[i]->Disappear();
	}
}

void ObstaclesCreation::Update(const Stage& mStage)
{
	mFrameCount++;

	// On stage 2: Make some obstacles move downwards (Bar Obstacles) //
	if (mStage == STAGE_2_IDLE)
	{
		if (mFrameCount % OBSTACLES_SPAWNING_STAGE_2_FRAME_COUNT == 0)
		{
			CoreObstacle* obstacle = GetAnInactiveObject(0);

			if (obstacle != nullptr)
			{
				obstacle->StartTraveling(mHasReleasedAnObstacleOnTheRightSide);

				mHasReleasedAnObstacleOnTheRightSide = !mHasReleasedAnObstacleOnTheRightSide;

				mFrameCount += int((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_2)) * TIME_RUNNING_STAGE_2);
			}
		}
	}
	// On stage 4: Make some obstacles move upwards (Spike Obstacles) //
	else if (mStage == STAGE_4_IDLE)
	{
		// Trick: Reset frame count to 0
		if (!mHasChangeFrameCount)
		{
			mFrameCount = 0;
			mHasChangeFrameCount = true;
		}

		if (mFrameCount % OBSTACLES_SPAWNING_STAGE_4_FRAME_COUNT == 0)
		{
			CoreObstacle* obstacle = GetAnInactiveObject(1);

			if (obstacle != nullptr)
			{
				obstacle->StartTraveling(mHasReleasedAnObstacleOnTheRightSide);

				mHasReleasedAnObstacleOnTheRightSide = !mHasReleasedAnObstacleOnTheRightSide;

				mFrameCount += int((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_4)) * TIME_RUNNING_STAGE_4);
			}
		}
	}
	// On stage 5: Make some obstacles move up and down (Boom Obstacles) //
	else if (mStage == STAGE_5_MOVE_UP_AND_DOWN)
	{
		// Trick: Reset frame count to 0
		if (mHasChangeFrameCount)
		{
			mFrameCount = 0;
			mHasChangeFrameCount = false;
		}

		if (mFrameCount % OBSTACLES_SPAWNING_STAGE_5_FRAME_COUNT == 0)
		{
			CoreObstacle* obstacle = GetAnInactiveObject(2);

			if (obstacle != nullptr)
			{
				obstacle->StartTraveling(mHasReleasedAnObstacleOnTheRightSide);

				mHasReleasedAnObstacleOnTheRightSide = !mHasReleasedAnObstacleOnTheRightSide;

				mFrameCount += int((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_5)) * TIME_RUNNING_STAGE_5);
			}
		}
	}
	// On stage 7: Make some obstacles move arbitrarily (Rock Obstacles) //
	else if (mStage == STAGE_7_MOVE_ARBITRARY)
	{
		// Trick: Reset frame count to 0
		if (!mHasChangeFrameCount)
		{
			mFrameCount = 0;
			mHasChangeFrameCount = true;
		}

		if (mFrameCount % OBSTACLES_SPAWNING_STAGE_6_FRAME_COUNT == 0)
		{
			CoreObstacle* obstacle = GetAnInactiveObject(3);

			if (obstacle != nullptr)
			{
				obstacle->StartTraveling(mHasReleasedAnObstacleOnTheRightSide);

				mHasReleasedAnObstacleOnTheRightSide = !mHasReleasedAnObstacleOnTheRightSide;

				mFrameCount += int((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_7)) * TIME_RUNNING_STAGE_7);
			}
		}
	}
}
