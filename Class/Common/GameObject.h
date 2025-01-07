#pragma once
#include "Class/Common/MyPhysics2D.h"
#include "Class/Common/MyMath.h"
#include "SimpleJson.h"

class GameObject
{
public:

	GameObject() = default;
	~GameObject() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Transform GetTransform() {
		return transform;
	}
	Vector2 GetPos() {
		return transform.pos;
	}
	Vector2 GetSize() {
		return transform.size;
	}
	Vector2 GetScale() {
		return transform.scale;
	}
	float GetAngle() {
		return transform.angle;
	}
	MyPhysics2D* GetPhysics() {
		return &physics;
	}
	int GetIsActive() {
		return isActive;
	}

	void SetTransform(Transform set) {
		transform = set;
	}
	void SetPos(Vector2 set) {
		transform.pos = set;
	}
	void SetSize(Vector2 set) {
		transform.size = set;
	}
	void SetScale(Vector2 set) {
		transform.scale = set;
	}
	void SetAngle(float set) {
		transform.angle = set;
	}
	void SetIsActive(int set) {
		isActive = set;
	}
	
protected:

	Transform transform;
	MyPhysics2D physics;
	int isActive;

	SJN::json value;

};

