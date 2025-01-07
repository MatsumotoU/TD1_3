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
	void DrawLine(Vector2 pos1, Vector2 pos2, Camera camera, unsigned int color);

	/// <summary>
	/// Transform指定箱描画関数
	/// </summary>
	/// <param name="transform">描画に使用する座標</param>
	/// <param name="camera">使用するカメラ</param>
	/// <param name="color">色</param>
	/// <param name="fillMode">描画スタイル</param>
	void DrawBox(Transform transform, Camera camera, unsigned int color, FillMode fillMode);

	/// <summary>
	/// 円描画
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="radius"></param>
	/// <param name="angle"></param>
	/// <param name="camera"></param>
	/// <param name="color"></param>
	/// <param name="fillMode"></param>
	void DrawEllipse(Vector2 pos, Vector2 radius,float angle, Camera camera, unsigned int color, FillMode fillMode);

	/// <summary>
	/// スプライト描画
	/// </summary>
	/// <param name="transform">描画に使用する座標</param>
	/// <param name="camera">使用するカメラ</param>
	/// <param name="color">色</param>
	/// <param name="gh">テクスチャ</param>
	void DrawSprite(Transform transform, Camera camera, unsigned int color,int gh);
}


