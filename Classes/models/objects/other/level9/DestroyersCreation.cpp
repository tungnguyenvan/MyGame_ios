#include "DestroyersCreation.h"
#include "../../../../models/objects/obstacles/level9/Shooter.h"
#include "../../../../models/objects/obstacles/level9/Archer.h"
#include "../../../../models/objects/obstacles/level9/Cannon.h"
#include "../../../../common/Definition.h"
#include "../../../../common/definitionlevels/DefinitionLevel9.h"

DestroyersCreation::DestroyersCreation(cocos2d::Scene* scene) : Creator()
{
	// Create the moving path lied under the destroyers //
	mDestroyersMovingPath = new DestroyersMovingPath(scene);

	// Set default creation stage //
	mCreationStage = CREATION_STAGE_1;


	// Keep track of departing position side //
    bool isDeparting;

	// Create initial destroyers and store it in the map // 
	for (int i = 0; i < NUMBER_OF_INTIAL_DESTROYERS_PER_TYPE; i++)
	{
        isDeparting = cocos2d::random(1, 2) % 2 == 0;

		// Shooters //
		mMapOfObjects[0].push_back(new Shooter(scene, 3.0F, isDeparting ?
			mDestroyersMovingPath->GetThePosition(true) :
			mDestroyersMovingPath->GetThePosition(false)));

		// Archers //
		mMapOfObjects[1].push_back(new Archer(scene, 2.5F, isDeparting ?
			mDestroyersMovingPath->GetThePosition(true) :
			mDestroyersMovingPath->GetThePosition(false)));

		// Cannons //
		mMapOfObjects[2].push_back(new Cannon(scene, 2.0F, isDeparting ?
			mDestroyersMovingPath->GetThePosition(true) :
			mDestroyersMovingPath->GetThePosition(false),isDeparting));
	}
}

CoreDestroyer* DestroyersCreation::GetAnInactiveObject(const int& mapIndex)
{
	for (int i = 0; i < mMapOfObjects[mapIndex].size(); i++)
	{
		if (!mMapOfObjects[mapIndex].at(i)->IsActive())
			return mMapOfObjects[mapIndex].at(i);
	}

	return nullptr;
}

CreationStage DestroyersCreation::GetCreationStage() const
{
	return mCreationStage;
}

void DestroyersCreation::DisappearActiveObjects()
{
	// Get a list of active destroyers in the scene //
	std::vector<CoreDestroyer*> vectorOfActiveObjects;

	for (int i = 0; i < 3; i++)
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

	// Stop moving the paths //
	mDestroyersMovingPath->StopMoving();
}

void DestroyersCreation::Update(const cocos2d::Vec2& balloonPosition)
{
	mFrameCount++;

	// On stage 1: Make some destroyers move downwards (Shooter Destroyers) //
	if (mCreationStage == CREATION_STAGE_1)
	{
		if (mFrameCount % DESTROYERS_SPAWNING_STAGE_1_FRAME_COUNT == 0)
		{
			// Get a shooter from the map and show it up //
			GetAnInactiveObject(0)->SetActive(true);

			mFrameCount += int(((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_1)) * TIME_RUNNING_STAGE_1)
				* FRAME_COUNT_MULTIPLIER);

			if (mFrameCount >= FPS * TIME_RUNNING_STAGE_1)
			{
				mFrameCount = 0;

				mCreationStage = CREATION_STAGE_2;
			}
		}
	}
	// On stage 2: Make some destroyers move downwards (Archer Destroyers) //
	else if (mCreationStage == CREATION_STAGE_2)
	{
		if (mFrameCount % DESTROYERS_SPAWNING_STAGE_2_FRAME_COUNT == 0)
		{
			// Get a archer from the map and show it up //
			GetAnInactiveObject(1)->SetActive(true);

			mFrameCount += int(((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_2)) * TIME_RUNNING_STAGE_2)
				* FRAME_COUNT_MULTIPLIER);

			if (mFrameCount >= FPS * TIME_RUNNING_STAGE_2)
			{
				mFrameCount = 0;

				mCreationStage = CREATION_STAGE_3;
			}
		}
	}
	// On stage 3: Make some destroyers move downwards (Cannon Destroyers) //
	else if (mCreationStage == CREATION_STAGE_3)
	{
		if (mFrameCount % DESTROYERS_SPAWNING_STAGE_3_FRAME_COUNT == 0)
		{
			// Get a cannon from the map and show it up //
			GetAnInactiveObject(2)->SetActive(true);

			mFrameCount += int(((float(mFrameCount) / (FPS * TIME_RUNNING_STAGE_3)) * TIME_RUNNING_STAGE_3)
				* FRAME_COUNT_MULTIPLIER);

			if (mFrameCount >= FPS * TIME_RUNNING_STAGE_3)
			{
				mFrameCount = 0;

				mCreationStage = CREATION_STAGE_IDLE;
			}
		}
	}
	// On stage done: Make all destroyers in the scene disappear //
	else if (mCreationStage == CREATION_STAGE_IDLE)
	{
		if(mFrameCount >= FPS * TIME_RUNNING_STAGE_IDLE)
		{
			DisappearActiveObjects();

			mCreationStage = CREATION_STAGE_DONE;
		}
	}

	// Update those active destroyers in the scene //
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < mMapOfObjects.at(i).size(); j++)
		{
			if (mMapOfObjects.at(i).at(j)->IsActive())
			{
				mMapOfObjects.at(i).at(j)->Update(balloonPosition);
			}
		}
	}

	// Update the destroyers moving path //
	mDestroyersMovingPath->Update();
}
