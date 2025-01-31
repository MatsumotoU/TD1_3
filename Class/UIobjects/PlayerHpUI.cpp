#include "PlayerHpUI.h"
#include "Class/Player/Player.h"
#include "Class/Common/MyEasing.h"

void PlayerHpUI::Init() {
	transform = { 0.0f };
	transform.pos = { -570.0f,310.0f };
	transform.size = { 64.0f,64.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;
	drawHpCount = 0;

	frameCount = 0;

	for (int i = 0; i < 3; i++) {
		drawTransform[i] = transform;
	}
	oldHp = 3;
	isChangeHp = false;
	hpGH[0] = Novice::LoadTexture("./Resources/Images/playerHpUI1.png");
	hpGH[1] = Novice::LoadTexture("./Resources/Images/playerHpUI2.png");
	hpGH[2] = Novice::LoadTexture("./Resources/Images/playerHpUI3.png");
}

void PlayerHpUI::Update() {
	frameCount++;

	for (int i = 0; i < 3; i++) {
		if (i < player->GetHp()) {
			drawTransform[i].pos.x = transform.pos.x + 64.0f * static_cast<float>(i);
			drawTransform[i].pos.y = transform.pos.y + sinf(static_cast<float>(frameCount - (i * 6)) * 0.1f) * 5.0f;

		} else {
			Eas::SimpleEaseIn(&drawTransform[i].scale.x, 0.0f, 0.1f);
			Eas::SimpleEaseIn(&drawTransform[i].scale.y, 0.0f, 0.1f);

			drawTransform[i].pos.x = transform.pos.x + 64.0f * static_cast<float>(i);
			drawTransform[i].pos.y = transform.pos.y;

			drawTransform[i].pos.x += Random(shakeRange, -shakeRange);
			drawTransform[i].pos.y += Random(shakeRange, -shakeRange);
		}
	}

	if (player->GetHp() != oldHp) {
		if (!isChangeHp) {
			isChangeHp = true;
		}
		oldHp = player->GetHp();
	}

	if (isChangeHp) {
		shakeRange = 20.0f;
		isChangeHp = false;
	}

	if (shakeRange > 0.0f) {
		shakeRange--;
	}
}

void PlayerHpUI::Draw() {

	for (int i = 0; i < player->GetMaxHp(); i++) {

		Transform drawTf = transform;
		drawTf.pos.x = transform.pos.x + 64.0f * static_cast<float>(i);
		if (i < player->GetHp()) {
			drawTf.pos.y = transform.pos.y + sinf(static_cast<float>(frameCount - (i * 6)) * 0.1f) * 5.0f;
		} else {
			drawTf.pos.x = transform.pos.x + 64.0f * static_cast<float>(i) + Random(2.0f, -2.0f);
			drawTf.pos.y = transform.pos.y + Random(2.0f, -2.0f);
		}

		Render::DrawSprite(drawTf, *camera, WHITE, hpGH[2]);
		
		Render::DrawSprite(drawTransform[i], *camera, WHITE, hpGH[1]);

		Render::DrawSprite(drawTf, *camera, WHITE, hpGH[0]);
	}

}

void PlayerHpUI::SetCamera(Camera* set) {
	camera = set;
}

void PlayerHpUI::SetPlayer(Player* set) {
	player = set;
}
