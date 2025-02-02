#include "Light.h"
#include "MyEasing.h"

Light::Light() {
	transform = { 0.0f };
	transform.size = { 600.0f,600.0f };
	alpha = 1.0f;
	targetPos = nullptr;
	isActive = false;
	camera = nullptr;
}

void Light::Init() {
	alpha = 1.0f;
	targetPos = nullptr;
	isActive = false;
	frameCount = 0;
	spawnScale = { 0.0f,0.0f };
}

void Light::Update() {
	frameCount++;

	if (targetPos != nullptr) {
		transform.pos = *targetPos;
	} else {
		
		isActive = false;
	}

	transform.scale.x += sinf(static_cast<float>(frameCount) * 0.1f) * 0.001f;
	transform.scale.y += sinf(static_cast<float>(frameCount) * 0.1f) * 0.001f;

	alpha += sinf(static_cast<float>(frameCount) * 0.1f) * 0.01f;
	alpha = Clamp(alpha, 0.0f, 1.0f);
}

void Light::Draw() {
	Render::DrawSprite(transform, *camera, ColorFade(color,alpha), *gh);
}

void Light::SetGH(int* set) {
	gh = set;
}

void Light::SetCamera(Camera* set) {
	camera = set;
}

void Light::SetTargetPos(Vector2* set) {
	targetPos = set;
}

void Light::SetColor(unsigned int set) {
	color = set;
}

void Light::SetAlpha(float set) {
	alpha = set;
}
