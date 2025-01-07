#pragma once

#include <Novice.h>

#include "MyMath.h"

/// <summary>
/// 円と円の当たり判定
/// </summary>
/// <param name="targetPos1">1つ目のオブジェクト座標</param>
/// <param name="targetPos2">2つ目のオブジェクト座標 Y</param>
/// <param name="targetVec1">1つ目のオブジェクト力</param>
/// <param name="targetVec2">2つ目のオブジェクト力 Y</param>
/// <param name="targetSpeed1">1つ目のオブジェクト速度</param>
/// <param name="targetSpeed2">2つ目のオブジェクト速度</param>
/// <param name="targetRadius1">1つ目のオブジェクト半径</param>
/// <param name="targetRadius2">2つ目のオブジェクト半径</param>
/// <param name="isRepulsion">衝突時反射するか？</param>
/// <param name="isTgt1Fix">1つ目のオブジェクトが固定されているか？</param>
/// <param name="isTgt2Fix">2つ目のオブジェクトが固定されているか？</param>
int CollisionEllipse(Vector2* targetPos1, Vector2* targetPos2, Vector2 targetVec1, Vector2 targetVec2, float targetSpeed1, float targetSpeed2, float targetRadius1, float targetRadius2, int isRepulsion, int isTgt1Fix, int isTgt2Fix);

//int CollisionRectangle(Vector2* targetPos1, Vector2* targetPos2, Vector2 targetsize1, Vector2 targetsize2, int isRepulsion, int isTgt1Fix, int isTgt2Fix);

/// <summary>
/// 円と矩形の当たり判定
/// </summary>
/// <param name="targetPos1">1つ目のオブジェクト座標</param>
/// <param name="targetPos2">2つ目のオブジェクト座標 Y</param>
/// <param name="targetVec1">1つ目のオブジェクト力</param>
/// <param name="targetVec2">2つ目のオブジェクト力 Y</param>
/// <param name="targetSpeed1">1つ目のオブジェクト速度</param>
/// <param name="targetSpeed2">2つ目のオブジェクト速度</param>
/// <param name="targetRadius1">1つ目のオブジェクト半径</param>
/// <param name="targetsize2">2つ目のオブジェクトサイズ</param>
/// <param name="isRepulsion">衝突時反射するか？</param>
/// <param name="isTgt1Fix">1つ目のオブジェクトが固定されているか？</param>
/// <param name="isTgt2Fix">2つ目のオブジェクトが固定されているか？</param>
int CollisionEllipseToRectangle(Vector2* targetPos1, Vector2* targetPos2, Vector2 targetVec1, Vector2 targetVec2, float targetSpeed1, float targetSpeed2, float targetRadius1, Vector2 targetsize2, int isRepulsion, int isTgt1Fix, int isTgt2Fix);

int CollisionRectangle(Vector2* aPos, Vector2 aSize, Vector2 bPos, Vector2 bSize,int isTransformX, int isTransformY);

int CollisionPointToRectangle(Vector2* pointPos, Vector2 rectanglePos, Vector2 rectangleSize);

int IsHitRectangle(Vector2 aPos, Vector2 aSize, Vector2 bPos, Vector2 bSize);

int IsHitCollisionEllipse(Vector2 targetPos1, Vector2 targetPos2, float targetRadius1, float targetRadius2);

int IsHitCollisionEllipseToRectangle(Vector2 targetPos1, Vector2 targetPos2, float targetRadius1, Vector2 targetsize2);

