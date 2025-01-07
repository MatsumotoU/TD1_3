#pragma once
struct Matrix3x3
{
	float m[3][3];

	Matrix3x3 operator+(const Matrix3x3& other) {
		Matrix3x3 returnMatrix;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {

				returnMatrix.m[x][y] = m[x][y] + other.m[x][y];
			}
		}
		return returnMatrix;
	}
	Matrix3x3 operator-(const Matrix3x3& other) {
		Matrix3x3 returnMatrix;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {

				returnMatrix.m[x][y] = m[x][y] - other.m[x][y];
			}
		}
		return returnMatrix;
	}
	Matrix3x3 operator*(const Matrix3x3& other) {
		Matrix3x3 result = { 0 };
		result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0];
		result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1];
		result.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2];

		result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0];
		result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1];
		result.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2];

		result.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0];
		result.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1];
		result.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2];
		return result;
	}
};