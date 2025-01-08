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
	Transform efect;
	Vector2 efectDir;
	float efectT;
	float alphaValue = 0.0f;
	int efectCoolTime;
	int isEfectMove;
	int isEaseStart;
	unsigned int color = 0xFFFFFF00;

	ParticlManager particleManager;
	Camera mainCamera;
};

