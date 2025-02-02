#pragma once
#include "GameObject.h"
#include "Render.h"

class Light:public GameObject
{
public:

	Light();

	void Init()override;
	void Update()override;
	void Draw()override;
	
	void SetGH(int* set);
	void SetCamera(Camera* set);
	void SetTargetPos(Vector2* set);
	void SetColor(unsigned int set);
	void SetAlpha(float set);

private:

	Vector2 spawnScale;
	int frameCount;
	int* gh;
	unsigned int color;
	float alpha;
	Camera* camera;

	Vector2* targetPos;
};

