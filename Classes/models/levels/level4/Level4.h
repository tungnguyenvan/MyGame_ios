#pragma once

#include <vector>

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../models/levels/level4/frames/frame1/Level4Frame1.h"
#include "../../../models/levels/level4/frames/frame2/Level4Frame2.h"
#include "../../../models/objects/obstacles/level4/lineobstacle/LineObstacleModel.h"
#include "../../../models/paths/circle/CirclePath.h"

#include "cocos2d.h"

class Level4 : public CoreLevel
{
private:
    int mIndexFrame;
    int mPosY;
    std::vector<CoreLevelFrame*> mLevelFrames;
    LineObstacleModel* mLineObstacle;
    CirclePath* mCirclePath;
    cocos2d::EventListenerPhysicsContact* mEventPhysics;

    /**
     * Init vector CoreLevelFrame
     * @param scene
     */
    void InitFrame(cocos2d::Scene* scene);

    /**
     * Set position for item CoreLevelFrames
     */
    void InitPositionFrame();

    /**
     * set position of frame index to top
     * @param index
     */
    void MoveFrameOnTop(int index);

    bool OnContactBegin(cocos2d::PhysicsContact& physicsContact);

public:
    Level4(cocos2d::Scene* scene);
    ~Level4();

    void Init() override;
    void Update() override;
};
