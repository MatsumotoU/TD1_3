#pragma once
#include "Enemy.h"
#include "Class/Common/ParticlManager.h"

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
	int GetIsThereEnemies(Vector2 pos,Vector2 size);
	int GetIsHitScreenEnemies(Vector2 pos, Vector2 size);

	void EnemyCollision();
	void SpawnEnemy(Vector2 pos,ENM::Type set);
	Vector2 NearEnemy(Vector2 targetPos);

private:

	Camera* camera;
	Enemy enemyes[EMG::kMaxEnemy];
	int enemyGH;
	int shotEnemyGH;
	int arrowGH;
	Transform arrowTransform;
	ParticlManager particleManager;
	int findGH[3];
	int findSE;
};