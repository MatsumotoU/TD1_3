#pragma once
#include "Camera.h"
#include <Novice.h>

namespace Render {

	/// <summary>
	/// 線描画関数
	/// </summary>
	/// <param name="pos1">第1座標</param>
	/// <param name="pos2">第2座標<</param>
	/// <param name="camera">使用するカメラ</param>
	/// <param name="color">色</param>
	void DrawLine(Vector2 pos1, Vector2 pos2, const Camera& camera, unsigned int color);

	/// <summary>
	/// Transform指定箱描画関数
	/// </summary>
	/// <param name="transform">描画に使用する座標</param>
	/// <param name="camera">使用するカメラ</param>
	/// <param name="color">色</param>
	/// <param name="fillMode">描画スタイル</param>
	void DrawBox(Transform transform, const Camera& camera, unsigned int color, FillMode fillMode);

	/// <summary>
	/// 円描画
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="radius"></param>
	/// <param name="angle"></param>
	/// <param name="camera"></param>
	/// <param name="color"></param>
	/// <param name="fillMode"></param>
	void DrawEllipse(Vector2 pos, Vector2 radius,float angle, const Camera& camera, unsigned int color, FillMode fillMode);

	void DrawTriangle(Vector2 pos1, Vector2 pos2, Vector2 pos3, const Camera& camera, unsigned int color, FillMode fillMode);

	/// <summary>
	/// スプライト描画
	/// </summary>
	/// <param name="transform">描画に使用する座標</param>
	/// <param name="camera">使用するカメラ</param>
	/// <param name="color">色</param>
	/// <param name="gh">テクスチャ</param>
	void DrawSprite(Transform transform, const Camera& camera, unsigned int color,int gh);

	/// <summary>
	/// 数字を描画
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">画像サイズ</param>
	/// <param name="scale">数字の拡大率</param>
	/// <param name="angle">各数字の角度</param>
	/// <param name="num">描画する数値</param>
	/// <param name="gh">数字のグラフィック</param>
	/// <param name="color">数字の色</param>
	void DrawNum(Vector2 pos, Vector2 size, Vector2 scale, float angle, const Camera& camera, int num, int* gh, unsigned int color);

	void DrawScore(Vector2 pos, Vector2 size, Vector2 scale, float angle, const Camera& camera, int num,int digit, int* gh, unsigned int color);
}


