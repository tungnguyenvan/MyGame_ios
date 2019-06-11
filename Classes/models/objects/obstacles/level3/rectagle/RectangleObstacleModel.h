#pragma once

#include "../../../../../models/core/CoreModel.h"

#include "cocos2d.h"

class RectangleObstacleModel : public CoreModel
{
private:
    bool mIsRotateToRight;

public:
    RectangleObstacleModel(cocos2d::Scene* scene, std::string name);
    RectangleObstacleModel(cocos2d::Node* node, std::string name);
    ~RectangleObstacleModel();

    void Init() override;
    void Update() override;
};
