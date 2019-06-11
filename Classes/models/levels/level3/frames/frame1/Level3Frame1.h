#pragma once

#include <vector>

#include "../../../../../models/levels/core/corelevelframe/CoreLevelFrame.h"
#include "../../../../../models/objects/obstacles/level3/horizontalline/HorizontalLine.h"

#include "cocos2d.h"

class Level3Frame1 : public CoreLevelFrame
{
private:
    std::vector<HorizontalLine*> mHorizontalLines;

    /**
     * Init vector HorizontalLines
     */
    void InitHorizontalLines();

public:
    Level3Frame1(cocos2d::Scene* scene);
    ~Level3Frame1();

    void Init() override;
    void Update() override;
    bool HasFinishedMoving() override;
    void FadeOutFrame(const float& opacity) override;
};
