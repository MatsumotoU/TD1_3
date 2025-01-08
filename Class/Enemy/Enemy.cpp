#include "Enemy.h"

Enemy::Enemy() {
	transform.pos = { 0.0f,0.0f };
	transform.angle = 0.0f;
	transform.scale = { 1.0f,1.0f };
	transform.size = { 32.0f,32.0f };

	physics.Init();
	isActive = true;

	isAlive = false;
	enemyGH = 0;
	color = WHITE;

	isHitAttack = false;
	hitDir = {0.0f,0.0f};

	isExprosion = false;
}

void Enemy::Init() {
}

void Enemy::Update() {
	physics.Update(&transform.pos);
}

void Enemy::Draw() {
	Render::DrawSprite(transform, *camera, color, enemyGH);

	if (isHitAttack) {
		Render::DrawLine(transform.pos, transform.pos + hitDir * 100.0f, *camera, RED);
		Render::DrawLine(transform.pos, transform.pos + -hitDir * 100.0f, *camera, RED);
	}
}

void Enemy::SetCamera(Camera* set) {
	camera = set;
}

void Enemy::SetIsAlive(int set) {
	isAlive = set;
}

void Enemy::SetIsHitAttack(int set) {
	isHitAttack = set;
}

void Enemy::SetHitAttackDir(Vector2 set) {
	hitDir = set;
}

int Enemy::GetIsAlive() {
	return isAlive;
}

int Enemy::GetIsHitAttack() {
	return isHitAttack;
}

Vector2 Enemy::GetHitDir() {
	return hitDir;
}

Vector2* Enemy::GetPosPtr() {
	return &transform.pos;
}
