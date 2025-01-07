#include "Particl.h"
#include <Novice.h>
#include "Class/Common/MyEasing.h"

void Particl::Init() {
	pos = { 0.0f,0.0f };
	size = { 16.0f,16.0f };
	scale = { 1.0f,1.0f };
	angle = 0.0f;
	rotateDir = 0.0f;

	isActive = false;
	isFalling = false;
	isFade = false;
	isTarget = false;
	isRotated = true;
	isShrink = false;
	fadeFrame = 1;
	maxFadeFrame = fadeFrame;
	aliveFrame = 1;
	stackFrame = 1;

	physics2D.Init();
	physics2D.SetResistance(1.0f);

	color = WHITE;

	particlGH = 0;
	frameCount = 0;

	camera = nullptr;

	transform.pos = pos;
	transform.angle = angle;
	transform.scale = scale;
	transform.size = size;

	gh = 0;
}

void Particl::Update() {

	frameCount++;
	if (isActive) {

		// 回転
		if (isRotated) {
			angle += rotateDir;
		}

		// 重力
		if (isFalling) {
			physics2D.AddGravity({ 0.0f,-0.4f }, 0.4f);
		}

		// 物理更新
		physics2D.Update(&pos);

		// 画面外に行ったら描画停止
		if (!camera->IsInScreen(pos,size)) {

			//Novice::ConsolePrintf("%f,%f\n", draw->GetScreenPos(pos).x, draw->GetScreenPos(pos).y);
			isActive = false;
		}

		// フェードアウト
		if (isFade) {

			color = ColorFade(color, static_cast<float>(fadeFrame) / static_cast<float>(maxFadeFrame));

			if (fadeFrame > 0) {
				fadeFrame--;
			} else {
				isActive = false;
			}
		}

		// 縮む
		if (isShrink) {
			if (isFade) {

				scale.x = static_cast<float>(fadeFrame) / static_cast<float>(maxFadeFrame);
				scale.y = static_cast<float>(fadeFrame) / static_cast<float>(maxFadeFrame);

			} else {

				if (scale.x > 0.0f) {
					scale.x -= 0.05f;
				}
				if (scale.y > 0.0f) {
					scale.y -= 0.05f;
				}
			}
		}

		// 向かう
		if (isTarget) {

			if (stackFrame <= 0) {

				Eas::SimpleEaseIn(&size.x, 0.0f, 0.05f);
				Eas::SimpleEaseIn(&size.y, 0.0f, 0.05f);

				Eas::SimpleEaseIn(&pos.x, targetPos.x, 0.1f);
				Eas::SimpleEaseIn(&pos.y, targetPos.y, 0.1f);
			} else {
				stackFrame--;
			}
			
			if (pos.x == targetPos.x && pos.y == targetPos.y) {
				isActive = false;
			}
		}

		// 消滅時間設定
		if (aliveFrame <= 0) {
			isActive = false;
		}
	}

	transform.pos = pos;
	transform.angle = angle;
	transform.scale = scale;
	transform.size = size;
}

void Particl::Draw() {
	if (isActive) {
		Render::DrawSprite(transform, *camera, color, gh);
	}
}

void Particl::SetPos(Vector2 set) {
	pos = set;
}

void Particl::SetSize(Vector2 set) {
	size = set;
}

void Particl::SetTargetPos(Vector2 set) {
	targetPos = set;
}

void Particl::SetAngle(float set) {
	angle = set;
}

void Particl::SetIsActive(int set) {
	isActive = set;
}

void Particl::SetIsFalling(int set) {
	isFalling = set;
}

void Particl::SetGraphHandle(int set) {
	particlGH = set;
}

void Particl::SetRotateDir(float set) {
	rotateDir = set;
}

void Particl::SetIsFade(int set) {
	isFade = set;
}

void Particl::SetFadeFrame(int set) {
	fadeFrame = set;
	maxFadeFrame = set;
}

void Particl::SetIsTarget(int set) {
	isTarget = set;
}

void Particl::SetStackFrame(int set) {
	stackFrame = set;
}

void Particl::SetRotated(int set) {
	isRotated = set;
}

void Particl::SetMaxFadeFrame(int set) {
	maxFadeFrame = set;
}

void Particl::SetIsShirink(int set) {
	isShrink = set;
}

void Particl::SetColor(unsigned int set) {
	color = set;
}

void Particl::SetCamera(Camera* set) {
	camera = set;
}

Vector2 Particl::GetPos() {
	return pos;
}

Vector2* Particl::GetPosPtr() {
	return &pos;
}

Vector2 Particl::GetSize() {
	return size;
}

float Particl::GetAngle() {
	return angle;
}

int Particl::GetIsFade() {
	return isFade;
}

int Particl::GetIsActive() {
	return isActive;
}

int Particl::GetGraphHandle() {
	return particlGH;
}

MyPhysics2D* Particl::GetPhysics2D() {
	return &physics2D;
}

int Particl::GetFrameCount() {
	return frameCount;
}
