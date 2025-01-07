#include "MyPhysics2D.h"

#include <algorithm>

void MyPhysics2D::Init() {

	velocity = { 0.0f,0.0f };
	acceleration = { 0.0f,0.0f };
	weight = 1.0f;
	airResistance = 0.0f;
	resistance = 0.9f;
}

void MyPhysics2D::Update(Vector2* worldPos) {

	//acceleration.x = std::clamp(acceleration.x, -1.0f, 1.0f);
	//acceleration.y = std::clamp(acceleration.y, -1.0f, 1.0f);
	velocity.x = std::clamp(velocity.x, -24.0f, 24.0f);
	velocity.y = std::clamp(velocity.y, -24.0f, 24.0f);

	// 物理加算処理
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	worldPos->x += velocity.x;
	worldPos->y += velocity.y;

	//acceleration.x *= 0.9f;
	//acceleration.y *= 0.9f;
	velocity.x *= resistance;
	velocity.y *= resistance;
	/*acceleration.x *= (1.0f - airResistance);
	acceleration.y *= (1.0f - airResistance);
	velocity.x *= (1.0f - airResistance);
	velocity.y *= (1.0f - airResistance);*/
}

void MyPhysics2D::AddForce(Vector2 force, ForceMode mode) {

	switch (mode)
	{
	case IMPACT:

		velocity.x += force.x;
		velocity.y += force.y;

		break;

	case ACCELERATION:

		acceleration.x += force.x / weight;
		acceleration.y += force.y / weight;

		break;
	default:
		break;
	}
}

void MyPhysics2D::AddGravity(Vector2 direction, float strength) {
	direction = Normalize(direction);
	acceleration.x += ((9.81f / 60.0f) * direction.x) * strength;
	acceleration.y += ((9.81f / 60.0f) * direction.y) * strength;
}

void MyPhysics2D::ResetAccelerationX() {
	acceleration.x = 0.0f;
}

void MyPhysics2D::ResetAccelerationY() {
	acceleration.y = 0.0f;
}

void MyPhysics2D::ResetVelocityX() {
	velocity.x = 0.0f;
}

void MyPhysics2D::ResetVelocityY() {
	velocity.y = 0.0f;
}

void MyPhysics2D::InversVelocity() {
	velocity.x *= -1.0f;
	velocity.y *= -1.0f;
}

void MyPhysics2D::InversAcceleration() {
	acceleration.x *= -1.0f;
	acceleration.y *= -1.0f;
}

void MyPhysics2D::AttenuationVelocity(float power) {
	velocity.x *= power;
	velocity.y *= power;
}

#pragma region Get
Vector2 MyPhysics2D::GetVelocity() {
	return velocity;
}

Vector2 MyPhysics2D::GetAcceleration() {
	return acceleration;
}

float MyPhysics2D::GetWeight() {
	return weight;
}

float MyPhysics2D::GetAirResistance() {
	return airResistance;
}
#pragma endregion

#pragma region Set
void MyPhysics2D::SetVelocity(Vector2 setVelocity) {
	velocity = setVelocity;
}

void MyPhysics2D::SetAcceleration(Vector2 setAcceleration) {
	acceleration = setAcceleration;
}

void MyPhysics2D::SetWeigh(float setWeight) {
	weight = setWeight;
}

void MyPhysics2D::SetAirResistance(float setAirResistance) {
	ptrClamp(&airResistance, 0.0f, 1.0f);
	airResistance = setAirResistance;
}
void MyPhysics2D::SetResistance(float set) {

	resistance = set;
}
#pragma endregion
