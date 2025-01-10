#pragma once
#include <vector>
#include "Class/Common/Render.h"
#include "Class/Common/GameObject.h"

namespace ENM {
	const int kMaxStunFrame = 180;
	const int kMaxDeathFrame = 60;
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

	int GetIsAlive();
	int GetIsHitAttack();
	Vector2 GetHitDir();
	Vector2* GetPosPtr();
	int GetGraphHandle();

	void Move();
	void LockOn();
	void StateCheck();

	void Stun();

private:

	int deathFrame;
	Vector2 angleDir;
	Vector2 moveDir;
	Transform drawTransform;

	int stunFrame;

	int isExprosion;
	int isAlive;
	Camera* camera;
	int enemyGH;
	unsigned int color;

	int isHitAttack;
	Vector2 hitDir;

	float moveSpeed;

	std::vector<Vector2> targetRoute;
	int nextRouteNum;
};