#pragma once
#include "IScene.h"
#include "Class/Player/Player.h"
#include "Class/Bullet/BulletManager.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Common/ParticlManager.h"
#include "Class/Common/Mapchip.h"
#include "Class/Balance/BalanceObject.h"

namespace GMScene {
	const int maxClearStageTimeBuffer = 120;
}

class GameStageScene : public IScene {
public:

	// 初期化と更新と描画
	void Init() override;
	void Update() override;
	void Draw() override;

	void ImGuiUpdate();

	// ゲームシーン取得用
	IScene* GetNextScene() override;

	// シーン遷移しようとしてるか取得用
	int GetIsTransition() override { return isTransition; };

	// ゲームステージ管理
	int GetGameStage() override { return gameStage; };
	void SetGameStage(int setGameStage) override { setGameStage; };
	int GetIsContinue() override { return false; };

	void WaveManager();
	void LoadWave();

	void ObjectUpdate();
	void ObjectCollision();

	void Attack();
	void PlayerLockOn();
	void ExprodeEnemy();
	void EnemyMoveToPlayer();
	void EnemyAttack();
	void WaveUiDraw();

	void ControlInfoUpdate();
	void ControlInfoDraw();

	void CameraUpdate();

private:

	int flashScreenFrame;
	int hitEffectGH[3];

	Transform contorolInfoTransform[3];
	int contorolInfoGH[4];

	int isClearStage;
	int clearStageTimeBuffer;
	int wave;
	int isChangeWave;

	int exprosionHitStopFrame;
	int stopObjectUpdateFrame;

	int slashGH;

	BalanceObject baranceObjects[EMG::kMaxEnemy + 1];
	Transform balancePoleTransform;
	int balancePoleGH;
	Transform balanceBasketTransform[2];
	float balanceBasketSwingWidth;
	int balanceBasketGH;
	float balanceAngle;
	float rightWeight;
	float leftWeight;
	int playerWeightGH;
	int enemyWeightGH;
	int lastHitEnemyNum;

	Transform waveStringTransform;
	int waveStringGH;

	Player player;
	BulletManager bulletManager;
	EnemyManager enemyManager;
	ParticlManager particleManager;
	Mapchip map;

	Vector2 testPopEnemyPos;

	Camera uiCamera;

	IScene* nextScene;
};

