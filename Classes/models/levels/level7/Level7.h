#pragma once

#include <vector>

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "../../../models/objects/obstacles/level3/circleline/CircleLineModel.h"
#include "../../../models/objects/other/level7/BarriersCreation.h"

#include "cocos2d.h"

class Level7 : public CoreLevel 
{
private:
	CircleLineModel* mCircleLine;
	BarriersCreation* mBarriersCreation;

public:
	Level7(cocos2d::Scene* scene);
    ~Level7();

	/**
	* remove node when collision
	*/
	void DisappearNode(cocos2d::Node* node);

	/**
	* Collision detection
	*/
	bool OnContactBegin(cocos2d::PhysicsContact &contact);

    void Init() override;
    void Update() override;
};
