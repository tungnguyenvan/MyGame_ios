#pragma once

#include "cocos2d.h"

class Level9Helper
{
public:
	static cocos2d::Vector<cocos2d::SpriteFrame*> GetAVectorOfSpriteFramesByCache(const char* format, const int& count);
};