#pragma once
#include "Enemy.h"

namespace EMG {
	const int kMaxEnemy = 64;
}

class EnemyManager
{
public:

	EnemyManager();

	void Init();
	void Update();
	void Draw();

	void SetCamera(Camera* set);
	void SetMapchip(Mapchip* set);
	void SetPlayerPos(Vector2* set);

	int GetRemainEnemies();
	int GetIsThereHitEnemy();
	Enemy* GetEnemyes();

	void EnemyCollision();
	void SpawnEnemy(Vector2 pos,ENM::Type set);
	Vector2 NearEnemy(Vector2 targetPos);

private:

	Enemy enemyes[EMG::kMaxEnemy];
	int enemyGH;

};