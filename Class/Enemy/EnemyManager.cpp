#include "EnemyManager.h"

EnemyManager::EnemyManager() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
	}
}

void EnemyManager::Init() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
	}
}

void EnemyManager::Update() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && enemyes[i].GetIsAlive()) {

			enemyes[i].Update();
		}
	}
}

void EnemyManager::Draw() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && enemyes[i].GetIsAlive()) {

			enemyes[i].Draw();
		}
	}
}

void EnemyManager::SetCamera(Camera* set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && !enemyes[i].GetIsAlive()) {

			enemyes[i].SetCamera(set);
		}
	}
}

int EnemyManager::GetRemainEnemies() {
	int count = 0;
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && enemyes[i].GetIsAlive()) {
			count++;
		}
	}
	return count;
}

Enemy* EnemyManager::GetEnemyes() {
	return enemyes;
}

void EnemyManager::SpawnEnemy(Vector2 pos, Vector2 size) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && !enemyes[i].GetIsAlive()) {

			enemyes[i].SetPos(pos);
			enemyes[i].SetSize(size);
			enemyes[i].SetIsAlive(true);
			enemyes[i].SetIsHitAttack(false);
			break;
		}
	}
}

Vector2 EnemyManager::NearEnemy(Vector2 targetPos) {
	Vector2 result = { 999.0f,999.0f };
	float length = 9999.0f;

	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && enemyes[i].GetIsAlive()) {

			if (Length(enemyes[i].GetPos() - targetPos) <= length) {
				result = enemyes[i].GetPos();
				length = Length(enemyes[i].GetPos() - targetPos);
			}
		}
	}
	return result;
}
