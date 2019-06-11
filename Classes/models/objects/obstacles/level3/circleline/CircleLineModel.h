#pragma once

#include <vector>

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/circle/CircleObstacleModel.h"

#include "cocos2d.h"

class CircleLineModel : public CoreModel
{
public:
	static const int OBSTACLE;
	static const int PATH;

private:
    std::vector<CircleObstacleModel*> mCircleObstacleModels;

	int mType;
	bool mIsTouching;
	bool mIsTouchingRight;

    cocos2d::Node* mNodeCoin;

    /**
     * Init vector circle obstacle
     */
    void InitCircleObstacleModels(cocos2d::Sprite* sprite);

    /**
     * Init the position of item in mCircleObstacleModels
     */
    void InitPositionCircleObstacleModels();

	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

public:
    CircleLineModel(cocos2d::Node* node, std::string name, int type);
    ~CircleLineModel();

    void Init() override;
    void Update() override;
    void FadeOutModel(const float& opacity);
};
