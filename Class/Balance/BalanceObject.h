#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"

class BalanceObject:public GameObject
{
public:

	BalanceObject();

	void Init()override;
	void Update()override;
	void Draw()override;

	void PhysicsUpdate();
	void parentObjectUpdate();

	void SetCamera(Camera* set);
	void SetFalling(int set);
	void SetGraphHandle(int set);
	void SetParentObject(Transform* set);

	int GetFalling();
	int GetFallingTime();

	void ParentObject(Transform* parent);

private:
	Transform* parentObjectTransform;
	Vector2 parentPos;

	int isFalling;
	int fallingTime;
	Camera* camera;
	int gh;
};

