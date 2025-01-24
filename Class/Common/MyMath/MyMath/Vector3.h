#pragma once
struct Vector3 {
	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3& other) { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator*(const Vector3& other) { return { x * other.x, y * other.y, z * other.z }; }
	Vector3 operator/(const Vector3& other) { return { x / other.x, y / other.y, z / other.z }; }
	Vector3 operator=(const Vector3& other) { return { x = other.x, y = other.y, z = other.z }; }
	Vector3 operator+=(const Vector3& other) { return { x += other.x, y += other.y, z += other.z }; }
	Vector3 operator-=(const Vector3& other) { return { x -= other.x, y -= other.y, z -= other.z }; }
	Vector3 operator*=(const Vector3& other) { return { x *= other.x, y *= other.y, z *= other.z }; }
	Vector3 operator/=(const Vector3& other) { return { x /= other.x, y /= other.y, z /= other.z }; }
};
