#include "BounceNumber.h"
#include "Class/Common/MyEasing.h"

BounceNumber::BounceNumber() {
	oldNumber = 0;
	number = 0;
	targetNumber = 0;
	transform = { 0.0f };
	transform.pos = { 0.0f,0.0f };
	transform.scale = { 1.0f,1.0f };
	transform.size = { 64.0f,64.0f };
	transform.angle = 0.0f;
	color = 0;
}

void BounceNumber::Init() {
	oldNumber = 0;
	number = 0;
	targetNumber = 0;

	color = WHITE;
}

void BounceNumber::Update() {

	if (number != targetNumber) {
		if (transform.scale.x > 0.8f && transform.scale.x < 1.2f) {

			transform.scale.y = 2.0f;
			transform.scale.x = 0.3f;

			if (number - targetNumber < 0) {
				number += 1;
			} else {
				number -= 1;
			}
		}
	}

	Eas::SimpleEaseIn(&transform.scale.x, 1.0f, 0.3f);
	Eas::SimpleEaseIn(&transform.scale.y, 1.0f, 0.3f);
}

void BounceNumber::Draw(Camera* drawCamera,int* numberGH) {

	Render::DrawNum(transform.pos, transform.size, transform.scale, transform.angle, *drawCamera, number, numberGH, color);
}

void BounceNumber::SetPos(Vector2 set) {
	transform.pos = set;
}

void BounceNumber::SetSize(Vector2 set) {
	transform.size = set;
}

void BounceNumber::SetTargetNum(int set) {
	targetNumber = set;
}
