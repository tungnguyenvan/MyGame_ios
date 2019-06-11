#include "CoreLevel.h"

CoreLevel::CoreLevel() 
{
	mFrameCount = 0;
	mIsGameOver = false;
	mIsCompletedLevel = false;
}

CoreLevel::~CoreLevel() 
{
	// Destructor
}

void CoreLevel::Init() 
{
    // Initialization
}

bool CoreLevel::IsGameOver() const
{
	return mIsGameOver;
}

bool CoreLevel::IsCompletedLevel() const
{
	return mIsCompletedLevel;
}

void CoreLevel::Update() 
{
    if (!mQueueOfFrames.empty())
    {
        mQueueOfFrames.front()->Update();
        if (mQueueOfFrames.front()->HasFinishedMoving())
        {
            mQueueOfFrames.pop();
        }
    }
}
