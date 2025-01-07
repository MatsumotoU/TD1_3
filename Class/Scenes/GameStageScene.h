#pragma once
#include "IScene.h"
#include "Class/Player/Player.h"
#include "Class/Bullet/BulletManager.h"
#include "Class/Enemy/EnemyManager.h"

class GameStageScene : public IScene {
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
	int GetIsContinue() override { return false; };

	void ObjectUpdate();
	void ObjectCollision();
	void Attack();
	void PlayerLockOn();
	void ExprodeEnemy();

private:

	Player player;
	BulletManager bulletManager;
	EnemyManager enemyManager;
	
};

