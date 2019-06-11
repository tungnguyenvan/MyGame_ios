#pragma once

#include <vector>

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/triangular/TriangularObstacleModel.h"
#include "../../../../../models/objects/obstacles/level3/circle/CircleObstacleModel.h"

#include "cocos2d.h"

class HorizontalLine : public CoreModel
{
public:
	static const int MODE_CIRCLE;
	static const int MODE_TRIANGULAR;

private:
    TriangularObstacleModel* mTriangularObstacleModel;
	std::vector<CircleObstacleModel*> mCircleObstacleModels;
	int mMode;

	/**
	* Init vector circle obstacle
	*/
	void InitCircleObstacleModels();

public:
    HorizontalLine(cocos2d::Scene* scene, int mode);
    HorizontalLine(cocos2d::Node* node, int mode);
    ~HorizontalLine();

    void Init() override;
    void Update() override;
	void FadeOutModel(const float& opacity);
};
