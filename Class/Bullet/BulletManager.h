#pragma once
#include "Bullet.h"

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

	void SetCamera(Camera* camera);

private:

	Bullet bullets[BMG::kBulletMax];

};

