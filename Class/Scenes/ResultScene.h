#pragma once
#include "IScene.h"
#include "Class/Common/ParticlManager.h"

class ResultScene : public IScene {
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

	Transform missionUI[starTotalCount];
	int isMissionUIMoving[starTotalCount];
	float missionUIT[starTotalCount];

	Transform button[2];
	int isButtonMoving[2];
	float buttonT[2];

	int movingOrder;

	int shouldClearedMission[starTotalCount];

	int shouldPressedRight;
	int shouldPressedLeft;

	float movingFrameCount;

	int starGraphHandle;
	int missionUIGraphHandle[starTotalCount];
	int nextSceneUIGraphHandle[2];

	Vector2 cameraZoom;
	Vector2* cameraPos;

	ParticlManager particleManager;
};

