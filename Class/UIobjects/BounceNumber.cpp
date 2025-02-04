#include "BounceNumber.h"
#include "Class/Common/MyEasing.h"

BounceNumber::BounceNumber() {
	isFillZero = false;
	oldNumber = 0;
	number = 0;
	targetNumber = 0;
	transform = { 0.0f };
	transform.pos = { 0.0f,0.0f };
	transform.scale = { 1.0f,1.0f };
	localScale = { 1.0f,1.0f };
	transform.size = { 64.0f,64.0f };
	transform.angle = 0.0f;
	color = 0;
	frameCount = 0;

	se = Novice::LoadAudio("./Resources/Sounds/numberSE.mp3");
}

void BounceNumber::Init() {
	oldNumber = 0;
	number = 0;
	targetNumber = 0;
	frameCount = 0;

	color = WHITE;
}

void BounceNumber::Update() {

	frameCount++;

	if (number != targetNumber) {
		if (transform.scale.x > 0.8f && transform.scale.x < 1.2f) {

			transform.scale.y = 2.0f;
			transform.scale.x = 0.3f;

			if (number - targetNumber < 0) {
				number += ((targetNumber - number) / 2) + 1;
				Novice::PlayAudio(se, false, 0.1f);
			} else {
				number += ((targetNumber - number) / 2) - 1;
				Novice::PlayAudio(se, false, 0.1f);
			}
		}
	}

	Eas::SimpleEaseIn(&transform.scale.x, 1.0f, 0.3f);
	Eas::SimpleEaseIn(&transform.scale.y, 1.0f, 0.3f);
}

void BounceNumber::Draw(Camera* drawCamera,int* numberGH) {

	if (isFillZero) {
		Render::DrawScore(transform.pos, transform.size, transform.scale * localScale.y, transform.angle, *drawCamera, number,8, numberGH, color);
	} else {
		Render::DrawNum(transform.pos, transform.size, transform.scale * localScale.y, transform.angle, *drawCamera, number, numberGH, color);
	}
}

void BounceNumber::SetPos(Vector2 set) {
	transform.pos = set;
}

void BounceNumber::SetSize(Vector2 set) {
	transform.size = set;
}

void BounceNumber::SetScale(Vector2 set) {
	transform.scale = set;
}

void BounceNumber::SetTargetNum(int set) {
	targetNumber = set;
}

void BounceNumber::SetLocalScale(Vector2 set) {
	localScale = set;
}

void BounceNumber::SetColor(unsigned int set) {
	color = set;
}

void BounceNumber::SetIsFillZero(int set) {
	isFillZero = set;
}

Transform BounceNumber::GetTransform() {
	return transform;
}

Vector2* BounceNumber::GetPosPtr() {
	return &transform.pos;
}

Vector2 BounceNumber::GetScale() {
	return transform.scale;
}

int BounceNumber::GetNumber() {
	return number;
}

int BounceNumber::GetDigit() {

	if (isFillZero) {
		return 8;
	}

	int tempNum = number;
	int digit = 1;

	while (tempNum >= 10)
	{
		tempNum /= 10;
		digit++;
	}
	return digit;
}
