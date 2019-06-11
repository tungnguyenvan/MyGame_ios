#pragma once

#include "cocos2d.h"

class CoreModel
{
protected:
    cocos2d::Sprite* mCoreSprite;
    cocos2d::PhysicsBody* mCorePhysicsBody;

    bool mIsActive;
    std::string mModelName;
    int mFrameCount;

public:
    CoreModel(const std::string& name);
    virtual ~CoreModel();

    /**
     * Get the position of the sprite
     *
     * @return position (cocos2d::Vec2)
     */
    cocos2d::Vec2 GetPosition() const;

    /**
     * Get the position x of the sprite
     *
     * @return positionX (float)
     */
    float GetPositionX() const;

    /**
     * Get the position Y of the sprite
     *
     * @return positionY (float)
     */
    float GetPositionY() const;

    /**
     * Set the position for the sprite
     *
     * @param position (cocos2d::Vec2)
     */
    void SetPosition(const cocos2d::Vec2& position);

    /**
     * Set the position for the sprite
     *
     * @param x (float)
     * @param y (float)
     */
    void SetPosition(const float& x, const float& y);

    /**
     * Get the size of the sprite
     *
     * @return size (cocos2d::Size)
     */
    cocos2d::Size GetContentSize() const;

    /**
     * Get the height size of the sprite
     *
     * @return height (float)
     */
    float GetHeight() const;

    /**
     * Get the width size of the sprite
     *
     * @return width (float)
     */
    float GetWidth() const;

    /**
     * Check to see whether or not the sprite is active
     *
     * @return isActive (bool)
     */
    bool IsActive() const;

    /**
     * Set the visibility of the sprite
     *
     * @param active (bool)
     */
    void SetActive(const bool& active);

    /**
     * Set enable or disable physics body of sprite
     *
     * @param enable : bool
     */
    void SetEnablePhysicsBody(const bool& enable);

    /**
     * Fade out sprite when finish game or game over
     */
    virtual void FadeOutModel(const float& opacity);

    /**
     * Return the name of the model
     *
     * @return model name (std::string)
     */
    std::string GetModelName() const;

    /**
     * Set the rotation of the sprite
     *
     * @param degree (int)
     */
    void SetRotation(const float& degree);

    /**
     * Initialization method
     */
    virtual void Init() = 0;

    /**
     * Update every single frame
     */
    virtual void Update() = 0;
};
