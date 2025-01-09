#pragma once
#include "IScene.h"
#include "Class/Common/ParticlManager.h"

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

	Transform stageIcon[stageTotalCount];
	float stageIconT[stageTotalCount];

	Transform arrow[2];
	float arrowTheta[2];

	int shouldClearedMission[stageTotalCount][starTotalCount];

	int shouldPressedRight;
	int shouldPressedLeft;

	float stageIconTheta;
	float notSelectedStageScale;

	//float timeMoveStageIcon;
	//float timeMoveStar;
	float movingFrameCount;

	int starGraphHandle;
	int arrowGraphHandle[2];

	Vector2* cameraPos;

	ParticlManager particleManager;
};

