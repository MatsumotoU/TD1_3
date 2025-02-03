#pragma once
#include "IScene.h"
#include "Class/Player/Player.h"
#include "Class/Bullet/BulletManager.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Common/ParticlManager.h"
#include "Class/Common/LightManager.h"
#include "Class/Common/Mapchip.h"
#include "Class/Balance/BalanceObject.h"

#include "Class/UIobjects/BounceNumber.h"
#include "Class/UIobjects/ContorolTutorialUI.h"
#include "Class/UIobjects/PlayerHpUI.h"
#include "Class/UIobjects/ComboUI.h"
#include "Class/UIobjects/PlayerStopClockUI.h"
#include "Class/UIobjects/ScoreUIManager.h"

namespace GMScene {
	const int maxClearStageTimeBuffer = 150;
	const int maxComboRemainFrame = 150;
	const float exprodeRange = 256.0f;

	const int maxPlayerAttackStopFrame = 120;
	const int kSecondPerPlayerAttackStopFrame = 3;
	const int kMaxComboTrigerCooldown = 5;

	const int startEventMaxFrame = 60;
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

	void EnemyCollision();

	void Attack();
	void PlayerLockOn();
	void ExprodeEnemy();
	void EnemyMoveToPlayer();
	void EnemyAttack();
	void WaveUiDraw();
	void BalanceUpdate();
	void PlayerDeath();

	void ControlInfoUpdate();
	void ControlInfoDraw();

	void CameraUpdate();

private:

	float seVolume;

	int flashScreenFrame;
	int hitEffectGH[3];

	Transform contorolInfoTransform[3];
	float shakeContorolInfoExprosion;
	int contorolInfoGH[4];
	int rcContorolInfoGH[4];

	int isClearStage;
	int clearStageTimeBuffer;
	int wave;
	int isChangeWave;

	int exprosionHitStopFrame;
	int stopObjectUpdateFrame;

	int slashGH;

	int exprosionComboCount;
	int comboRemainFrame;
	int comboOP[5];

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

	ContorolTutorialUI contorolTutorialUI;
	PlayerHpUI playerHpUI;

	BounceNumber targetScoreNum;
	int enemyRemainNumGH[10];
	BounceNumber waveNumber;
	Transform clossTransform;
	int clossGH;
	Transform enemyTargetTransform;
	int targetEnemyUiGH;
	Transform missionTransform;
	int missionGH;

	LightManager lightManager;

	float cameraLocalScale;

	ComboUI comboUI;

	int playerAttackStopFrame;
	int playerAttackHitCount;
	int playerAttackOP;
	PlayerStopClockUI playerStopClockUI;

	ScoreUIManager scoreUIManager;

	int score;
	BounceNumber gameScore;
	Transform scoreTitle;
	int scoreTitleGH;

	int isNotDeath;
	int isSlowFrame;
	float slowFrameScoreRatio;

	BounceNumber scoreRatio;
	
	int stageStartGH;

	int gameTime;
	BounceNumber timeNum;

	int enemyBloodGH;
	int exprosionGH[7];
	int enemyBulletGH;

	int playerHitGH[5];

	int comboTrigerCooldown;

	int isStartingGame;
	int startGameBufferFrame;
	int startGH;

	int enemySpawnFrame;

	int isEndGame;
};

