#pragma once
#include "IScene.h"
#include "Class/Common/ParticlManager.h"
#include "Class/Common/InputManager.h"
#include "Class/Common/MyEasing.h"

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
	Transform star[stageTotalCount][starTotalCount];
	Transform stageIcon[stageTotalCount];

	ParticlManager particleManager;

	// キー入力受付クラス呼び出し
	InputManager* input = InputManager::GetInstance();
};

