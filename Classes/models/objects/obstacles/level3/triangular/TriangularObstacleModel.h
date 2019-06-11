#pragma once

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../utils/physics/CustomPhysicsBody.h"

#include "cocos2d.h"

class TriangularObstacleModel : public CoreModel
{
private:
    bool mIsGoAhead;
    bool mIsMoveToRight;
    bool mIsRotateHasFinish;
    int mCountStep;
    int mMoveType;

    /**
     * Rotate obstacle when move horizontal
     */
    void RotateTriangularObstacle();

public:
    static const int MOVE_VERTICAL;
    static const int MOVE_HORIZONTAL;

public:
    TriangularObstacleModel(cocos2d::Scene* scene, int move);
    TriangularObstacleModel(cocos2d::Node* node, int move);
    ~TriangularObstacleModel();

    void Init() override;
    void Update() override;
};
