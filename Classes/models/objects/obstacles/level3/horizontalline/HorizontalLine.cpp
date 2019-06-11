#include "HorizontalLine.h"
#include "../../../../../common/definitionlevels/DefinitionLevel3.h"

const int HorizontalLine::MODE_CIRCLE = 0;
const int HorizontalLine::MODE_TRIANGULAR = 1;

HorizontalLine::HorizontalLine(cocos2d::Scene* scene, int mode) : CoreModel(HORIZONTAL_LINE_NAME_PATH)
{
	mMode = mode;
    Init();

    scene->addChild(mCoreSprite);
}

HorizontalLine::HorizontalLine(cocos2d::Node* node, int mode) : CoreModel(HORIZONTAL_LINE_NAME_PATH)
{
	mMode = mode;
    Init();

    node->addChild(mCoreSprite);
}

HorizontalLine::~HorizontalLine()
{
    // Destructor
}

void HorizontalLine::Init()
{
    mCoreSprite = cocos2d::Sprite::create(mModelName);

	if (mMode == MODE_TRIANGULAR)
	{
		mTriangularObstacleModel = new TriangularObstacleModel(mCoreSprite, TriangularObstacleModel::MOVE_HORIZONTAL);
		int positionX = cocos2d::RandomHelper::random_real(mTriangularObstacleModel->GetContentSize().width / 2,
			cocos2d::Director::getInstance()->getVisibleSize().width - mTriangularObstacleModel->GetContentSize().width / 2);
		mTriangularObstacleModel->SetPosition(positionX, mTriangularObstacleModel->GetPositionX());
	}
	else if (mMode == MODE_CIRCLE)
	{
		InitCircleObstacleModels();
	}
}

void HorizontalLine::InitCircleObstacleModels()
{
	for (int i = 0; i < HORIZONTAL_LINE_SIZE_CIRCLE_OBSTACLE; i++)
	{
		auto circleModel = new CircleObstacleModel("sprites/gameplay/level3/circle/circle.png", mCoreSprite, CircleObstacleModel::MODE_MOVE_HORIZONTAL);
		circleModel->SetPosition(mCoreSprite->getContentSize().width + circleModel->GetContentSize().width,
									mCoreSprite->getContentSize().height / 2);
		circleModel->SetActive(false);

		mCircleObstacleModels.push_back(circleModel);
	}
}

void HorizontalLine::Update()
{
	if (mMode == MODE_TRIANGULAR)
	{
		mTriangularObstacleModel->Update();
	}
	else if (mMode == MODE_CIRCLE)
	{
		for (int i = 0; i < HORIZONTAL_LINE_SIZE_CIRCLE_OBSTACLE; i++)
		{
			mCircleObstacleModels.at(i)->Update();
		}

		mFrameCount++;
		if (mFrameCount % 150 == 0)
		{
			mFrameCount = 0;
			for (int i = 0; i < HORIZONTAL_LINE_SIZE_CIRCLE_OBSTACLE; i++)
			{
				if (!mCircleObstacleModels.at(i)->IsActive())
				{
					mCircleObstacleModels.at(i)->SetActive(true);
					break;
				}
			}
		}
	}
}

void HorizontalLine::FadeOutModel(const float &opacity)
{
	CoreModel::FadeOutModel(opacity);

	if (mCircleObstacleModels.size() > 0)
	{
		for (int i = 0;i < mCircleObstacleModels.size(); i++)
		{
			mCircleObstacleModels.at(i)->FadeOutModel(opacity);
			mCircleObstacleModels.at(i)->SetEnablePhysicsBody(false);
		}
	}
	else
	{
		mTriangularObstacleModel->FadeOutModel(opacity);
		mTriangularObstacleModel->SetEnablePhysicsBody(false);
	}
}
