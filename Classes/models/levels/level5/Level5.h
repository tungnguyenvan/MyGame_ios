#pragma once

#include <vector>
#include "ui/CocosGUI.h"

#include "../../../models/levels/core/corelevel/CoreLevel.h"
#include "../../../models/objects/obstacles/level5/LineFrame.h"
#include "../../../common/Definition.h"
#include "../../../models/paths/horizontalline/HorizontalLinePath.h"
#include "../../../common/definitionlevels/DefinitionLevel5.h"

#include "cocos2d.h"

class Level5 : public CoreLevel 
{
private:
	LineFrame* mFirstLine;
	LineFrame* mSecondLine;
	LineFrame* mThirdLine;
	HorizontalLinePath* mHorizontalLinePath;
	int mIndexPath;
	int mFrameCount;
	int mMode;
	cocos2d::EventListenerPhysicsContact *mContact;

	std::vector<cocos2d::Color3B> mListOfColors;
	int mCurrentColorIndex;
	int mRandomTimeLerpColor;

	/**
	* Get Line Frame name Path
	*/
	std::string GetLineFramePath();

	/**
	* Moving line frame
	*/
	void MoveLine();

	/**
	* Disapear balloon when it collision with line frame
	*/
	void DisappearBalloon(cocos2d::Node* node);

	/**
	* Lerp color for line frame
	*/
	void LerpColor();

	/**
	* Collision detection
	*/
	bool OnContactBegin(cocos2d::PhysicsContact &contact);

public:
	Level5(cocos2d::Scene* scene);
    ~Level5();

    void Init() override;
    void Update() override;
};
