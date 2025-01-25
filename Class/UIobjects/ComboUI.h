#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"
#include "BounceNumber.h"

class ComboUI : public GameObject
{
public:

	ComboUI();

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);
	void SetCombo(int* setCombo, int* setRemainFrame);

private:

	Camera* camera;
	int* combo;
	int* remainFrame;

	Transform comboRamainFrameTransform;
	float maxRemainFrame;

	BounceNumber comboCount;
	int comboNumGH[10];
};

