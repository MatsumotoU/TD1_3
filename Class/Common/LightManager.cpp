#include "LightManager.h"

LightManager::LightManager() {
	lightGH = Novice::LoadTexture("./Resources/Images/Light600x600.png");
	for (int i = 0; i < kMaxLight; i++) {
		lights[i].SetGH(&lightGH);
	}
}

void LightManager::Init() {
	for (int i = 0; i < kMaxLight; i++) {
		lights[i].Init();
	}
}

void LightManager::Update() {
	for (int i = 0; i < kMaxLight; i++) {
		if (lights[i].GetIsActive()) {
			lights[i].Update();
		}
	}
}

void LightManager::Draw() {
	Novice::SetBlendMode(kBlendModeAdd);
	for (int i = 0; i < kMaxLight; i++) {
		if (lights[i].GetIsActive()) {
			lights[i].Draw();
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}

void LightManager::SetCamera(Camera* set) {
	for (int i = 0; i < kMaxLight; i++) {
		lights[i].SetCamera(set);
	}
}

void LightManager::SpawnLight(Vector2 pos, float radius, unsigned int color, float alpha) {
	for (int i = 0; i < kMaxLight; i++) {
		if (!lights[i].GetIsActive()) {
			lights[i].Init();
			lights[i].SetPos(pos);
			lights[i].SetIsActive(true);
			lights[i].SetScale({ radius / 600.0f,radius / 600.0f });
			lights[i].SetColor(color);
			lights[i].SetAlpha(alpha);
			return;
		}
	}
}

void LightManager::SpawnTrackingLight(Vector2* targetPos, float radius, unsigned int color, float alpha) {
	for (int i = 0; i < kMaxLight; i++) {
		if (!lights[i].GetIsActive()) {
			lights[i].Init();
			lights[i].SetIsActive(true);
			lights[i].SetTargetPos(targetPos);
			lights[i].SetScale({ radius / 600.0f,radius / 600.0f });
			lights[i].SetColor(color);
			lights[i].SetAlpha(alpha);
			return;
		}
	}
}
