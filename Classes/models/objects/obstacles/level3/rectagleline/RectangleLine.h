#pragma once

#include <vector>

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/triangular/TriangularObstacleModel.h"
#include "../../../../../models/objects/obstacles/level3/coin/CoinModel.h"

#include "cocos2d.h"

class RectangleLine : public CoreModel
{
private:
    std::vector<TriangularObstacleModel*> mTriangularObstacleModels;

    /**
     * Init vector RectangleObstacleModels
     */
    void InitTriangleObstacleModels();

    /**
     * Init the position of item of mRectangleObstacleModels
     */
    void InitPositionTriangleModels();

public:
    RectangleLine(cocos2d::Scene* scene);
    RectangleLine(cocos2d::Node* node);
    ~RectangleLine();

    void Init() override;
    void Update() override;
    void FadeOutModel(const float& opacity);
};
