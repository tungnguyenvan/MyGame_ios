#pragma once

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level3/rectagleline/RectangleLine.h"
#include "../../../../../models/objects/obstacles/level3/horizontalline/HorizontalLine.h"

#include "cocos2d.h"

class Level3Frame4 : public CoreLevelFrame
{
private:
    RectangleLine* mRectangleLine;
    HorizontalLine* mHorizontalLine;
	HorizontalLine* mHorizontal;

public:
    Level3Frame4(cocos2d::Scene* scene);
    ~Level3Frame4();

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
