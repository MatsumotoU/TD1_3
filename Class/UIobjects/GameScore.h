#pragma once
#include "BounceNumber.h"

class GameScore:public GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetGH(int* set);
	void SetPlusGH(int* set);
	void SetCamera(Camera* set);
	void SetScore(int set);
	void SetGroundPos(Vector2 set);

private:

	Vector2 groundPos;

	Camera* camera;
	BounceNumber score;
	int scoreNum;
	int* scoreGH;
	int* plusGH;
	int aliveFrame;
};

