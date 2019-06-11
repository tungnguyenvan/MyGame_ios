#pragma once

#include <vector>

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "frames/frame1/Level3Frame1.h"
#include "frames/frame2/Level3Frame2.h"
#include "frames/frame3/Level3Frame3.h"
#include "frames/frame4/Level3Frame4.h"
#include "../../../models/paths/circle/CirclePath.h"

class Level3 : public CoreLevel
{
private:
    int mPosY;
    std::vector<CoreLevelFrame*> mCoreLevelFrame;
    CirclePath* mCirclePath;

    cocos2d::EventListenerPhysicsContact* mPhysicsContact;
    int mIndex;

public:
    Level3(cocos2d::Scene* scene);
    ~Level3();

    /**
     * Event physics collision
     * @param contact
     * @return
     */
    bool OnContactBegin(cocos2d::PhysicsContact& contact);

    void Init() override;
    void Update() override;
};
