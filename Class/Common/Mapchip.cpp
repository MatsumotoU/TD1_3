#include "Mapchip.h"
#include "Class/Common/Render.h"
#include "Class/Common/Collision2D.h"

#include "Class/Player/Player.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Bullet/BulletManager.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


Mapchip::Mapchip() {
	frameCount = 0;
	isTransition = nullptr;

	mapchipGH[0] = 0;
	mapchipGH[1] = Novice::LoadTexture("./Resources/Images/block1.png");
	mapchipGH[2] = 0;
	mapchipGH[3] = 0;
	mapchipGH[4] = 0;
	mapchipGH[5] = 0;
	mapchipGH[6] = 0;
	mapchipGH[7] = 0;
	mapchipGH[8] = 0;
	mapchipGH[9] = 0;

	camera = nullptr;
}

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

int Mapchip::GetEnemyNum() {
	int count = 0;
	for (int y = 0; y < kMapSizeY; y++) {
		for (int x = 0; x < kMapSizeX; x++) {

			if (map[y][x] >= 2) {
				count++;
			}
		}
	}
	return count;
}

int Mapchip::GetIsFromToVisionClear(Vector2 from, Vector2 to) {
	for (float i = 0.0f; i <= 1.0f; i += 0.1f) {

		int x = static_cast<int>(((from.x * i) + (to.x * (1.0f - i))) / kMapChipSize.x);
		int y = static_cast<int>(((from.y * i) + (to.y * (1.0f - i))) / kMapChipSize.y);

		if (x < 0 || x > kMapSizeX || y < 0 || y > kMapSizeY) {
			return false;
		}

		if (map[y][x] == 1) {
			return false;
		}
	}
	return true;
}

void Mapchip::SetCamera(Camera* set) {
	camera = set;
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

						if (player->GetIsAlive()) {
							CollisionRectangle(player->GetPosPtr(), player->GetSize(), blockPos, kMapChipSize, true, true);

							if (player->GetIsDash()) {
								camera->shakeRange += player->GetPhysics()->GetVelocity();
								player->SetIsDash(false);

							}
						} else {

							if (fabsf(player->GetPos().x - blockPos.x) <= fabsf(player->GetPos().y - blockPos.y)) {
								player->GetPhysics()->SetVelocity(
									{ player->GetPhysics()->GetVelocity().x,
									-player->GetPhysics()->GetVelocity().y });
							} else {
								player->GetPhysics()->SetVelocity(
									{ -player->GetPhysics()->GetVelocity().x,
									player->GetPhysics()->GetVelocity().y });
							}
							
						}
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

void Mapchip::SpawnEnemy() {
	for (int y = 0; y < kMapSizeY; y++) {
		for (int x = 0; x < kMapSizeX; x++) {
			if (map[y][x] == 2) {
				enemyManager->SpawnEnemy({ 32.0f + 64.0f * static_cast<float>(x),32.0f + 64.0f * static_cast<float>(y) },ENM::Melee);
			}
			if (map[y][x] == 3) {
				enemyManager->SpawnEnemy({ 32.0f + 64.0f * static_cast<float>(x),32.0f + 64.0f * static_cast<float>(y) }, ENM::Shot);
			}
			if (map[y][x] == 4) {
				enemyManager->SpawnEnemy({ 32.0f + 64.0f * static_cast<float>(x),32.0f + 64.0f * static_cast<float>(y) }, ENM::Shield);
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
}

void Mapchip::SetMap(int setMap[kMapSizeY][kMapSizeX]) {

	for (int y = 0; y < kMapSizeY; y++) {

		for (int x = 0; x < kMapSizeX; x++) {

			map[y][x] = setMap[y][x];
		}
	}
}

void Mapchip::Draw() {
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
						Render::DrawSprite(blockTransform, *camera, WHITE, mapchipGH[map[y][x] % kMapChipGraphHandleNumMax]);
					}
				}
			}
		}
	}
}

void Mapchip::Update() {
	frameCount++;
}

void Mapchip::ImGuiUpdate() {
#ifdef _DEBUG



#endif // _DEBUG
}

std::vector<Vector2> Mapchip::GetMapStoG(Vector2 start, Vector2 goal) {
	std::vector<Vector2> result;

	int startMapPosX = static_cast<int>((start.x) / kMapChipSize.x);
	int startMapPosY = static_cast<int>((start.y) / kMapChipSize.y);

	int goalMapPosX = static_cast<int>((goal.x) / kMapChipSize.x);
	int goalMapPosY = static_cast<int>((goal.y) / kMapChipSize.y);

	// ほぼ同じ位置なら目標地点を返す
	if (startMapPosX == goalMapPosX && startMapPosY == goalMapPosY) {
		result.push_back(goal);
		return result;
	}

	// 判定しない部分作成
	int mapRoute[kMapSizeY][kMapSizeX] = { 0 };
	for (int y = 0; y < kMapSizeY; y++) {
		for (int x = 0; x < kMapSizeX; x++) {
			mapRoute[y][x] = -1;
		}
	}

	// スタート地点を0手に設定
	mapRoute[startMapPosY][startMapPosX] = 0;

	// 移動できるマスと距離を出す
	int searchCount = 0;
	while (searchCount < 100)
	{
		for (int y = 0; y < kMapSizeY; y++) {
			for (int x = 0; x < kMapSizeX; x++) {

				// 進める道探索
				if (mapRoute[y][x] == searchCount) {

					// 右の探索
					if (x + 1 < kMapSizeX && map[y][x + 1] != 1 && mapRoute[y][x + 1] == -1) {
						mapRoute[y][x + 1] = searchCount + 1;
					}
					// 左の探索
					if (x - 1 > 0 && map[y][x - 1] != 1 && mapRoute[y][x - 1] == -1) {
						mapRoute[y][x - 1] = searchCount + 1;
					}
					// 上の探索
					if (y + 1 < kMapSizeY && map[y + 1][x] != 1 && mapRoute[y + 1][x] == -1) {
						mapRoute[y + 1][x] = searchCount + 1;
					}
					// 下の探索
					if (y - 1 > 0 && map[y - 1][x] != 1 && mapRoute[y - 1][x] == -1) {
						mapRoute[y - 1][x] = searchCount + 1;
					}
				}
			}
		}
		searchCount++;
	}

	// ゴールまでの道を作成
	int goalSteps = mapRoute[goalMapPosY][goalMapPosX];
	int stepX = goalMapPosX;
	int stepY = goalMapPosY;
	for (int i = goalSteps; i >= 0; i--) {

		if (stepX + 1 < kMapSizeX && mapRoute[stepY][stepX + 1] == i) {// 右の探索
			result.push_back({ kMapChipSize.x * 0.5f + static_cast<float>(stepX + 1) * kMapChipSize.x ,kMapChipSize.y * 0.5f + static_cast<float>(stepY) * kMapChipSize.y });
			stepX++;
		} else if (stepX - 1 > 0 && mapRoute[stepY][stepX - 1] == i) {// 左の探索
			result.push_back({ kMapChipSize.x * 0.5f + static_cast<float>(stepX - 1) * kMapChipSize.x ,kMapChipSize.y * 0.5f + static_cast<float>(stepY) * kMapChipSize.y });
			stepX--;
		} else if (stepY + 1 < kMapSizeY && mapRoute[stepY + 1][stepX] == i) {// 上の探索
			result.push_back({ kMapChipSize.x * 0.5f + static_cast<float>(stepX) * kMapChipSize.x ,kMapChipSize.y * 0.5f + static_cast<float>(stepY + 1) * kMapChipSize.y });
			stepY++;
		} else if (stepY - 1 > 0 && mapRoute[stepY - 1][stepX] == i) {// 下の探索
			result.push_back({ kMapChipSize.x * 0.5f + static_cast<float>(stepX) * kMapChipSize.x ,kMapChipSize.y * 0.5f + static_cast<float>(stepY - 1) * kMapChipSize.y });
			stepY--;
		}
	}

	return result;
}
