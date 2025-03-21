#include "Camera.h"
#include "Render.h"
#include "Class/Common/MyEasing.h"

#include <Novice.h>
#include <math.h>

Camera::Camera() {

	transform.pos = { 0.0f,0.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;
	screenSize = { 1280.0f,720.0f };
	shake = { 0.0f,0.0f };
	shakeRange = { 0.0f,0.0f };

	angleShake = 0.0f;
	angleShakeRange = 0.0f;
	panRange = 0.0f;
	localScale = { 1.0f,1.0f };
}

int Camera::IsInScreen(Vector2 pos, Vector2 size) {
	int inX = false;
	int inY = false;

	if (transform.pos.x + size.x * 0.5f >= pos.x - (screenSize.x * localScale.x * 0.5f) &&
		transform.pos.x - size.x * 0.5f <= pos.x + (screenSize.x * localScale.x * 0.5f)) {

		inX = true;
	}

	if (transform.pos.y + size.y * 0.5f >= pos.y - (screenSize.y * localScale.y * 0.5f) &&
		transform.pos.y - size.y * 0.5f <= pos.y + (screenSize.y * localScale.y * 0.5f)) {

		inY = true;
	}

	return inX & inY;
}

void Camera::CameraMoveLimit(Vector2 min, Vector2 max) {

	if (transform.pos.x <= min.x) {
		transform.pos.x = min.x;
	}

	if (transform.pos.y <= min.y) {
		transform.pos.y = min.y;
	}

	if (transform.pos.x >= max.x) {
		transform.pos.x = max.x;
	}

	if (transform.pos.y >= max.y) {
		transform.pos.y = max.y;
	}
}

Matrix3x3 Camera::GetWvpVpMatrix(Vector2 setPos, Vector2 setScale, float setAngle) const {
	Matrix3x3 result = { 0 };
	Matrix3x3 objWorldMatrix = MakeAffineMatrix(setScale, setAngle, setPos);

	Matrix3x3 cameraWorldMatrix = MakeAffineMatrix(transform.scale * localScale, transform.angle + angleShake, transform.pos + shake);
	Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(-screenSize.x * 0.5f, screenSize.y * 0.5f, screenSize.x * 0.5f, -screenSize.y * 0.5f);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, screenSize.x, screenSize.y);

	result = MakeWvpVpMatrix(objWorldMatrix, viewMatrix, orthoMatrix, viewportMatrix);
	return result;
}

Vector2 Camera::GetScreenSize() {
	return screenSize;
}

Vector2* Camera::GetPosPtr() {
	return &transform.pos;
}

Transform* Camera::GetTransformPtr() {
	return &transform;
}

void Camera::SetScreenSize(Vector2 set) {
	screenSize = set;
}

void Camera::SetLocalScale(Vector2 set) {
	localScale = set;
}

void Camera::DrawGrid(Vector2 gridSize) {

	Vector2 zero = { 0 };

	// グリッド描画
	Vector2 divideScreen = screenSize / gridSize;
	// 縦線
	for (int i = 0; i < static_cast<int>(divideScreen.x); i++) {
		Novice::DrawLine((static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).x) + static_cast<int>(gridSize.x) * i) % static_cast<int>(screenSize.x),
			0,
			(static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).x) + static_cast<int>(gridSize.x) * i) % static_cast<int>(screenSize.x),
			static_cast<int>(screenSize.y),
			0xFFFFFF23);
	}
	// 横線
	for (int i = 0; i < static_cast<int>(divideScreen.y); i++) {
		Novice::DrawLine(0,
			(static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).y) + static_cast<int>(gridSize.y) * i) % static_cast<int>(screenSize.y),
			static_cast<int>(screenSize.x),
			(static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).y) + static_cast<int>(gridSize.y) * i) % static_cast<int>(screenSize.y),
			0xFFFFFF23);
	}

	// * 原点からの軸描画 * //
	// X軸
	Novice::DrawLine(0,
		static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).y),
		static_cast<int>(screenSize.x),
		static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).y),
		RED);
	// Y軸
	Novice::DrawLine(static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).x),
		0,
		static_cast<int>((zero * GetWvpVpMatrix((transform.size * 0.5f), { 1.0f,1.0f }, 0.0f)).x),
		static_cast<int>(screenSize.y),
		GREEN);

}

void Camera::Init() {

	transform.pos = { 0.0f,0.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;
	screenSize = { 1280.0f,720.0f };
	shake = { 0.0f,0.0f };
	shakeRange = { 0.0f,0.0f };
	angleShake = 0.0f;
	angleShakeRange = 0.0f;
	localScale = { 1.0f,1.0f };
}

void Camera::Update() {

	// 画面揺れ
	shakeRange.x *= 0.9f;
	shakeRange.y *= 0.9f;
	/*if (shakeRange.x >= 50.0f) {
		shakeRange.x = 50.0f;
	}
	if (shakeRange.y >= 50.0f) {
		shakeRange.y = 50.0f;
	}*/

	if (shakeRange.x > 1.0f) {
		shake.x = static_cast<float>(rand() % static_cast<int>(shakeRange.x * 2.0f) - static_cast<int>(shakeRange.x));
	} else {
		shake.x = 0.0f;
	}

	if (shakeRange.y > 1.0f) {
		shake.y = static_cast<float>(rand() % static_cast<int>(shakeRange.y * 2.0f) - static_cast<int>(shakeRange.y));
	} else {
		shake.y = 0.0f;
	}

	// 画面角度揺れ
	angleShakeRange *= 0.9f;
	if (angleShakeRange <= 0.0f) {
		angleShakeRange = 0.0f;
	}
	if (angleShakeRange >= 15.0f) {
		angleShakeRange = 15.0f;
	}
	angleShake = sinf(time->frameCount * 0.1f) * (angleShakeRange * 0.01f);

	// パン
	panRange *= 0.9f;
	if (fabsf(panRange) > 0.1f) {
		transform.scale = {1.0f + panRange,1.0f + panRange};
	} else {
		Eas::SimpleEaseIn(&transform.scale.x, 1.0f, 0.1f);
		Eas::SimpleEaseIn(&transform.scale.y, 1.0f, 0.1f);
	}
}

void Camera::Draw() {

}
