#pragma once

#include <vector>

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/rectagle/RectangleObstacleModel.h"
#include "../../../../../models/objects/obstacles/level3/coin/CoinModel.h"

#include "cocos2d.h"

class TriangularLine : public CoreModel
{
private:
    std::vector<RectangleObstacleModel*> mRectangleObstacleModels;

    /**
     * Init vector RectangleObstacleModels
     */
    void InitRectangleObstacleModels();

    /**
     * Init the position of item of mRectangleObstacleModels
     */
    void InitPositionRectangleModels();

public:
    TriangularLine(cocos2d::Scene* scene);
    TriangularLine(cocos2d::Node* node);
    ~TriangularLine();

    void Init() override;
    void Update() override;
    void FadeOutModel(const float& opacity);
};
