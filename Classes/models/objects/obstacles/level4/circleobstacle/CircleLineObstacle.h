#pragma once

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/coin/CoinModel.h"

class CircleLineObstacle : public CoreModel
{
public:
    CircleLineObstacle(cocos2d::Scene* scene);
    CircleLineObstacle(cocos2d::Node* node);
    ~CircleLineObstacle();

    void Init() override;
    void Update() override;
};
