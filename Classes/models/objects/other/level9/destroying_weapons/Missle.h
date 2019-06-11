#pragma once

#include "../../../../../models/objects/other/level9/destroying_weapons/core/DestroyingWeapon.h"

#include "cocos2d.h" 

class Missle : public DestroyingWeapon
{
public:
	Missle(cocos2d::Scene* scene, const std::string& name);

	void StartOperating(const cocos2d::Vec2& originPosition, const cocos2d::Vec2& destinationPosition) override;
};
