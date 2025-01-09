#pragma once
#include "IScene.h"
#include "Class/Common/ParticlManager.h"

class TitleScene : public IScene {
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

	// タイトル用の変数
	Transform logo[3];
	Transform startLogo[2];
	Transform endLogo[2];
	Transform button[3];
	Transform startButton[2];
	Transform endButton[2];
	Transform efect[2];
	float efectT[2];
	float alphaValue[2];
	int efectCoolTime;
	int isEfectMove;
	int isEaseStart;
	int isUnderEfectMove;
	int isMoveEnd;
	int blinkTimer;
	int efectNum;
	unsigned int color[2];
	unsigned int returnColor[2];

	ParticlManager particleManager;
	Camera mainCamera;
	Vector2* cameraPos;

	// 画像のグラフハンドル
	int titleLogoGh[3];
	int buttonGh[3];
	int bigEfectGh[9];
	int smallEfectGh[9];
};

