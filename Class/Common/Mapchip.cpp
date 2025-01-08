#include "Mapchip.h"
#include "Class/Common/Render.h"
#include "Class/Common/Collision2D.h"

#include "Class/Player/Player.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Bullet/BulletManager.h"

void Mapchip::SetIsTransition(int* set) {
	isTransition = set;
}

int Mapchip::GetIsHit(Vector2 pos) {
	int mapX = static_cast<int>(pos.x / kMapChipSize.x);
	int mapY = static_cast<int>(pos.y / kMapChipSize.y);

	// マップ外参照例外処理
	if (mapX < 0 || mapX >= kMapSizeX ||
		mapY < 0 || mapY >= kMapSizeY) {
		return false;
	}

	// データがあれば真を返す
	if (map[mapY][mapX] != 0) {
		return true;
	} else {
		return false;
	}
}

int Mapchip::GetMapNum(Vector2 pos) {
	int mapX = static_cast<int>(pos.x / kMapChipSize.x);
	int mapY = static_cast<int>(pos.y / kMapChipSize.y);

	// マップ外参照例外処理
	if (mapX < 0 || mapX >= kMapSizeX ||
		mapY < 0 || mapY >= kMapSizeY) {
		return 0;
	}

	return map[mapY][mapX];
}

void Mapchip::SetPlayer(Player* set) {
	player = set;
}

void Mapchip::SetEnemyManager(EnemyManager* set) {
	enemyManager = set;
}

void Mapchip::SetBulletManager(BulletManager* set) {
	bulletManager = set;
}

void Mapchip::PlayerMapCollision() {
	if (player == nullptr) {
		return;
	}

	for (int y = 0; y < kMapSizeY; y++) {

		for (int x = 0; x < kMapSizeX; x++) {

			Vector2 blockPos = {
				(kMapChipSize.x * 0.5f) + kMapChipSize.x * static_cast<float>(x),
				(kMapChipSize.y * 0.5f) + kMapChipSize.y * static_cast<float>(y) };

			// 計算量を減らす
			if (Length(player->GetPos() - blockPos) <= Length(player->GetSize()) + Length(kMapChipSize)) {

				if (map[y][x] == 1) {
					if (IsHitRectangle(player->GetPos(), player->GetSize(), blockPos, kMapChipSize)) {

						CollisionRectangle(player->GetPosPtr(), player->GetSize(), blockPos, kMapChipSize, true, true);
					}
				}
			}

		}
	}
}

void Mapchip::EnemyMapCollision() {
	if (enemyManager == nullptr) {
		return;
	}

	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (enemyManager->GetEnemyes()[e].GetIsAlive()) {

			for (int y = 0; y < kMapSizeY; y++) {
				for (int x = 0; x < kMapSizeX; x++) {

					Vector2 blockPos = {
						(kMapChipSize.x * 0.5f) + kMapChipSize.x * static_cast<float>(x),
						(kMapChipSize.y * 0.5f) + kMapChipSize.y * static_cast<float>(y) };

					// 計算量を減らす
					if (Length(enemyManager->GetEnemyes()[e].GetPos() - blockPos) <= Length(enemyManager->GetEnemyes()[e].GetSize()) + Length(kMapChipSize)) {

						if (map[y][x] == 1) {
							if (IsHitRectangle(enemyManager->GetEnemyes()[e].GetPos(), enemyManager->GetEnemyes()[e].GetSize(), blockPos, kMapChipSize)) {

								CollisionRectangle(enemyManager->GetEnemyes()[e].GetPosPtr(), enemyManager->GetEnemyes()[e].GetSize(), blockPos, kMapChipSize, true, true);
							}
						}
					}
				}
			}
		}
	}
}

void Mapchip::BulletMapCollision() {
	for (int b = 0; b < BMG::kBulletMax; b++) {
		if (bulletManager->GetBullets()[b].GetIsShot()) {

			for (int y = 0; y < kMapSizeY; y++) {
				for (int x = 0; x < kMapSizeX; x++) {

					Vector2 blockPos = {
						(kMapChipSize.x * 0.5f) + kMapChipSize.x * static_cast<float>(x),
						(kMapChipSize.y * 0.5f) + kMapChipSize.y * static_cast<float>(y) };

					// 計算量を減らす
					if (Length(bulletManager->GetBullets()[b].GetPos() - blockPos) <= Length(bulletManager->GetBullets()[b].GetSize()) + Length(kMapChipSize)) {

						if (map[y][x] == 1) {
							if (IsHitRectangle(bulletManager->GetBullets()[b].GetPos(), bulletManager->GetBullets()[b].GetSize(), blockPos, kMapChipSize)) {

								bulletManager->GetBullets()[b].SetIsShot(false);
							}
						}
					}
				}
			}
		}
	}
}

void Mapchip::LoadMap(std::string setFilePath) {
	file.LoadFilePath(setFilePath);
	file.LoadArr2DData();

	for (int y = 0; y < kMapSizeY; y++) {

		for (int x = 0; x < kMapSizeX; x++) {
			map[y][x] = file.GetArr2DData()[(kMapSizeY - 1) - y][x];
		}
	}

	frameCount = 0;
	isTransition = nullptr;
}

void Mapchip::SetMap(int setMap[kMapSizeY][kMapSizeX]) {

	for (int y = 0; y < kMapSizeY; y++) {

		for (int x = 0; x < kMapSizeX; x++) {

			map[y][x] = setMap[y][x];
		}
	}
}

void Mapchip::Draw(Camera* camera) {
	for (int y = 0; y < kMapSizeY; y++) {

		for (int x = 0; x < kMapSizeX; x++) {

			// 画面外の処理を飛ばす
			if (camera->IsInScreen({
				(kMapChipSize.x * 0.5f) + kMapChipSize.x * static_cast<float>(x),
				(kMapChipSize.y * 0.5f) + kMapChipSize.y * static_cast<float>(y) }, kMapChipSize)) {

				// 何かしらと当たった時
				if (map[y][x] != 0) {

					if (map[y][x] == 1) {

						Transform blockTransform = { 0 };
						blockTransform.size = kMapChipSize;
						blockTransform.scale = { 1.0f,1.0f };
						blockTransform.pos = {
							(kMapChipSize.x * 0.5f) + kMapChipSize.x * static_cast<float>(x),
							(kMapChipSize.y * 0.5f) + kMapChipSize.y * static_cast<float>(y) };
						Render::DrawSprite(blockTransform, *camera, WHITE, 0);
					}
				}
			}
		}
	}
}

void Mapchip::Update() {
	frameCount++;
}
