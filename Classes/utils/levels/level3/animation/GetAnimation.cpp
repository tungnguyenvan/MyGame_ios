#include "GetAnimation.h"

GetAnimation* GetAnimation::mGetAnimation = nullptr;

GetAnimation::GetAnimation()
{
    // Constructor
}

GetAnimation *GetAnimation::GetInstance()
{
    if (mGetAnimation == nullptr)
    {
        mGetAnimation = new GetAnimation();
    }

    return mGetAnimation;
}

cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimation::GetSpriteFramesWidthPlistFile(const std::string &plistFilePath,
                                                                                   const char *nameFormat,
                                                                                   const int &totalFrame)
{
    auto spriteCache = cocos2d::SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile(plistFilePath);
    cocos2d::Vector<cocos2d::SpriteFrame*> spriteFrames;

    char str[100];
    for (int i = 0; i < totalFrame; i++) {
        sprintf(str, nameFormat, i);
        spriteFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }

    return spriteFrames;
}

cocos2d::RepeatForever* GetAnimation::GetAnimationRepeatForever(const cocos2d::Vector<cocos2d::SpriteFrame *> &spriteFrames,
                                        const float &delayTime)
{
    return cocos2d::RepeatForever::create(cocos2d::Animate::create(
            cocos2d::Animation::createWithSpriteFrames(spriteFrames, delayTime)));
}
