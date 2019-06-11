#pragma once

#include <vector>

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "../../../models/paths/circle/CirclePath.h"
#include "../../../models/objects/other/level9/DestroyersCreation.h"

#include "cocos2d.h"

class Level9 : public CoreLevel 
{
private: 
	CirclePath* mCirclePath;
	DestroyersCreation* mDestroyersCreation;

	bool OnContactBegin(const cocos2d::PhysicsContact& contact);

public:
	Level9(cocos2d::Scene* scene);
    ~Level9();

    void Init() override;
    void Update() override;
};
