#include "GameScore.h"

void GameScore::Init() {
	score.Init();
	aliveFrame = 120;

	isActive = false;
	transform.pos = { 0.0f,0.0f };
	transform.scale = { 1.0f,1.0f };
	transform.size = { 64.0f,64.0f };
	transform.angle = 0.0f;

	physics.Init();
}

void GameScore::Update() {

	score.SetPos(transform.pos);
	score.SetTargetNum(scoreNum);
	score.Update();

	if (score.GetNumber() == scoreNum) {
		if (aliveFrame > 0) {
			aliveFrame--;
		}
	}

	if (aliveFrame <= 0) {
		isActive = false;
	}

	if (isActive) {
		physics.AddGravity({ 0.0f,-1.0f }, 0.3f);
		physics.Update(&transform.pos);

		if (transform.pos.y < groundPos.y) {
			physics.SetVelocity({ physics.GetVelocity().x,-physics.GetVelocity().y * 0.8f });
			physics.SetAcceleration({ physics.GetAcceleration().x,-physics.GetAcceleration().x * 0.98f });
			physics.Update(&transform.pos);
		}
	}
}

void GameScore::Draw() {
	Transform plusTf = transform;
	plusTf.size = { 64.0f,64.0f };
	plusTf.pos.x -= 32.0f + 32.0f * static_cast<float>(score.GetDigit());

	if (aliveFrame <= 30) {

		if (aliveFrame % 2) {
			Render::DrawSprite(plusTf, *camera, WHITE, *plusGH);
			score.Draw(camera, scoreGH);
		}

	} else {

		
		Render::DrawSprite(plusTf, *camera, WHITE, *plusGH);
		score.Draw(camera, scoreGH);
	}
	
}

void GameScore::SetGH(int* set) {
	scoreGH = set;
}

void GameScore::SetPlusGH(int* set) {
	plusGH = set;
}

void GameScore::SetCamera(Camera* set) {
	camera = set;
}

void GameScore::SetScore(int set) {
	scoreNum = set;
}

void GameScore::SetGroundPos(Vector2 set) {
	groundPos = set;
}
