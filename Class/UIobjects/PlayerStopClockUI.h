#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"

class PlayerStopClockUI:public GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);
	void SetPlayerAttackStopFrame(int* set);
	void SetPlayerAttackComboCount(int* set);

private:

	unsigned int color;
	float alpha;

	int clockGH;
	int clockHandlesGH;

	int* playerAttackComboCount;
	int* playerAttackStopFrame;

	Transform clockHandleTransform;
	Camera* camera;
};

