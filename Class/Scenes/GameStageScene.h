#pragma once
#include "IScene.h"
#include "Class/Player/Player.h"
#include "Class/Bullet/BulletManager.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Common/ParticlManager.h"
#include "Class/Common/Mapchip.h"

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
	void WaveUiDraw();

	void CameraUpdate();

private:

	int wave;
	int isChangeWave;

	Transform balancePoleTransform;
	int balancePoleGH;
	Transform balanceBasketTransform[2];
	float balanceBasketSwingWidth;
	int balanceBasketGH;
	float balanceAngle;

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

