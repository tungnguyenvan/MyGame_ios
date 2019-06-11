 #pragma once

#include "../../../common/definitionlevels/DefinitionLevel5.h"
#include "../core/CorePath.h"
#include "../../../common/Definition.h"

 #include "cocos2d.h"

class HorizontalLinePath : public CorePath
{
private:
	cocos2d::PhysicsBody* mBalloonSpritePhysicsBody;
public: 
	HorizontalLinePath(cocos2d::Scene* scene, const std::string& pathNamePath, 
		const std::string& balloonNamePath, const float& pathPositionY, const float& ballooonMovingSpeed);
	~HorizontalLinePath();

	void Update() override;
	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	void OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
};
