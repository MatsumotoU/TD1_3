#pragma once
#include "Light.h"

const int kMaxLight = 128;

class LightManager 
{
public:

	LightManager();

	void Init();
	void Update();
	void Draw();

	void SetCamera(Camera* set);

	void SpawnLight(Vector2 pos,float radius,unsigned int color, float alpha);
	void SpawnTrackingLight(Vector2* targetPos, float radius, unsigned int color,float alpha);

private:

	Light lights[kMaxLight];
	int lightGH;
};