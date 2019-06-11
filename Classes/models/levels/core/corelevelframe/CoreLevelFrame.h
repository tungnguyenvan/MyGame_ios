#pragma once

#include <map>

#include "../../../../models/core/CoreModel.h"

#include "cocos2d.h"

class CoreLevelFrame 
{
protected:
	float mSpeed;
    std::map<std::string, CoreModel*> mObjectsDictionary;
    cocos2d::Node* mGroupNode;
    bool mHasFinishMoving;
	int mFrameCount;
	bool mIsBelowCenter;

public:
	CoreLevelFrame();
    ~CoreLevelFrame();

    /**
     * Check frame below center of screen
     *
     * @return true : below center screen
     * @return false : not below center screen
     */
    bool IsBelowCenter();

    void SetPositionY(float y);

	virtual void Init() = 0;
	virtual void Update() = 0;
    virtual bool HasFinishedMoving() = 0;
    virtual void FadeOutFrame(const float& opacity) = 0;
};
