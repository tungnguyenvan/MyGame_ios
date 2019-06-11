#pragma once

#include <queue>

#include "../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"

#include "cocos2d.h"

class CoreLevel 
{
protected:
    std::queue<CoreLevelFrame*> mQueueOfFrames;
	int mFrameCount;
	bool mIsGameOver;
	bool mIsCompletedLevel;
	
public:
    CoreLevel();
    ~CoreLevel();

	bool IsGameOver() const;
	bool IsCompletedLevel() const;

    virtual void Init() = 0;
    virtual void Update() = 0;
};
