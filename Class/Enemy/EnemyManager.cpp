#include "EnemyManager.h"
#include "Class/Common/Collision2D.h"

EnemyManager::EnemyManager() {
	enemyGH = Novice::LoadTexture("./Resources/Images/enemy.png");
	shotEnemyGH = Novice::LoadTexture("./Resources/Images/shotEnemy.png");
	arrowGH = Novice::LoadTexture("./Resources/Images/enemyTargetArrow.png");
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
		enemyes[i].SetGH(&enemyGH);
	}
	camera = nullptr;
	arrowTransform = { 0.0f };
	
	findGH[0] = Novice::LoadTexture("./Resources/Images/find1.png");
	findGH[1] = Novice::LoadTexture("./Resources/Images/find2.png");
	findGH[2] = Novice::LoadTexture("./Resources/Images/find3.png");
	findSE = Novice::LoadAudio("./Resources/Sounds/select.mp3");
}

void EnemyManager::Init() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].Init();
	}
	particleManager.Init();
}

void EnemyManager::Update() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive()) {

			enemyes[i].Update();

			if (enemyes[i].GetIsFindPlayer()) {
				enemyes[i].SetIsFindPlayer(false);
				particleManager.AnimEffect({ enemyes[i].GetPos().x,enemyes[i].GetPos().y + 64.0f }, {64.0f,64.0f}, 0.0f, 3, 5, false, findGH);
				Novice::PlayAudio(findSE,false, 0.2f);
			}
		}
	}
	EnemyCollision();
	particleManager.Update();
}

void EnemyManager::Draw() {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsActive()) {

			if (camera->IsInScreen(enemyes[i].GetPos(), enemyes[i].GetSize())) {
				enemyes[i].Draw();
			} else {
				
				//Render::DrawSprite()
			}
		}
	}
	particleManager.Draw();
}

void EnemyManager::SetCamera(Camera* set) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		enemyes[i].SetCamera(set);
	}
	camera = set;
	particleManager.SetCamera(set);
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

int EnemyManager::GetIsThereEnemies(Vector2 pos, Vector2 size) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsAlive()) {
			if(IsHitRectangle(pos, size, enemyes[i].GetPos(), enemyes[i].GetSize())){
				return true;
			}
		}
	}
	return false;
}

int EnemyManager::GetIsHitScreenEnemies(Vector2 pos, Vector2 size) {
	for (int i = 0; i < EMG::kMaxEnemy; i++) {
		if (enemyes[i].GetIsAlive()) {
			if (IsHitRectangle(pos, size, enemyes[i].GetScreenPos(), enemyes[i].GetSize())) {
				return true;
			}
		}
	}
	return false;
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

			enemyes[i].Init();
			enemyes[i].SetIsActive(true);
			enemyes[i].SetDeathFrame(ENM::kMaxDeathFrame);
			enemyes[i].SetPos(pos);
			enemyes[i].SetIsAlive(true);
			enemyes[i].SetIsHitAttack(false);
			enemyes[i].SetEnemyType(set);
			enemyes[i].TypeInit();
			enemyes[i].SetIsSpawning(true);

			switch (set)
			{
			case ENM::None:
				enemyes[i].SetGH(&enemyGH);
				break;
			case ENM::Melee:
				enemyes[i].SetGH(&enemyGH);
				break;
			case ENM::Shot:
				enemyes[i].SetGH(&shotEnemyGH);
				break;
			case ENM::Shield:
				enemyes[i].SetGH(&enemyGH);
				break;
			default:
				break;
			}

			break;
		}
	}
}

Vector2 EnemyManager::NearEnemy(Vector2 targetPos) {
	Vector2 result = { 9999999.0f,9999999.0f };
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
