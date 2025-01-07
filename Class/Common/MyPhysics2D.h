#pragma once
#include "Class/Common/MyMath.h"

enum ForceMode {
	IMPACT,
	ACCELERATION,
};

class MyPhysics2D
{
public:

	void Init();
	void Update(Vector2* worldPos);

	Vector2 GetVelocity();
	Vector2 GetAcceleration();
	float GetWeight();
	float GetAirResistance();

	void SetVelocity(Vector2 setVelocity);
	void SetAcceleration(Vector2 setAcceleration);
	void SetWeigh(float setWeight);
	void SetAirResistance(float setAirResistance);
	void SetResistance(float set);

	void AddForce(Vector2 force,ForceMode mode);
	void AddGravity(Vector2 direction,float strength);
	void ResetAccelerationX();
	void ResetAccelerationY();
	void ResetVelocityX();
	void ResetVelocityY();
	void InversVelocity();
	void InversAcceleration();
	void AttenuationVelocity(float power);

private:

	Vector2 velocity;
	Vector2 acceleration;
	float weight;
	float airResistance;
	float resistance;
};

