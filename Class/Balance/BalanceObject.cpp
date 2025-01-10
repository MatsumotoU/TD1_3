#include "BalanceObject.h"

BalanceObject::BalanceObject() {
	gh = 0;
	camera = nullptr;
	physics.Init();
	isFalling = true;
	parentPos = ZeroVector2;
	fallingTime = 0;
	isActive = false;

	transform = {
		{0.0f,0.0f},
		{48.0f,48.0f},
		{1.0f,1.0f},
		0.0f };
}

void BalanceObject::Init() {
	physics.Init();
	isFalling = true;
	parentPos = ZeroVector2;
	fallingTime = 0;
	gh = 0;

	transform = {
		{0.0f,0.0f},
		{48.0f,48.0f},
		{1.0f,1.0f},
		0.0f };
}

void BalanceObject::Update() {
	PhysicsUpdate();
	parentObjectUpdate();
}

void BalanceObject::Draw() {
	Render::DrawSprite(transform, *camera, WHITE, gh);
}

void BalanceObject::PhysicsUpdate() {

	if (isFalling) {
		fallingTime++;
		physics.AddGravity({ 0.0f,-1.0f }, 0.1f);
	}
	physics.Update(&transform.pos);
}

void BalanceObject::parentObjectUpdate() {

	if (!isFalling) {
		
		transform.pos = parentPos * MakeAffineMatrix(parentObjectTransform->scale, parentObjectTransform->angle, parentObjectTransform->pos);
	}
}

#pragma region Setter
void BalanceObject::SetCamera(Camera* set) {
	camera = set;
}
void BalanceObject::SetFalling(int set) {
	isFalling = set;
}
void BalanceObject::SetGraphHandle(int set) {
	gh = set;
}
void BalanceObject::SetParentObject(Transform* set) {
	parentObjectTransform = set;
}
#pragma endregion
#pragma region Getter
int BalanceObject::GetFalling() {
	return isFalling;
}

int BalanceObject::GetFallingTime() {
	return fallingTime;
}

#pragma endregion

void BalanceObject::ParentObject(Transform* parent) {
	SetParentObject(parent);
	parentPos = transform.pos - parent->pos;
}