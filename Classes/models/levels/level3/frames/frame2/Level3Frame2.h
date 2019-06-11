#pragma once

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level3/circleline/CircleLineModel.h"
#include "../../../../../models/objects/obstacles/level3/horizontalline/HorizontalLine.h"

#include "cocos2d.h"

class Level3Frame2 : public CoreLevelFrame
{
private:
    CircleLineModel* mCircleLineModel;
    HorizontalLine* mHorizontalLine;
	HorizontalLine* mHorizontal;

public:
    Level3Frame2(cocos2d::Scene* scene);
    ~Level3Frame2();

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
