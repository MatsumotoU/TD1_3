#include "TitleScene.h"
#include "SelectScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"
#include "Class/Common//MyEasing.h"
#include "Class/Common/Render.h"
#include "Class/Common/MyMath.h"

void TitleScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);
	mainCamera.Init();

	// タイトルロゴの変数
	logo[0] =
	{
		0.0f,100.0f,
		650.0f,350.0f,
		1.0f,1.0f,0.0f
	};

	logo[1] =
	{
		0.0f,187.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	startLogo[0] =
	{
		0.0f,187.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	endLogo[0] =
	{
		-162.0f,187.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	logo[2] =
	{
		0.0f,28.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	startLogo[1] =
	{
		0.0f,28.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	endLogo[1] =
	{
		163.0f,28.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	isEaseStart = false;

	// エフェクトの変数
	efect.pos.x = -500.0f;
	efect.pos.y = 100.0f;
	efect.size.x = 10.0f;
	efect.size.y = 10.0f;
	efectDir.x = -1.0f;
	efectDir.y = 0.0f;
	efectT = 0.0f;
	efectCoolTime = 60;
	isEfectMove = false;
}

void TitleScene::Update() {

	if (input->GetTriger(DIK_R))
	{
		Init();
	}

	if (efectCoolTime >= 0)
	{
		efectCoolTime--;

		if (efectCoolTime == 0)
		{
			isEfectMove = true;
		}
	}
	else if (isEfectMove)
	{
		particleManager.SlashEffect(efect.pos, efect.size, efectDir, 10.0f, 5, 10, 10, 0);
		particleManager.Update();

		// エフェクトを横に動かす処理
		efect.pos.x += 128.0f;

		if (efect.pos.x >= -340.0f)
		{
			// エフェクトが当たったら点滅させる
			alphaValue += 16.0f;
			color = ColorFade(color, alphaValue);
		}

		if (efect.pos.x >= 700.0f)
		{
			// エフェクトが右端に到達した時の処理
			isEfectMove = false;
			isEaseStart = true;
		}
	}
	else if (isEaseStart)
	{
		if (efectT <= 1.0f)
		{
			// ロゴをイージングさせる処理
			efectT += 0.015f;
			logo[1].pos.x = Eas::EaseIn(efectT,4.0f, startLogo[0].pos.x, endLogo[0].pos.x);
			logo[2].pos.x = Eas::EaseIn(efectT,4.0f, startLogo[1].pos.x, endLogo[1].pos.x);
		}
	}
}

void TitleScene::Draw() {

	if (isEaseStart)
	{
		// ロゴの描画処理
		Render::DrawSprite(logo[1], mainCamera, BLACK, 0);
		Render::DrawSprite(logo[2], mainCamera, BLACK, 0);
	}
	else
	{
		// ロゴの描画処理
		Render::DrawSprite(logo[0], mainCamera, BLACK, 0);

		if (isEfectMove)
		{
			// 点滅の描画処理
			Render::DrawSprite(logo[0], mainCamera, color, 0);
			// パーティクルの描画処理
			particleManager.Draw();
		}
	}

}

IScene* TitleScene::GetNextScene() {
	return nullptr;
}