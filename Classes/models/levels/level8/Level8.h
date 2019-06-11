#pragma once

#include <vector>

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "../../../models/paths/verticalline/VerticalLinePath.h"
#include "../../../models/objects/other/level8/ObstaclesCreation.h"

#include "cocos2d.h"

class Level8 : public CoreLevel 
{
private: 
	VerticalLinePath* mVerticalLinePath;
	ObstaclesCreation* mObstaclesCreation;

	bool OnContactBegin(const cocos2d::PhysicsContact& contact);

public:
	Level8(cocos2d::Scene* scene);
    ~Level8();

    void Init() override;
    void Update() override;
};
