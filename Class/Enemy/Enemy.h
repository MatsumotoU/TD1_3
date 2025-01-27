#pragma once
#include <vector>
#include "Class/Common/Render.h"
#include "Class/Common/GameObject.h"

class Mapchip;

namespace ENM {
	const int kMaxStunFrame = 30;
	const int kMaxDeathFrame = 60;

	const int kCircleResolution = 64;

	enum Type
	{
		None,
		Melee,
		Shot,
		Shield
	};
}

class Enemy:public GameObject
{
public:

	Enemy();

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera(Camera* set);
	void SetIsAlive(int set);
	void SetIsHitAttack(int set);
	void SetHitAttackDir(Vector2 set);
	void SetPlayerRoute(std::vector<Vector2> set);
	void SetDeathFrame(int set);
	void SetEnemyType(ENM::Type set);
	void SetCanAttack(int set);
	void SetIsSeePlayer(int set);
	void SetPlayerPos(Vector2* set);
	void SetIsShot(int set);
	void SetIsExprosion(int set);
	void SetGH(int* set);
	void SetMapchip(Mapchip* set);
	void SetStunFrame(int set);

	int GetIsAlive();
	int GetIsHitAttack();
	Vector2 GetHitDir();
	Vector2* GetPosPtr();
	int GetGraphHandle();
	ENM::Type GetType();
	int GetIsAttack();
	int GetIsShot();
	Vector2 GetAngleDir();
	int GetIsReqestExprosion();
	Vector2 GetScreenPos();

	void Move();
	void LockOn();
	void Attack();
	void StateCheck();
	void UpdateExprodeCircle(int count);

	void UpdateSword();
	void DrawSword();

	void Stun();
	void TypeInit();

private:

	Transform oldTransform;

	int attackAnticipationFrame;
	int maxAttackAnticipationFrame;
	int isAttack;
	int isShot;
	int isAttacking;
	int canAttack;
	int isSeePlayer;
	Vector2* playerPos;
	float attackRange;
	int attackCoolDown;

	int deathFrame;
	Vector2 angleDir;
	Vector2 moveDir;
	Transform drawTransform;
	float rotateSpeed;

	int stunFrame;

	int isExprosion;
	int isAlive;
	Camera* camera;
	int* enemyGH;
	Transform swordTransform;
	int swordGH;
	unsigned int color;

	int isHitAttack;
	Vector2 hitDir;

	float moveSpeed;

	std::vector<Vector2> targetRoute;
	int nextRouteNum;

	ENM::Type type;

	Mapchip* map;

	float exprosionRadius;
	Vector2 exprosionRange[ENM::kCircleResolution];
	Vector2 exprosionMaxRange[ENM::kCircleResolution];
};