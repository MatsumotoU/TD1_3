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
			{-(transform.size.x / 2.0f) ,
			+(transform.size.y / 2.0f) },
			{+(transform.size.x / 2.0f) ,
			+(transform.size.y / 2.0f) },
			{-(transform.size.x / 2.0f)  ,
			-(transform.size.y / 2.0f)},
			{+(transform.size.x / 2.0f),
			-(transform.size.y / 2.0f)},
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

void Render::DrawSprite(Vector2 pos, Vector2 size, Vector2 scale, float angle, Camera camera, unsigned int color, int gh) {
	// 画像が差し込まれているか
	if (gh == 0) {

		// 無地描画
		Transform temp = { 0.0f };
		temp.pos = pos;
		temp.size = size;
		temp.scale = scale;
		temp.angle = angle;
		Render::DrawBox(temp, camera, color, kFillModeSolid);

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
			{-(size.x / 2.0f) ,
			+(size.y / 2.0f) },
			{+(size.x / 2.0f) ,
			+(size.y / 2.0f) },
			{-(size.x / 2.0f)  ,
			-(size.y / 2.0f)},
			{+(size.x / 2.0f),
			-(size.y / 2.0f)},
		};

		// カメラのvWVPVp行列取得
		Matrix3x3 vWVPVpMatrix = camera.GetWvpVpMatrix(pos, scale, angle);

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
			1, 1, static_cast<int>(size.x), static_cast<int>(size.y), gh, color);
	}
}

void Render::DrawNum(Vector2 pos, Vector2 size, Vector2 scale, float angle, Camera camera, int num, int* gh, unsigned int color) {
	Transform tempTransform = { 0 };
	tempTransform.pos = pos;
	tempTransform.scale = scale;
	tempTransform.size = size;
	tempTransform.angle = angle;
	
	int tempNum = num;
	int digit = 1;
	int numD[10] = { 0 };

	while (tempNum >= 10)
	{
		tempNum /= 10;
		digit++;
	}

	tempNum = num;
	for (int i = 0; i < digit; i++) {

		numD[i] = tempNum % 10;
		tempNum /= 10;
	}

	for (int i = 0; i < digit; i++) {
		Vector2 digitPos = { pos.x + ((size.x * static_cast<float>(i)) * 0.5f) - ((size.x * static_cast<float>(digit - (i + 1))) * 0.25f),0.0f };
		tempTransform.pos -= digitPos;

		DrawSprite(tempTransform,camera, color, gh[numD[i] % 10]);
	}
}
