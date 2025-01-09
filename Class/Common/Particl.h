#pragma once
#include "Class/Common/MyMath.h"
#include "Class/Common/MyPhysics2D.h"
#include "Class/Common/Render.h"

class Particl
{
public:

	void Init();
	void Update();
	void Draw();

	void SetPos(Vector2 set);
	void SetSize(Vector2 set);
	void SetTargetPos(Vector2* set);
	void SetAngle(float set);
	void SetIsActive(int set);
	void SetIsFalling(int set);
	void SetGraphHandle(int set);
	void SetRotateDir(float set);
	void SetIsFade(int set);
	void SetFadeFrame(int set);
	void SetIsTarget(int set);
	void SetStackFrame(int set);
	void SetRotated(int set);
	void SetMaxFadeFrame(int set);
	void SetIsShirink(int set);
	void SetColor(unsigned int set);
	void SetCamera(Camera* set);
	void SetIsAnim(int set);
	void SetMaxAnimFrame(int set);
	void SetAnimSpeed(int set);
	void SetIsLoop(int set);
	void SetAnimGH(int* set);

	Vector2 GetPos();
	Vector2* GetPosPtr();
	Vector2 GetSize();
	float GetAngle();
	int GetIsFade();
	int GetIsActive();
	int GetGraphHandle();
	MyPhysics2D* GetPhysics2D();
	int GetFrameCount();


private:

	int outCameraAliveFrame;
	Transform transform;
	Vector2* targetPos;
	Vector2 pos;
	Vector2 size;
	Vector2 scale;
	float angle;
	float rotateDir;
	int isTarget;
	int isFalling;
	int isRotated;
	int isActive;
	int isShrink;
	int particlGH;
	int isFade;
	int maxFadeFrame;
	int fadeFrame;
	int aliveFrame;
	int stackFrame;
	int isAnim;
	int maxAnimFrame;
	int animSpeed;
	int isLoop;
	int* animGH;
	int animCount;
	int frameCount;
	int gh;

	unsigned int color;
	MyPhysics2D physics2D;

	Camera* camera;

};

