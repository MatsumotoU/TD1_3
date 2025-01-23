#include "EnemyManager.h"
#include "Class/Common/Collision2D.h"

EnemyManager::EnemyManager() {
	enemyGH = Novice::LoadTexture("./Resources/Images/enemy.png");
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
		enemyes[i].SetGH(&enemyGH);
	}
}

void EnemyManager::Init() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
	}
}

void EnemyManager::Update() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive()) {

			enemyes[i].Update();
		}
	}
	EnemyCollision();
}

void EnemyManager::Draw() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive()) {

			enemyes[i].Draw();
		}
	}
}

void EnemyManager::SetCamera(Camera* set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].SetCamera(set);
	}
}

void EnemyManager::SetMapchip(Mapchip* set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].SetMapchip(set);
	}
}

void EnemyManager::SetPlayerPos(Vector2* set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].SetPlayerPos(set);
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

int EnemyManager::GetIsThereHitEnemy() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsHitAttack() && enemyes[i].GetIsAlive()) {
			return true;
		}
	}
	return false;
}

Enemy* EnemyManager::GetEnemyes() {
	return enemyes;
}

void EnemyManager::EnemyCollision() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive() && enemyes[i].GetIsAlive()) {
			
			for (int e = 0; e < EMG::kMaxEnemy; e++) {
				if (enemyes[e].GetIsActive() && enemyes[e].GetIsAlive()) {
					
					if (e != i) {

						CollisionRectangle(enemyes[i].GetPosPtr(), enemyes[i].GetSize(), enemyes[e].GetPos(), enemyes[e].GetSize(), true, true);
					}
				}
			}
		}
	}
}

void EnemyManager::SpawnEnemy(Vector2 pos, ENM::Type set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (!enemyes[i].GetIsActive() && !enemyes[i].GetIsAlive()) {

			enemyes[i].SetIsActive(true);
			enemyes[i].SetDeathFrame(ENM::kMaxDeathFrame);
			enemyes[i].SetPos(pos);
			enemyes[i].SetIsAlive(true);
			enemyes[i].SetIsHitAttack(false);
			enemyes[i].SetEnemyType(set);
			enemyes[i].TypeInit();
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
