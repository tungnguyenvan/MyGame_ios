#pragma once

#include <string>

#include "cocos2d.h"

class GetAnimation
{
private:
    static GetAnimation* mGetAnimation;

    GetAnimation();

public:

    /**
     * GetInstance singleton
     *
     * @return class GetAnimation
     */
    static GetAnimation* GetInstance();

    /**
     * Get animation RepeatForever using .plist file
     *
     * @param plistFilePath : .plist file path
     * @param nameFormat : name of frame in .plist
     * @param totalFrame : total frame
     * @param timeDelay : time delay 2 frame
     *
     * @return cocos2d::RepeatForever*
     */
    cocos2d::Vector<cocos2d::SpriteFrame*> GetSpriteFramesWidthPlistFile(const std::string &plistFilePath,
                                                                         const char *nameFormat, const int &totalFrame);

    /**
     * Create animation repeat forever from vector sprite frame
     *
     * @param spriteFrames : cocos2d::Vector<cocos2d::SpriteFrame*>
     * @param delayTime : float
     *
     * @return coocs2d::RepeatForever*
     */
    cocos2d::RepeatForever* GetAnimationRepeatForever(const cocos2d::Vector<cocos2d::SpriteFrame*>& spriteFrames,
                                                      const float& delayTime = 0.1);
};