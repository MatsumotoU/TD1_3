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
	void SetScale(Vector2 set);
	void SetTargetNum(int set);
	void SetLocalScale(Vector2 set);

	Transform GetTransform();
	Vector2* GetPosPtr();
	Vector2 GetScale();

private:

	int frameCount;
	int oldNumber;
	int number;
	int targetNumber;

	unsigned int color;
	Transform transform;
	Vector2 localScale;

};

