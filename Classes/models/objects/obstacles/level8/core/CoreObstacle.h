#pragma once

#include "../../../../../models/core/CoreModel.h"

#include "cocos2d.h"

class CoreObstacle : public CoreModel
{
protected:
	float mTravelingDuration;

	void Init() override;
	void Update() override;

	/**
	 * Set the physics body for the obstacles sprites
	 */
	virtual void SetPhysicsBody(const std::string& physicsBodyName);
	 
public:
	CoreObstacle(const float& travelingDuration, const std::string& name);
	
	/**
	 * Make this obstacle to gradually disappear from the scene
	 */
	virtual void Disappear();

	/**
	* Make the obstacles move with the proper direction based on the path's stages
	* @param startOnTheRightSide
	*/
	virtual void StartTraveling(const bool& startOnTheRightSide) = 0;
};
