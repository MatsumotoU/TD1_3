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

	Enemy* GetEnemyes();

	void SpawnEnemy(Vector2 pos, Vector2 size);
	Vector2 NearEnemy(Vector2 targetPos);

private:

	Enemy enemyes[EMG::kMaxEnemy];

};