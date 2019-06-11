#pragma once

#include "../../../../models/objects/other/level8and9/Creator.h"
#include "../../../../models/objects/obstacles/level9/core/CoreDestroyer.h"
#include "../../../../models/objects/other/level9/destroyer_moving_path/DestroyersMovingPath.h"

#include "cocos2d.h"

enum CreationStage
{
	CREATION_STAGE_1,
	CREATION_STAGE_2,
	CREATION_STAGE_3,
	CREATION_STAGE_IDLE,
	CREATION_STAGE_DONE
};

class DestroyersCreation : public Creator<CoreDestroyer>
{
private:
	DestroyersMovingPath* mDestroyersMovingPath;
	CreationStage mCreationStage;

	CoreDestroyer* GetAnInactiveObject(const int& mapIndex) override;

public:
	DestroyersCreation(cocos2d::Scene* scene);

	CreationStage GetCreationStage() const;

	void DisappearActiveObjects() override;

	/**
	 * Update every single frame
	 */
	void Update(const cocos2d::Vec2& balloonPosition);
};
