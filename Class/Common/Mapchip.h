#pragma once
#include <vector>

#include "Class/Common/MyFileIO.h"
#include "Class/Common/Camera.h"
#include "Class/Common/ParticlManager.h"

const int kMapSizeX = 32;
const int kMapSizeY = 32;
const Vector2 kMapChipSize = { 64.0f,64.0f };
const float kMapChipNum = 10;
const int kMapChipGraphHandleNumMax = 10;
const Vector2 kMapCenter = {
	static_cast<float>(kMapSizeX / 2) * kMapChipSize.x,
	static_cast<float>(kMapSizeY / 2) * kMapChipSize.y };

class Player;
class EnemyManager;
class BulletManager;

class Mapchip
{
public:

	Mapchip();

	void SetIsTransition(int* set);

	int GetIsHit(Vector2 pos);
	int GetMapNum(Vector2 pos);
	int GetEnemyNum();
	int GetIsFromToVisionClear(Vector2 from, Vector2 to);

	void SetCamera(Camera* set);
	void SetPlayer(Player* set);
	void SetEnemyManager(EnemyManager* set);
	void SetBulletManager(BulletManager* set);

	void PlayerMapCollision();
	void EnemyMapCollision();
	void BulletMapCollision();

	void SpawnEnemy();
	void LoadMap(std::string setFilePath);
	void SetMap(int setMap[kMapSizeY][kMapSizeX]);
	void Draw();
	void Update();

	void ImGuiUpdate();

	std::vector<Vector2> GetMapStoG(Vector2 start, Vector2 goal);

private:

	int* isTransition;
	int* isCrear;
	int frameCount;
	int map[kMapSizeY][kMapSizeX];
	int mapchipGH[kMapChipGraphHandleNumMax];

	MyFileIO file;

	Player* player;
	EnemyManager* enemyManager;
	BulletManager* bulletManager;
	Camera* camera;
	ParticlManager particleManager;

	Vector2 drawPos[kMapSizeX * kMapSizeY];

	int smokeGH;
	int smallHitEffectGH[3];
	int enemyBulletEffectGH;
};

