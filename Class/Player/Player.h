#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/InputManager.h"
#include "Class/Common/Render.h"
#include "Class/Common/ParticlManager.h"

class Mapchip;

// プレイヤーで使う定数
namespace PLR {
	const int kMaxMoveStackFrame = 15;
	const int kMaxDashCoolDown = 30;
	const int kMaxAttackCoolDown = 60;
	const int kMaxSheatheCoolDown = 120;
	const float kAttackReach = 32.0f;
	const int kMaxAttackChance = 2;
	const int kMaxDamageCoolDown = 120;
}

class Player : public GameObject
{
public:

	Player();

	void Init() override;
	void Update() override;
	void Draw() override;

	void Move();
	void LockOn();
	void Dash();
	void Attack();
	void Sheathe();
	void StateCheck();

	void HaloMove();
	void WingMove();
	void WingDraw();

	void UpdateHpUi();
	void DrawHpUi();
	void DrawSword();

	void LoadVariables();
	void SaveVariables();
	void UpdateImGui();

	void SetIsLockOn(int set);
	void SetTargetPos(Vector2 set);
	void SetCamera(Camera* set);
	void SetIsAttack(int set);
	void SetIsSheathe(int set);
	void SetRemainAttackChance(int set);
	void SetIsDash(int set);
	void SetMapchip(Mapchip* set);

	int GetIsAlive();
	int GetIsAttack();
	int GetIsSheathe();
	int GetIsDash();
	int GetRemainAttackChance();
	int GetCanAttack();
	int GetDamageCoolDown();
	Vector2 GetAttackPos();
	Vector2* GetPosPtr();
	int GetGraphHandle();
	int GetHp();
	int GetMaxHp();

	void CountDownRemainAttackChance();
	void Damage();

private:
	int frameCount;
	float seVolume;

	Transform oldTransform;

	Transform rightArm;
	Transform leftArm;
	int swordGH;

	int hpUiDrawFrame;
	Transform hpTransform[3];
	int hpGH;
	int lostHpGH;

	Transform haloTransform;
	int haloGH;
	int haloExprosionGH[4];
	int orangeLightGH;

	float flapping;
	Transform leftWingTransform;
	Transform rightWingTransform;
	int wingGH;
	int featherGH;

	int playerGH;

	int hp;
	int maxHp;
	int isAlive;
	
	int isMove;
	int moveStackFrame;
	float moveSpeed;
	Vector2 angleDir;

	int isDash;
	int dashCoolDown;
	float dashPower;
	int dashAfterimageRemainFrame;
	int dashAfterimageRemainInterval;
	int dashOP;

	int isAttack;
	int attackCoolDown;
	int remainAttackChance;

	int isSheathe;
	int sheatheCoolDown;

	int damageCoolDown;

	int isLockOn;
	Vector2 targetPos;
	Transform targetTransform;
	int lockOnGH;

	Camera* camera;

	ParticlManager particleManager;

	// キー入力受付クラス呼び出し
	InputManager* input = InputManager::GetInstance();

	Mapchip* map;
};

