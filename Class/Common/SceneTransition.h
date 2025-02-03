#pragma once
#include "Class/Common/MyEasing.h"
#include "Class/Common/ParticlManager.h"
#include "Class/Common/Camera.h"
#include "Class/Common/MyMath.h"

namespace Pal {
	enum ColorPalette : unsigned int {
		kBLACK = 0x222831ff,
		kGRAY = 0x393e46ff,
		kORANGE = 0xd65a31ff,
		kWHITE = 0xeeeeeeff
	};
}

class SceneTransition {
public:
	void Init();
	void Update();
	void Draw();

	void SetIsTransition(int setIsTransition);
	int GetIsTransition();
	int GetIsTransitionClosed();

private:
	int frameCount;

	int transitionType;
	float t[3];
	int cnt;

	int transitionTime;
	int transitionEndTime;

	int shutterGraphHandle;

	int isTransition;
	int isTransitionClosed;

	ParticlManager particle;

	Camera mainCamera;
};

