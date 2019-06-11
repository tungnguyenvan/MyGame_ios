#pragma once

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/obstacles/level3/coin/CoinModel.h"

#include "cocos2d.h"

class LineObstacleModel : public CoreModel
{
private:
    bool mIsRun;
    cocos2d::EventListenerPhysicsContact* mPhysicsContact;

public:
    LineObstacleModel(cocos2d::Scene* scene);
    LineObstacleModel(cocos2d::Node* node);
    ~LineObstacleModel();

    /**
     * Rotate mCoreSprite
     */
    void Rotate();

    /**
     * Get rotate of mCoreSprite
     *
     * @return float rotation of mCoreSprite
     */
    float GetRotate();

    void Init() override;
    void Update() override;
};
