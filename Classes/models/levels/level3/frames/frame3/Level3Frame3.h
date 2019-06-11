#pragma once

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level3/triangularline/TriangularLine.h"
#include "../../../../../models/objects/obstacles/level3/horizontalline/HorizontalLine.h"

#include "cocos2d.h"

class Level3Frame3 : public CoreLevelFrame
{
private:
    TriangularLine* mTriangularLine;
    HorizontalLine* mHorizontalLine;
	HorizontalLine* mHorizontal;

public:
    Level3Frame3(cocos2d::Scene* scene);
    ~Level3Frame3();

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
