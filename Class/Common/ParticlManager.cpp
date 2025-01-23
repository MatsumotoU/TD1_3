#define _USE_MATH_DEFINES
#include "ParticlManager.h"

void ParticlManager::Init() {

	frameCount = 0;
	particleCount = 0;
	camera = nullptr;

	for (int i = 0; i < kPlarticlMax; i++) {

		particls[i].Init();
		particls[i].GetPhysics2D()->SetVelocityLimit({ 256.0f,256.0f });

		if (camera != nullptr) {
			particls->SetCamera(camera);
		}
	}
}

void ParticlManager::Update() {
	particleCount = 0;
	for (int i = 0; i < kPlarticlMax; i++) {

		if (particls[i].GetIsActive()) {

			particleCount++;
			particls[i].Update();
		}
	}

	// 処理最大値の半分に来たら
	if (particleCount >= kPlarticlMax / 2) {

		// 3秒以上描画されてるパーティクルを消す
		for (int a = 0; a < kPlarticlMax; a++) {
			if (particls[a].GetIsActive()) {

				if (particls[a].GetFrameCount() >= 120) {

					if (!particls[a].GetIsFade()) {
						particls[a].SetIsFade(true);
						particls[a].SetFadeFrame(60);
						particls[a].SetMaxFadeFrame(120);
					}
				}
			}
		}
	}
}

void ParticlManager::Draw() {

	int num = 0;
	for (int i = 0; i < kPlarticlMax; i++) {

		if (particls[i].GetIsActive()) {

			particls[i].Draw();
			num++;
		}
	}

	//Novice::ScreenPrintf(0, 120, "particl = %d", num);
}

Particl* ParticlManager::GetParticle() {
	return particls;
}

void ParticlManager::SetCamera(Camera* set) {
	camera = set;
	for (int i = 0; i < kPlarticlMax; i++) {
		particls->SetCamera(set);
	}
}

void ParticlManager::SprayEffect(Vector2 pos, Vector2 size, int particlCap, int gh, unsigned int color) {

	for (int i = 0; i < particlCap; i++) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {

				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFade(true);
				particls[p].SetFadeFrame(20);
				particls[p].SetIsActive(true);
				particls[p].SetPos(pos);
				particls[p].SetSize(size);
				particls[p].GetPhysics2D()->AddForce({ static_cast<float>(rand() % 30 - 15) * 0.2f,static_cast<float>(rand() % 30 - 15) * 0.2f }, IMPACT);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				particls[p].SetColor(color);
				break;
			}
		}
	}
}

void ParticlManager::ExplosionEffect(Vector2 pos, Vector2 size, Vector2 force, int particlCap, int gh, unsigned int color) {

	for (int i = 0; i < particlCap; i++) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {

				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFalling(true);
				particls[p].SetIsActive(true);
				particls[p].SetPos(pos);
				particls[p].SetSize(size);
				particls[p].GetPhysics2D()->AddForce(force, IMPACT);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				particls[p].SetColor(color);
				break;
			}
		}
	}
}

void ParticlManager::ShowerEffect(Vector2 pos, Vector2 dir, int diffusivity, int particlCap, int gh) {

	if (frameCount % Clamp(particlCap, 1, 60) == 0) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {

				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFalling(true);
				particls[p].SetIsActive(true);
				particls[p].SetPos(pos);
				particls[p].SetSize({ 16.0f,16.0f });
				particls[p].GetPhysics2D()->AddForce({ dir.x * static_cast<float>(rand() % 10 - 5) * 10.0f,dir.y * static_cast<float>(rand() % (diffusivity + 1)) }, IMPACT);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				break;
			}
		}
	}
}

void ParticlManager::FromToEffect(Vector2 fromPos, Vector2* toPos, Vector2 size, int stackFrame, int particlCap, int gh, unsigned int color) {

	for (int i = 0; i < particlCap; i++) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {

				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFade(true);
				particls[p].SetFadeFrame(stackFrame * 3);
				particls[p].SetIsTarget(true);
				particls[p].SetStackFrame(stackFrame);
				particls[p].SetIsActive(true);
				particls[p].SetSize(size);
				particls[p].SetPos(fromPos);
				particls[p].SetTargetPos(toPos);
				particls[p].GetPhysics2D()->AddForce({ static_cast<float>(rand() % 30 - 15) * 0.4f,static_cast<float>(rand() % 30 - 15) * 0.4f }, IMPACT);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				particls[p].SetColor(color);

				break;
			}
		}
	}
}

void ParticlManager::PointEffect(Vector2 pos, int RemainingFrame, int gh, unsigned int color) {

	for (int p = 0; p < kPlarticlMax; p++) {

		if (!particls[p].GetIsActive()) {

			particls[p].Init();
			particls[p].SetCamera(camera);
			particls[p].SetIsFade(true);
			particls[p].SetFadeFrame(RemainingFrame);
			particls[p].SetPos(pos);
			particls[p].SetIsActive(true);
			particls[p].SetSize({ 16.0f,16.0f });
			particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
			particls[p].SetGraphHandle(gh);
			particls[p].SetColor(color);
			break;
		}
	}
}

void ParticlManager::SpriteEffect(Vector2 pos, Vector2 size, float angle, int RemainingFrame, int gh) {

	for (int p = 0; p < kPlarticlMax; p++) {

		if (!particls[p].GetIsActive()) {

			particls[p].Init();
			particls[p].SetCamera(camera);
			particls[p].SetIsFade(true);
			particls[p].SetFadeFrame(RemainingFrame);
			particls[p].SetMaxFadeFrame(RemainingFrame * 2);
			particls[p].SetPos(pos);
			particls[p].SetIsActive(true);
			particls[p].SetSize(size);
			particls[p].SetRotated(false);
			particls[p].SetAngle(angle);
			particls[p].SetGraphHandle(gh);
			break;
		}
	}

}

void ParticlManager::SlashEffect(Vector2 pos, Vector2 size, Vector2 dir, float power, int rnd, int RemainingFrame, int particlCap, int gh) {
	dir = Normalize(dir);

	for (int i = 0; i < particlCap; i++) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {

				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFade(true);
				particls[p].SetFadeFrame(RemainingFrame);
				particls[p].SetIsActive(true);
				particls[p].SetPos(pos);
				particls[p].SetSize(size);
				particls[p].GetPhysics2D()->AddForce(
					{ (dir.x + static_cast<float>(rand() % (rnd + 1) - (rnd / 2)) * 0.1f) * power,
					(dir.y + static_cast<float>(rand() % (rnd + 1) - (rnd / 2)) * 0.1f) * power }, IMPACT);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				particls[p].GetPhysics2D()->SetResistance(0.95f);
				particls[p].SetIsShirink(true);
				break;
			}
		}
	}
}

void ParticlManager::AnimEffect(Vector2 pos, Vector2 size, float angle, int animMaxFrame, int animSpeed, int isLoop, int* gh) {

	for (int p = 0; p < kPlarticlMax; p++) {

		if (!particls[p].GetIsActive()) {

			particls[p].Init();
			particls[p].SetCamera(camera);
			particls[p].SetIsActive(true);
			particls[p].SetPos(pos);
			particls[p].SetSize(size);
			particls[p].SetGraphHandle(gh[0]);
			particls[p].SetAngle(angle);

			particls[p].SetIsAnim(true);
			particls[p].SetAnimSpeed(animSpeed);
			particls[p].SetMaxAnimFrame(animMaxFrame);
			particls[p].SetAnimGH(gh);
			particls[p].SetIsLoop(isLoop);
			break;
		}
	}

}

// クラッカー（出し始める位置、大きさ、出す方向(ラジアン)、勢い、出す方向プラス最大何度ぶらすか(ディグリー)、出す方向マイナス何度ぶらすか(ディグリー)、平均描画時間、最大数、画像、色）
void ParticlManager::CrackerEffect(Vector2 pos, Vector2 size, float dir, float power, float max, float min, int RemainingFrame, int particleCap, int gh, unsigned int color) {
	for (int i = 0; i < particleCap; i++) {

		for (int p = 0; p < kPlarticlMax; p++) {

			if (!particls[p].GetIsActive()) {
				dir += Random(max, min) * (static_cast<float>(M_PI) / 180.0f);
				particls[p].Init();
				particls[p].SetCamera(camera);
				particls[p].SetIsFade(true);
				particls[p].SetFadeFrame(RemainingFrame + Random(10, -10));
				particls[p].SetIsActive(true);
				particls[p].SetPos(pos);
				particls[p].SetSize(size * Random(1.15f, 0.85f));
				particls[p].GetPhysics2D()->AddForce(
					{ (power + Random(power / 2.5f,-power / 2.5f)) * cosf(dir), (power + Random(power / 2.5f,-power / 2.5f)) * sinf(dir) }, IMPACT);
				particls[p].GetPhysics2D()->AddForce({ 0.0f,-0.2f }, ACCELERATION);
				particls[p].SetRotateDir(static_cast<float>(rand() % 10 - 5) * 0.1f);
				particls[p].SetGraphHandle(gh);
				particls[p].GetPhysics2D()->SetResistance(0.9f);
				particls[p].SetIsShirink(true);
				particls[p].SetColor(color);
				break;
			}
		}
	}
}
