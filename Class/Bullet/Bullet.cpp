#include "Bullet.h"

Bullet::Bullet() {
	transform.pos = { 0.0f,0.0f };
	transform.angle = 0.0f;
	transform.scale = { 1.0f,1.0f };
	transform.size = { 0.0f,0.0f };

	physics.Init();
	physics.SetResistance(1.0f);
	isActive = true;

	aliveFrame = 0;
	camera = nullptr;
	isShot = false;
	tag = "none";
	bulletGH = 0;
	color = WHITE;
}

void Bullet::Init() {
	transform.pos = { 0.0f,0.0f };
	transform.angle = 0.0f;
	transform.scale = { 1.0f,1.0f };
	transform.size = { 0.0f,0.0f };

	physics.Init();
	physics.SetResistance(1.0f);
	isActive = true;

	aliveFrame = 0;
	isShot = false;
	tag = "none";
	bulletGH = 0;
	color = RED;
}

void Bullet::Update() {
	Move();
	Destroy();
}

void Bullet::Draw() {
	Render::DrawSprite(transform, *camera, color, bulletGH);
}

void Bullet::Move() {
	physics.Update(&transform.pos);
}

void Bullet::Destroy() {
	// 自然消滅
	aliveFrame--;
	if (aliveFrame <= 0) {
		isShot = false;
	}
}

void Bullet::SetIsShot(int set) {
	isShot = set;
}

void Bullet::SetCamera(Camera* set) {
	camera = set;
}

void Bullet::SetGH(int set) {
	bulletGH = set;
}

void Bullet::SetTag(std::string set) {
	tag = set;
}

void Bullet::SetAliveFrame(int set) {
	aliveFrame = set;
}

int Bullet::GetIsShot() {
	return isShot;
}

std::string Bullet::GetTag() {
	return tag;
}

Vector2* Bullet::GetPosPtr() {
	return &transform.pos;
}
