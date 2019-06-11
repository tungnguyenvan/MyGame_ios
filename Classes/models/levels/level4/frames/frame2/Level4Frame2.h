#pragma once

#include <vector>

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level4/lineobstacle/LineObstacleModel.h"
#include "../../../../../models/objects/obstacles/level4/circleobstacle/CircleLineObstacle.h"

#include "cocos2d.h"

class Level4Frame2 : public CoreLevelFrame
{
private:
    float mPositionY;
    LineObstacleModel* mLineObstacleModel;
    CircleLineObstacle* mCircleLineObstacle;

public:
    Level4Frame2(cocos2d::Scene* scene);
    ~Level4Frame2();

    void AliveObstacle(bool alive);

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
