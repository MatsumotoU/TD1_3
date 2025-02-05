#pragma once
#include "IScene.h"
#include "Class/Common/ParticlManager.h"
#include "Class/UIobjects/BounceNumber.h"

// ステージの総数
const int stageTotalCount = 3;

// ミッションの星の総数
const int starTotalCount = 3;

class SelectScene : public IScene {
public:

	// 初期化と更新と描画
	void Init() override;
	void Update() override;
	void Draw() override;

	// ゲームシーン取得用
	IScene* GetNextScene() override;

	// シーン遷移しようとしてるか取得用
	int GetIsTransition() override { return isTransition; };

	// ゲームステージ管理
	int GetGameStage() override { return gameStage; };
	void SetGameStage(int setGameStage) override { setGameStage; };
	int GetIsContinue() override { return true; };

private:
	IScene* nextScene;

	Transform star[starTotalCount];
	int isStarMoving[starTotalCount];
	float starT[starTotalCount];
	unsigned int starColor[starTotalCount];

	Transform stageIcon[stageTotalCount];
	float stageIconT[stageTotalCount];

	Transform arrow[2];
	float arrowTheta[2];

	Transform spaceUI;

	Transform bg;
	unsigned int bgColor[3];
	float bgTheta[3];

	int playSEHandle[10];

	int shouldClearedMission[stageTotalCount][starTotalCount];

	int shouldPressedRight;
	int shouldPressedLeft;

	float stageIconTheta;
	float notSelectedStageScale;

	float zoomT;

	int isZoom;
	float movingFrameCount;

	int starGraphHandle;
	int arrowGraphHandle[2];
	int arrowPadGraphHandle[2];
	int spaceUIGraphHandle[2];
	int aUIGraphHandle[2];
	int bgGraphHandle[3];
	int stageIconGraphHandle[3];

	int tempGH;

	int sEHandle[10];

	Vector2* cameraPos;
	Vector2 cameraZoom;

	ParticlManager particleManager;

	BounceNumber highScore;
	int numGH[10];
	int crownGH;
	Transform crownTransform;
};

