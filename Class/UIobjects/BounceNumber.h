#pragma once
#include "Class/Common/Render.h"

class BounceNumber
{
public:

	BounceNumber();

	void Init();
	void Update();
	void Draw(Camera* drawCamera, int* numberGH);

	void SetPos(Vector2 set);
	void SetSize(Vector2 set);
	void SetTargetNum(int set);
private:

	int oldNumber;
	int number;
	int targetNumber;

	unsigned int color;
	Transform transform;

};

