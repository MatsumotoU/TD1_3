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

	Transform spaceUI;

	Transform bg;
	unsigned int bgColor[3];
	int isBgDrawn;

	Transform cracker[2];
	float crackerT[2];
	unsigned int crackerAlpha[2];
	int isCrackerMoving[2];

	int movingOrder;

	int shouldClearedMission[starTotalCount];

	int shouldPressedRight;
	int shouldPressedLeft;

	float movingFrameCount;

	int isDuringAnimation;

	int starGraphHandle;
	int missionUIGraphHandle[starTotalCount];
	int nextSceneUIGraphHandle[2];
	int spaceUIGraphHandle[2];
	int aUIGraphHandle[2];
	int crackerGraphHandle[2];
	int bgGraphHandle[3];

	unsigned int flashAlpha;

	Vector2 cameraZoom;
	Vector2* cameraPos[2];

	Camera subCamera;

	ParticlManager particleManager;
};

