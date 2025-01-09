#pragma once
#include "Class/Common/Particl.h"
#include "Class/Common/Camera.h"

// パーティクル最大数
const int kPlarticlMax = 128;

class ParticlManager
{
public:

	void Init();
	void Update();
	void Draw();

	Particl* GetParticle();

	void SetCamera(Camera* set);

	void SprayEffect(Vector2 pos, Vector2 size, int particlCap, int gh, unsigned int color);
	void ExplosionEffect(Vector2 pos, Vector2 size,Vector2 force,int particlCap, int gh,unsigned int color);
	void ShowerEffect(Vector2 pos, Vector2 dir, int diffusivity, int particlCap, int gh);
	void FromToEffect(Vector2 fromPos, Vector2* toPos,Vector2 size, int stackFrame, int particlCap, int gh, unsigned int color);
	void PointEffect(Vector2 pos, int RemainingFrame, int gh);
	void SpriteEffect(Vector2 pos, Vector2 size, float angle, int RemainingFrame, int gh);
	void SlashEffect(Vector2 pos, Vector2 size, Vector2 dir, float power, int rnd, int RemainingFrame, int particlCap, int gh);
	void AnimEffect(Vector2 pos, Vector2 size,float angle, int animMaxFrame, int animSpeed, int isLoop, int* gh);

private:

	int frameCount;
	int particleCount;
	Particl particls[kPlarticlMax];
	Camera* camera;
};

