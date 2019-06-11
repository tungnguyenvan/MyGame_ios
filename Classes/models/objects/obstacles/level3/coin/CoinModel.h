#pragma once

#include "../../../../../models/core/CoreModel.h"

#include "cocos2d.h"

class CoinModel : public CoreModel
{
private:
    cocos2d::Vector<cocos2d::SpriteFrame*> mSpriteFrames;

public:
    CoinModel(cocos2d::Scene* scene);
    CoinModel(cocos2d::Node* node);
    ~CoinModel();

    void Init() override;
    void Update() override;
};
