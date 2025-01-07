#pragma once
#include "GameObject.h"
#include "Class/Common/TimeManager.h"

class Camera :private GameObject
{
public:

	Camera();
	~Camera() = default;

	void Init() override;
	void Update() override;
	void Draw()override;

	Matrix3x3 GetWvpVpMatrix(Vector2 setPos, Vector2 setScale, float setAngle);
	Vector2 GetScreenSize();
	Vector2* GetPosPtr();

	void SetScreenSize(Vector2 set);

	int IsInScreen(Vector2 pos,Vector2 size);
	void CameraMoveLimit(Vector2 min, Vector2 max);
	void DrawGrid(Vector2 gridSize);

	float angleShakeRange;
	Vector2 shakeRange;

private:

	Vector2 shake;
	float angleShake;
	Vector2 screenSize;

	TimeManager* time = TimeManager::GetInstance();
};

