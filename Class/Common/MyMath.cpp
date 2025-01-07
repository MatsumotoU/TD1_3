#include "MyMath.h"
#include <Novice.h>
#include <math.h>

float Dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

float Cross(Vector2 a, Vector2 b) {
    return a.x * b.y - a.y * b.x;
}

unsigned int ColorFade(unsigned int color, float alpha) {

    unsigned int maskColor = 0xFFFFFF00 & color;
    

    return maskColor | static_cast<int>(alpha * 255);;
}

float Length(Vector2 a) {
    return sqrtf(powf(a.x, 2.0f) + powf(a.y, 2.0f));;
}

Vector2 Normalize(Vector2 setVec) {
    Vector2 vec = setVec;
    
    if (Length(vec) == 0.0f) {
        return vec;
    }

    vec = {
        setVec.x / Length(vec),
        setVec.y / Length(vec)
    };

    return vec;
}

int reClamp(int t, int min, int max) {
	if (t >= max) {
		return max;
	} else if (t <= min) {
		return min;
	}
	return t;
}

Vector2 RotatePos(Vector2 anker, float angle, float length) {
    Vector2 result;
    result.x = anker.x + (cosf(angle) - sinf(angle)) * length;
    result.x = anker.x + (cosf(angle) + sinf(angle)) * length;

    return result;
}

int ScopeVar(int var, int min, int max) {

    if (var >= min && var <= max) {
        return true;
    } else {
        return false;
    }
}

unsigned int FadeColor(unsigned int color, float alpha) {

    unsigned int rgbColor = color & 0xFFFFFF00;
    return  rgbColor|static_cast<int>(alpha * 255);
}

Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 result = { 0 };
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result = { 0 };
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 result = { 0 };
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;

	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	return result;
}

Vector2 BezierCurve(Vector2 a, Vector2 b, Vector2 c,float pow, float t) {
	Vector2 result = { 0 };
	ptrClamp(&t, 0.0f, 1.0f);

	result.x = (powf(1.0f - t, pow) * a.x) +
		(pow * (1.0f - t) * t * b.x) +
		powf(t, pow) * c.x;

	result.y = (powf(1.0f - t, pow) * a.y) +
		(pow * (1.0f - t) * t * b.y) +
		powf(t, pow) * c.y;

	return result;
}

Vector2 SplineInterpolation(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t) {
	Vector2 result = { 0 };

	result.x = 0.5f *
		((-a.x + 3.0f * b.x - 3.0f * c.x + d.x) * powf(t, 3.0f) +
			(2.0f * a.x - 5.0f * b.x + 4.0f * c.x - d.x) * powf(t, 2.0f) +
			(-a.x + c.x) * t +
			2.0f * b.x);

	result.y = 0.5f *
		((-a.y + 3.0f * b.y - 3.0f * c.y + d.y) * powf(t, 3.0f) +
			(2.0f * a.y - 5.0f * b.y + 4.0f * c.y - d.y) * powf(t, 2.0f) +
			(-a.y + c.y) * t +
			2.0f * b.y);

	return result;
}

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * 64, y + row * 20,
				"%.02f", matrix.m[row][column]);
		}
	}
}

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * 64, y + row * 20,
				"%.02f", matrix.m[row][column]);
		}
	}
}

Matrix2x2 Inverse(Matrix2x2 matrix) {
	Matrix2x2 result = { 0 };
	float i = (matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[0][1] * matrix.m[1][0]);

	if (i != 0.0f) {
		result.m[0][0] = matrix.m[1][1] / i;
		result.m[0][1] = -matrix.m[0][1] / i;
		result.m[1][0] = -matrix.m[1][0] / i;
		result.m[1][1] = matrix.m[0][0] / i;
	}

	return result;
}

Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 result = { 0 };
	float i = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	if (i != 0.0f) {
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / i;
		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / i;
		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / i;
		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / i;
		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / i;
		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / i;
		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / i;
		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / i;
		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / i;
	}

	return result;
}

Matrix2x2 Transpose(Matrix2x2 matrix) {
	Matrix2x2 result = matrix;
	result.m[0][1] = matrix.m[1][0];
	result.m[1][0] = matrix.m[0][1];
	return result;
}

Matrix3x3 Transpose(Matrix3x3 matrix) {
	Matrix3x3 result = matrix;
	result.m[0][1] = matrix.m[1][0];
	result.m[1][0] = matrix.m[0][1];
	result.m[0][2] = matrix.m[2][0];
	result.m[2][0] = matrix.m[0][2];
	result.m[1][2] = matrix.m[2][1];
	result.m[2][1] = matrix.m[1][2];
	return result;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {

	Matrix3x3 result = {0};

	if (left - right == 0.0f || top - bottom == 0.0f || right - left == 0.0f || bottom - top == 0.0f) {
		return result;
	}

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);

	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result = { 0 };

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height /2.0f;

	result.m[2][0] = left + (width / 2.0f);
	result.m[2][1] = top + (height / 2.0f);

	result.m[2][2] = 1.0f;

	return result;
}

Matrix3x3 MakeWvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthoMatrix, Matrix3x3 viewportMatrix) {

	Matrix3x3 result = worldMatrix * viewMatrix;
	result = result * orthoMatrix;
	result = result * viewportMatrix;

	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	Matrix3x3 result;

	result.m[0][0] = scale.x * cosf(rotate);
	result.m[0][1] = scale.x * sinf(rotate);
	result.m[0][2] = 0.0f;

	result.m[1][0] = scale.y * -sinf(rotate);
	result.m[1][1] = scale.y * cosf(rotate);
	result.m[1][2] = 0.0f;

	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return result;
}