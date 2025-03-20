#pragma once
#include "Bullet.h"
#include "Class/Common/LightManager.h"
#include "Class/Common/ParticlManager.h"

namespace BMG {
	const int kBulletMax = 128;
}

class BulletManager
{
public:
	BulletManager();

	void Init();
	void Update();
	void Draw();

	void ShotBullet(Vector2 pos, Vector2 size,Vector2 shotDir,float power, int aliveFrame, const std::string& tag, int bulletGH);

	Bullet* GetBullets();

	void SetCamera(Camera* set);
	void SetLightManager(LightManager* set);

private:

	int attackSE;
	int framecount;
	Camera* camera;
	Bullet bullets[BMG::kBulletMax];
	LightManager* lightManager;
	ParticlManager particleManager;

};

