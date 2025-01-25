#include "PlayerStopClockUI.h"
#include "Class/Common/MyEasing.h"
#include "Class/Scenes/GameStageScene.h"

void PlayerStopClockUI::Init() {
	clockGH = Novice::LoadTexture("./Resources/Images/Timer.png");
	clockHandlesGH = Novice::LoadTexture("./Resources/Images/clockHands.png");

	transform = { 0.0f };
	transform.scale = { 1.0f,1.0f };
	transform.size = { 512.0f,512.0f };

	clockHandleTransform = transform;
	playerAttackStopFrame = nullptr;
	playerAttackComboCount = nullptr;
	color = WHITE;
	alpha = 0.0f;
}

void PlayerStopClockUI::Update() {
	
	if (*playerAttackStopFrame > 0) {

		clockHandleTransform.angle = 
			6.8f * (static_cast<float>(*playerAttackStopFrame) / static_cast<float>(GMScene::maxPlayerAttackStopFrame / (*playerAttackComboCount + 1)));

		Eas::SimpleEaseIn(&alpha, 0.5f, 0.5f);
	} else {
		Eas::SimpleEaseIn(&alpha, 0.0f, 0.3f);
	}
}

void PlayerStopClockUI::Draw() {
	Render::DrawSprite(transform, *camera, ColorFade(color,alpha), clockGH);
	Render::DrawSprite(clockHandleTransform, *camera, ColorFade(color, alpha), clockHandlesGH);
}

void PlayerStopClockUI::SetCamera(Camera* set) {
	camera = set;
}

void PlayerStopClockUI::SetPlayerAttackStopFrame(int* set) {
	playerAttackStopFrame = set;
}

void PlayerStopClockUI::SetPlayerAttackComboCount(int* set) {
	playerAttackComboCount = set;
}
