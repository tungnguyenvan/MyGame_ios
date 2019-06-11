#pragma once

#include "../../../models/paths/core/CorePath.h"

#include "cocos2d.h"

class TriangularPath : public CorePath
{
private:
    //variable of triangular
    cocos2d::Vec2 mPointTop;
    cocos2d::Vec2 mPointLeft;
    cocos2d::Vec2 mPointRight;
    cocos2d::Size mVisibleSize;

    /* Change variables here to fit your needs */
    float mLengthPath;
    /******************************************/

public:
    TriangularPath(cocos2d::Scene* scene, const float& lengthPath,
                   const std::string& pathNamePath, const std::string& balloonNamePath,
                   const float& pathPositionY, const float& balloonMovingSpeed);
    ~TriangularPath();

    /**
     * Move Sprite to Right (user touch on right scene)
     */
    void OnMoveToRight();

    /**
     * Move Sprite to left (user touch on left scene)
     */
    void OnMoveToLeft();

    /**
     * Move Sprite to point right
     *
     * @param isToRight : is touch on right screen
     */
    void ToPointRight(bool isToRight);

    /**
     * Move sprite to point right
     *
     * @param isRight : is touch on right screen
     */
    void ToPointLeft(bool isRight);

    /**
     * Move sprite horizontal
     *
     * @param isRight : is touch on right screen
     */
    void ToHorizontal(bool isRight);

    /**
     * Event on touch on screen
     *
     * @param touch
     * @param event
     *
     * @return true : will implement event OnTouchEnded
     */
    bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;

    /**
     * Event on touch ended on screen
     *
     * @param touch
     * @param event
     */
    void OnTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;

    /**
     * Update logic for sprite
     */
    void Update();
};
