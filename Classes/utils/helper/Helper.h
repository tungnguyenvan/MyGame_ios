#pragma once

#include <vector>

#include "cocos2d.h"

class Helper
{
private:
    static char* SKIP_INTRO_SCENE_VALUE;
    static char* CURRENT_PASSED_LEVEL_INDEX;

    static std::string sLevelNames[];
    static std::string sLevelDescriptions[];

public:
    static std::vector<std::string> GetAVectorOfAnimationFramesNames(const char* format, const int& count);
    static bool HasSkippedTheIntroScene();
    static void SkipTheIntroScene();
    static std::string GetTheLevelNameBasedOnTheIndex(const int& index);
    static std::string GetTheLevelDescriptionBasedOnTheIndex(const int& index);
    static int GetTheCurrentPassedLevelIndex();
    static void SetTheCurrentPassedLevelIndex();
};