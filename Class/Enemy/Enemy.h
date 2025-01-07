#pragma once
#include "Class/Common/Render.h"
#include "Class/Common/GameObject.h"

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

	int GetIsAlive();
	int GetIsHitAttack();
	Vector2 GetHitDir();

private:

	int isExprosion;
	int isAlive;
	Camera* camera;
	int enemyGH;
	unsigned int color;

	int isHitAttack;
	Vector2 hitDir;
};