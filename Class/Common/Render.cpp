#include "Render.h"

void Render::DrawLine(Vector2 pos1, Vector2 pos2, Camera camera, unsigned int color) {
	// ローカル座標計算
	Vector2 zero = { 0 };
	// スクリーン座標計算
	Vector2 from = zero * camera.GetWvpVpMatrix(pos1, { 1.0f,1.0f }, 0.0f);
	Vector2 to = zero * camera.GetWvpVpMatrix(pos2, { 1.0f,1.0f }, 0.0f);

	// 線描画
	Novice::DrawLine(
		static_cast<int>(from.x), static_cast<int>(from.y),
		static_cast<int>(to.x), static_cast<int>(to.y), color);
}

void Render::DrawBox(Transform transform, Camera camera, unsigned int color, FillMode fillMode) {
	// ローカル座標計算
	Vector2 leftTopPos = {
		-(transform.size.x  * 0.5f),
		(transform.size.y  * 0.5f),
	};
	// スクリーン座標計算
	Vector2 drawPos = leftTopPos * camera.GetWvpVpMatrix(transform.pos, transform.scale, transform.angle);

	// 箱描画
	Novice::DrawBox(
		static_cast<int>(drawPos.x), static_cast<int>(drawPos.y),
		static_cast<int>(transform.size.x * transform.scale.x),
		static_cast<int>(transform.size.y * transform.scale.y),
		-transform.angle, color, fillMode);
}

void Render::DrawEllipse(Vector2 pos, Vector2 radius, float angle, Camera camera, unsigned int color, FillMode fillMode) {
	// ローカル座標計算
	Vector2 zero = { 0 };
	// スクリーン座標計算
	Vector2 drawPos = zero * camera.GetWvpVpMatrix(pos, { 1.0f,1.0f }, 0.0f);

	// 円描画
	Novice::DrawEllipse(
		static_cast<int>(drawPos.x), static_cast<int>(drawPos.y),
		static_cast<int>(radius.x), static_cast<int>(radius.y), angle, color, fillMode);
}

void Render::DrawSprite(Transform transform, Camera camera, unsigned int color, int gh) {

	// 画像が差し込まれているか
	if (gh == 0) {

		// 無地描画
		Render::DrawBox(transform, camera, color, kFillModeSolid);

	} else {

		// 矩形頂点用
		struct QuadPos
		{
			Vector2 leftTop;
			Vector2 rightTop;
			Vector2 leftDown;
			Vector2 rightDown;
		};

		// スプライトのサイズ割り出し
		QuadPos sizePos = {
			{-(transform.size.x / 2.0f) * transform.scale.x ,
			+(transform.size.y / 2.0f) * transform.scale.y},
			{+(transform.size.x / 2.0f) * transform.scale.x,
			+(transform.size.y / 2.0f) * transform.scale.y},
			{-(transform.size.x / 2.0f) * transform.scale.x ,
			-(transform.size.y / 2.0f) * transform.scale.y},
			{+(transform.size.x / 2.0f) * transform.scale.x,
			-(transform.size.y / 2.0f) * transform.scale.y},
		};

		// カメラのvWVPVp行列取得
		Matrix3x3 vWVPVpMatrix = camera.GetWvpVpMatrix(transform.pos, transform.scale, transform.angle);

		// 描画用座標代入
		QuadPos drawSpritePos = {
			sizePos.leftTop * vWVPVpMatrix,
			sizePos.rightTop * vWVPVpMatrix,
			sizePos.leftDown * vWVPVpMatrix,
			sizePos.rightDown * vWVPVpMatrix,
		};

		// スプライト描画
		Novice::DrawQuad(static_cast<int>(drawSpritePos.leftTop.x), static_cast<int>(drawSpritePos.leftTop.y),
			static_cast<int>(drawSpritePos.rightTop.x), static_cast<int>(drawSpritePos.rightTop.y),
			static_cast<int>(drawSpritePos.leftDown.x), static_cast<int>(drawSpritePos.leftDown.y),
			static_cast<int>(drawSpritePos.rightDown.x), static_cast<int>(drawSpritePos.rightDown.y),
			1, 1, static_cast<int>(transform.size.x), static_cast<int>(transform.size.y), gh, color);

	}
}
