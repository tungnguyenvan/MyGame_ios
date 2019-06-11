#pragma once

#include "../../../../../../models/core/CoreModel.h"

#include "cocos2d.h" 

class DestroyingWeapon : public CoreModel
{
private:
	void Init() override;
	void Update() override;

public:
	DestroyingWeapon(const std::string& name);

	virtual void StartOperating(const cocos2d::Vec2& originPosition,
		const cocos2d::Vec2& destinationPosition) = 0;
};
