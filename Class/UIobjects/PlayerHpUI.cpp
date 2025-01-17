#include "PlayerHpUI.h"
#include "Class/Player/Player.h"

void PlayerHpUI::Init() {
	transform = { 0.0f };
	transform.pos = { 320.0f,320.0f };
	transform.size = { 64.0f,64.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;
	drawHpCount = 0;

	hpGH = Novice::LoadTexture("./Resources/Images/playerHpUI.png");
}

void PlayerHpUI::Update() {
}

void PlayerHpUI::Draw() {

	for (int i = 0; i < player->GetHp(); i++) {
		Transform drawTf = transform;
		drawTf.pos.x = transform.pos.x + 64.0f * static_cast<float>(i);
		Render::DrawSprite(drawTf, *camera, WHITE, hpGH);
	}

}

void PlayerHpUI::SetCamera(Camera* set) {
	camera = set;
}

void PlayerHpUI::SetPlayer(Player* set) {
	player = set;
}
