#include "Level9Helper.h"

cocos2d::Vector<cocos2d::SpriteFrame*> Level9Helper::GetAVectorOfSpriteFramesByCache(const char* format, const int& count)
{
	auto spritecache = cocos2d::SpriteFrameCache::getInstance();

	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;

	char str[100];

	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}

	return animFrames;
}