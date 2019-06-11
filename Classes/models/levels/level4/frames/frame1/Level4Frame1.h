#pragma once

#include <vector>

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level3/rectagle/RectangleObstacleModel.h"

#include "cocos2d.h"

class Level4Frame1 : public CoreLevelFrame
{
private:
    std::vector<RectangleObstacleModel*> mRectangleObstacleModels;
    int mIndexRectangleObstacle;
    float mPosY;

    void RandomRectangle();

public:
    Level4Frame1(cocos2d::Scene* scene);
    ~Level4Frame1();

    void AliveObstacle(bool alive);

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
