#include "BulletManager.h"

BulletManager::BulletManager() {
	for (int i = 0; i < BMG::kBulletMax;i++) {
		bullets[i].Init();
	}
}

void BulletManager::Init() {
	for (int i = 0; i < BMG::kBulletMax; i++) {
		bullets[i].Init();
	}
}

void BulletManager::Update() {
	// 各弾更新処理
	for (int i = 0; i < BMG::kBulletMax; i++) {
		if (bullets[i].GetIsActive() && bullets[i].GetIsShot()) {

			bullets[i].Update();
		}
	}

	// 画面外の弾を消す
}

void BulletManager::Draw() {
	int count = 0;
	for (int i = 0; i < BMG::kBulletMax; i++) {
		if (bullets[i].GetIsActive() && bullets[i].GetIsShot()) {
			
			bullets[i].Draw();
			count++;

		}
	}
	Novice::ScreenPrintf(500, 0, "%d", count);
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

void BulletManager::SetCamera(Camera* camera) {
	for (int i = 0; i < BMG::kBulletMax; i++) {
		bullets[i].SetCamera(camera);
	}
}
