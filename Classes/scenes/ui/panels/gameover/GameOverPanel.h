#pragma once

#include "cocos2d.h"
 
class GameOverPanel
{
private:
	void Share();
	void Menu();
	void TryAgain();

public:
	GameOverPanel(cocos2d::Scene* scene);
};
