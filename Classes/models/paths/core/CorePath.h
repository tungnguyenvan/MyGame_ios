#pragma once

#include "cocos2d.h"

class CorePath
{
protected:
    std::string mBalloonNamePath;
	std::string mPathNamePath;
	
	cocos2d::Sprite* mBalloonSprite;
    cocos2d::Sprite* mPathSprite;
	
	float mPathPositionY;
	float mBalloonMovingSpeed;

	bool mIsTouching;
	bool mIsTouchingRight;
	 
    /** Called when users touch the screen
	 *
	 * @param touch:
	 * @param event:
	 *
	 * @return a boolean indicates whether or not the listener passes down the touch event to other touch events
	 */
    virtual bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) = 0;

    /** Called when users stop touching the screen
    *
    * @param touch:
    * @param event:
    *
    * @return a boolean indicates whether or not the listener passes down the touch event to other touch events
    */
    virtual void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) = 0;

public:
    CorePath(const float& pathPositionY, const float& balloonMovingSpeed);
    virtual ~CorePath();

	/**
	* set balloon speed when frame change speed
	*/
	void setBalloonMovingSpeed(int balloonSpeed); 
	
	/**
	* Stop all operations when the balloon is exploded
	*/
	virtual void Disappear();

	virtual void Disappear(const float& opacity);

    /**
	 *  Update every single frame
	 */
    virtual void Update() = 0;
};
