#pragma once

#include "../../../../../models/core/CoreModel.h"

class CircleObstacleModel : public CoreModel
{
public:
	static const int MODE_MOVE_HORIZONTAL;
	static const int MODE_NONE;

private:
	int mMode;

public:
    CircleObstacleModel(const std::string& name, cocos2d::Sprite* sprite, int mode = 0);
    CircleObstacleModel(const std::string& name, cocos2d::Node* node, int mode = 0);
    ~CircleObstacleModel();

    void Init() override;
    void Update() override;
};
