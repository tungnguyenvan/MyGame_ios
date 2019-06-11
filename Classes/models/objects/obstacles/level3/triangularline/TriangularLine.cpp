#include "TriangularLine.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"

TriangularLine::TriangularLine(cocos2d::Scene *scene) : CoreModel(TRIANGULAR_PATH_NAME_PATH)
{
    Init();
    scene->addChild(mCoreSprite);
}

TriangularLine::TriangularLine(cocos2d::Node *node) : CoreModel(TRIANGULAR_PATH_NAME_PATH)
{
    Init();
    node->addChild(mCoreSprite);
}

TriangularLine::~TriangularLine()
{
    // Destructor
}

void TriangularLine::Init()
{
    mCoreSprite = cocos2d::Sprite::create(mModelName);

    // Init vector rectangle
    InitRectangleObstacleModels();
    InitPositionRectangleModels();
}

void TriangularLine::Update()
{
    for (int i = 0; i < TRIANGULAR_SIZE_RECTANGULAR_OBSTACLE_MODELS; ++i)
    {
      mRectangleObstacleModels.at(i)->Update();
    }
}

void TriangularLine::InitRectangleObstacleModels()
{
    for (int i = 0; i < TRIANGULAR_SIZE_RECTANGULAR_OBSTACLE_MODELS; i++)
    {
        mRectangleObstacleModels.push_back(new RectangleObstacleModel(mCoreSprite, RECTANGLE_NAME_PATH));
    }
}

void TriangularLine::InitPositionRectangleModels()
{
    mRectangleObstacleModels.at(0)->SetPosition(GetContentSize().width / 2, GetContentSize().height);
    mRectangleObstacleModels.at(1)->SetPosition(GetContentSize().width, 0);
    mRectangleObstacleModels.at(2)->SetPosition(GetContentSize().width / 2, 0);
}

void TriangularLine::FadeOutModel(const float &opacity)
{
    CoreModel::FadeOutModel(opacity);

    for (int i = 0; i < mRectangleObstacleModels.size(); i++)
    {
        mRectangleObstacleModels.at(i)->FadeOutModel(opacity);
        mRectangleObstacleModels.at(i)->SetEnablePhysicsBody(false);
    }
}
