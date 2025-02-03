#include "BulletManager.h"

BulletManager::BulletManager() {
	for (int i = 0; i < BMG::kBulletMax;i++) {
		bullets[i].Init();
	}
	camera = nullptr;
	framecount = 0;
}

void BulletManager::Init() {
	for (int i = 0; i < BMG::kBulletMax; i++) {
		bullets[i].Init();
	}

	particleManager.Init();
	particleManager.SetCamera(camera);

	framecount = 0;
}

void BulletManager::Update() {

	framecount++;

	// 各弾更新処理
	for (int i = 0; i < BMG::kBulletMax; i++) {
		if (bullets[i].GetIsActive() && bullets[i].GetIsShot()) {

			if (framecount % 3 == 0) {
				if (bullets[i].GetTag() == "enemy") {
					particleManager.SpriteEffect(bullets[i].GetPos(), bullets[i].GetSize(), 0.0f, 10, bullets[i].GetGH());
				}
			}

			bullets[i].Update();
		}
	}
	particleManager.Update();
	// 画面外の弾を消す
}

void BulletManager::Draw() {
	particleManager.Draw();
	int count = 0;
	for (int i = 0; i < BMG::kBulletMax; i++) {
		if (bullets[i].GetIsActive() && bullets[i].GetIsShot()) {
			
			bullets[i].Draw();
			count++;

		}
	}
	//Novice::ScreenPrintf(500, 0, "%d", count);
}

void BulletManager::ShotBullet(Vector2 pos, Vector2 size, Vector2 shotDir, float power,int aliveFrame, const std::string& tag, int bulletGH) {
	for (int i = 0; i < BMG::kBulletMax; i++) {
		if (bullets[i].GetIsActive() && !bullets[i].GetIsShot()) {

			bullets[i].Init();
			bullets[i].SetIsShot(true);
			bullets[i].SetPos(pos);
			bullets[i].SetSize(size);
			bullets[i].GetPhysics()->AddForce(shotDir * power, IMPACT);
			bullets[i].SetGH(bulletGH);
			bullets[i].SetTag(tag);
			bullets[i].SetAliveFrame(aliveFrame);
			bullets[i].SetAngle(atan2f(shotDir.y, shotDir.x));
			break;
		}
	}
}

Bullet* BulletManager::GetBullets() {
	return bullets;
}

void BulletManager::SetCamera(Camera* set) {
	for (int i = 0; i < BMG::kBulletMax; i++) {
		bullets[i].SetCamera(set);
	}
	camera = set;
	particleManager.SetCamera(set);
}

void BulletManager::SetLightManager(LightManager* set) {
	lightManager = set;
}
