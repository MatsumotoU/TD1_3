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

	hpBreakEffectGH[0] = Novice::LoadTexture("./Resources/Images/playerHpBreakEffect1.png");
	hpBreakEffectGH[1] = Novice::LoadTexture("./Resources/Images/playerHpBreakEffect2.png");
	hpBreakEffectGH[2] = Novice::LoadTexture("./Resources/Images/playerHpBreakEffect3.png");

	particleManager.Init();
}

void PlayerHpUI::Update() {
	frameCount++;
	particleManager.Update();

	for (int i = 0; i < 3; i++) {
		if (i < player->GetHp()) {
			drawTransform[i].pos.x = transform.pos.x + 64.0f * static_cast<float>(i);
			drawTransform[i].pos.y = transform.pos.y + sinf(static_cast<float>(frameCount - (i * 6)) * 0.1f) * 3.0f;
			
			if (i + 1 == player->GetHp()) {
				
				if (player->GetHp() <= 1) {
					drawTransform[i].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.3f) * 0.2f;
					drawTransform[i].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.3f) * 0.2f;
				} else {
					drawTransform[i].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.2f;
					drawTransform[i].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.2f;
				}
				

			}

		} else {
			Eas::SimpleEaseIn(&drawTransform[i].scale.x, 0.0f, 0.3f);
			Eas::SimpleEaseIn(&drawTransform[i].scale.y, 0.0f, 0.3f);

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

		drawTransform[Clamp(oldHp - 1,0,2)].scale = { 1.5f,1.5f };
		oldHp = player->GetHp();
		particleManager.AnimEffect(drawTransform[Clamp(oldHp, 0, 2)].pos, transform.size, transform.angle, 3, 5, false, hpBreakEffectGH);
	}

	if (isChangeHp) {
		shakeRange = 10.0f;
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

			drawTf.pos.y = transform.pos.y + sinf(static_cast<float>(frameCount - (i * 6)) * 0.1f) * 3.0f;
			if (i + 1 == player->GetHp()) {
				
				if (player->GetHp() <= 1) {
					drawTf.scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.3f) * 0.2f;
					drawTf.scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.3f) * 0.2f;
				} else {
					drawTf.scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.2f;
					drawTf.scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.2f;
				}
				
			}

		} else {
			drawTf.pos.x = transform.pos.x + 64.0f * static_cast<float>(i) + Random(1.0f, -1.0f);
			drawTf.pos.y = transform.pos.y + Random(1.0f, -1.0f);
		}

		Render::DrawSprite(drawTf, *camera, WHITE, hpGH[2]);
		
		Render::DrawSprite(drawTransform[i], *camera, WHITE, hpGH[1]);

		Render::DrawSprite(drawTf, *camera, WHITE, hpGH[0]);

		particleManager.Draw();
	}

}

void PlayerHpUI::SetCamera(Camera* set) {
	camera = set;
	particleManager.SetCamera(set);
}

void PlayerHpUI::SetPlayer(Player* set) {
	player = set;
}
