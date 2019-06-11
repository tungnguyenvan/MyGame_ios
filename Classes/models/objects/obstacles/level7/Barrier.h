#pragma once

#include "../../../../models/core/CoreModel.h"

#include "cocos2d.h"

class Barrier : public CoreModel{
public:
	static const int MODE_MOVE_TOP_TO_BOTTOM;
	static const int MODE_MOVE_BOTTOM_TO_TOP;
	static const int MODE_MOVE_TOP_LEFT_TO_BOTTOM_RIGHT;
	static const int MODE_MOVE_BOTTOM_RIGHT_TO_TOP_LEFT;
	static const int MODE_MOVE_TOP_RIGHT_TO_BOTTOM_LEFT;
	static const int MODE_MOVE_BOTTOM_LET_TO_TOP_RIGHT;
	
	static const int COLOR_BLUE;
	static const int COLOR_RED;
	static const int COLOR_GREEN;
	static const int COLOR_YELLOW;

private:
	int mMode;
	int mColor;
	int mCurrentDistance;
	cocos2d::Vec2 mStartPosition;
	cocos2d::Vec2 mEndPosition;
	int mBarrierMovingSpeed;

public:
	Barrier(cocos2d::Scene* scene, std::string name, int mode, int color);
	~Barrier();

	/**
	* Set physics body for sprite
	*/
	void SetPhysicsBody();

	void Init() override;
	void Update() override;
};
