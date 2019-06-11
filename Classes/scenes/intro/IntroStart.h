#pragma once

#include <vector>

#include "cocos2d.h"

class IntroStart : public cocos2d::Scene
{
private:
	cocos2d::Sprite* mFirstAnimationSprite;
	cocos2d::Sprite* mSecondAnimationSprite;
	std::vector<std::string> mAnimationFramesNames;
	int mAnimationCurrentFrameIndex;
	
	void AnimateNextFrame();
	void SkipIntro();
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntroStart);
};
