#pragma once

#include <vector>

#include "../../../../../models/core/CoreModel.h"
#include "../../../../../models/objects/other/level9/destroying_weapons/core/DestroyingWeapon.h"

#include "cocos2d.h"

class CoreDestroyer : public CoreModel
{
protected:
	cocos2d::Sprite* mExtraComponentSprite;
	std::vector<DestroyingWeapon*> mVectorOfDestroyingWeapons;

	cocos2d::Vec2 mDepartingPosition;
	float mTravelingSpeed;

	void Init() override;
	void Update() override;

public:
	CoreDestroyer(const float& travelingSpeed, const cocos2d::Vec2& DepartingPosition, const std::string& name);
	 
	/**
	 * Check whether or not this destroyer is moving in a specific zone, if it is > able to destroy
	 * @return bool
	 */
	virtual bool IsAbleToDestroy();

	/**
	 * Every destroyer has to do something harmful to the balloon
	 */
	void Destroy(const cocos2d::Vec2& balloonPosition);

	/**
	 * Make this destroyer to gradually disappear from the scene
	 */
	virtual void Disappear();

	/**
	 * Update every single frame
	 */
	virtual void Update(const cocos2d::Vec2& balloonPosition) = 0;
};
