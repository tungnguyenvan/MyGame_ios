#include "../../scenes/gameplay/GamePlayScene.h"
#include "Helper.h"

char* Helper::SKIP_INTRO_SCENE_VALUE = "SKIP_INTROSCENE_VALUE";
char* Helper::CURRENT_PASSED_LEVEL_INDEX = "CURRENT_PASSED_LEVELINDEX_VALUE";

std::string Helper::sLevelNames[] = { "Uranus", "Neptune", "Saturn", "Pluto", "Mars", "Earth","Jupiter","Venus","Mercury" };
std::string Helper::sLevelDescriptions[] = { "The personification of heaven", "Roman God of water",
                                             "God of agriculture", "Roman God of the underworld, Hades", "Roman God of war", "World of Gods",
                                             "Ruler of the Roman Gods","Goddess of love and beauty","Messenger of the Roman Gods" };

std::vector<std::string> Helper::GetAVectorOfAnimationFramesNames(const char* format, const int& count)
{
    std::vector<std::string> animFramesNames;

    char str[100];

    for (int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFramesNames.push_back(str);
    }

    return animFramesNames;
}

bool Helper::HasSkippedTheIntroScene()
{
    cocos2d::UserDefault* userDefault = cocos2d::UserDefault::getInstance();

    return userDefault->getIntegerForKey(SKIP_INTRO_SCENE_VALUE, 0) == 1;
}

void Helper::SkipTheIntroScene()
{
    cocos2d::UserDefault* userDefault = cocos2d::UserDefault::getInstance();
    userDefault->setIntegerForKey(SKIP_INTRO_SCENE_VALUE, 1);
}

std::string Helper::GetTheLevelNameBasedOnTheIndex(const int& index)
{
    return sLevelNames[index];
}

std::string Helper::GetTheLevelDescriptionBasedOnTheIndex(const int& index)
{
    return sLevelDescriptions[index];
}

int Helper::GetTheCurrentPassedLevelIndex()
{
    cocos2d::UserDefault* userDefault = cocos2d::UserDefault::getInstance();
    return userDefault->getIntegerForKey(CURRENT_PASSED_LEVEL_INDEX, 0);
}

void Helper::SetTheCurrentPassedLevelIndex()
{
    cocos2d::UserDefault* userDefault = cocos2d::UserDefault::getInstance();
    userDefault->setIntegerForKey(CURRENT_PASSED_LEVEL_INDEX, GamePlayScene::sCurrentLevelIndex + 1);
}
