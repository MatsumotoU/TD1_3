#pragma once
#include"Class/Common/MyMath/MathInclude.h"

float Dot(Vector2 a, Vector2 b);
float Cross(Vector2 a, Vector2 b);
float Length(Vector2 a);
Vector2 Normalize(Vector2 setVec);

unsigned int ColorFade(unsigned int color, float alpha);

template <typename T>
T Clamp(T t, T min, T max) {

	if (t > max) {
		return max;
	} else if (t < min) {
		return min;
	}
	return t;
};
template <typename T>
void ptrClamp(T* t, T min, T max){

	if (*t > max) {
		*t = max;
	} else if (*t < min) {
		*t = min;
	}
};
int ScopeVar(int var, int min, int max);

Vector2 RotatePos(Vector2 anker, float angle, float length);

Matrix3x3 MakeScaleMatrix(Vector2 scale);
Matrix3x3 MakeRotateMatrix(float theta);
Matrix3x3 MakeTranslateMatrix(Vector2 translate);
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

Vector2 BezierCurve(Vector2 a, Vector2 b, Vector2 c, float pow,float t);
Vector2 SplineInterpolation(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t);
//Vector2 CatmullRomSpline(Vector2* p, int subscript, float t);

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);
Matrix2x2 Inverse(Matrix2x2 matrix);
Matrix3x3 Inverse(Matrix3x3 marix);

Matrix2x2 Transpose(Matrix2x2 matrix);
Matrix3x3 Transpose(Matrix3x3 matrix);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);
Matrix3x3 MakeWvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthoMatrix, Matrix3x3 viewportMatrix);
