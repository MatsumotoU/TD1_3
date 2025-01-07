#pragma once
#include "Matrix3x3.h"

struct Vector2 {

	float x;
	float y;

	Vector2 operator-()const { return { -x,-y }; };

	Vector2 operator+(const Vector2& other) { return { x + other.x, y + other.y }; }
	Vector2 operator-(const Vector2& other) { return { x - other.x, y - other.y }; }
	Vector2 operator*(const Vector2& other) { return { x * other.x, y * other.y }; }
	Vector2 operator/(const Vector2& other) { return { x / other.x, y / other.y }; }
	Vector2 operator=(const Vector2& other) { return { x = other.x, y = other.y }; }
	Vector2 operator+=(const Vector2& other) { return *this = *this + other; }
	Vector2 operator-=(const Vector2& other) { return *this = *this - other; }
	Vector2 operator*=(const Vector2& other) { return *this = *this * other; }
	Vector2 operator/=(const Vector2& other) { return *this = *this / other; }

	Vector2 operator+(const float& other) { return { x + other,y + other }; };
	Vector2 operator-(const float& other) { return { x - other,y - other }; };
	Vector2 operator/(const float& other) { return { x / other,y / other }; };
	Vector2 operator*(const float& other) { return { x * other,y * other }; };

	Vector2 operator*(const Matrix3x3& other) {
		Vector2 result = {
		x * other.m[0][0] + y * other.m[1][0] + other.m[2][0],
		x * other.m[0][1] + y * other.m[1][1] + other.m[2][1]
		};
		return result;
	}

};