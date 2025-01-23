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
	Transform logo[4];
	Transform startLogo[4];
	Transform endLogo[4];
	Transform button[4];
	Transform startButton[2];
	Transform endButton[2];
	Transform efect[2];
	float efectT[4];
	float alphaValue[4];
	int efectCoolTime;
	int isEfectMove;
	int isEaseStart;
	int isUnderEfectMove;
	int isSwordMove;
	int isMoveEnd;
	int isIncreaseAlpha;
	int efectNum;
	int changeSceneCount;
	int isChangeScene;
	unsigned int color[3];
	unsigned int returnColor[3];
	unsigned int endColor;

	ParticlManager particleManager;
	Camera mainCamera;
	Vector2* cameraPos;
	Vector2 sword[2];
	Vector2 efectDir[2];

	// 画像のグラフハンドル
	int titleLogoGh[4];
	int buttonGh[4];
	int bigEfectGh[9];
	int smallEfectGh[9];
	int bgGraphHandle[3];

	// 背景の変数
	float bgAngle[3];
	Transform bg;
	unsigned int bgColor[3];

	// 音の変数
	int dicisionSe;
	int isDicision;
};

