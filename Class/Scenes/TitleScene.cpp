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

	particleManager.SetCamera(&mainCamera);
	mainCamera.Init();

	// タイトルロゴの変数
	logo[0] =
	{
		640.0f,460.0f,
		650.0f,350.0f,
		1.0f,1.0f,0.0f
	};

	logo[1] =
	{
		640.0f,547.0f,
		650.0f,logo[0].size.y/2.0f,
		1.0f,1.0f,0.0f
	};

	startLogo[0] =
	{
		640.0f,547.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	endLogo[0] =
	{
		478.0f,547.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	logo[2] =
	{
		640.0f,logo[0].pos.y - 87.5f,
		650.0f,logo[0].size.y / 2.0f,
		1.0f,1.0f,0.0f
	};

	startLogo[1] =
	{
		640.0f,388.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	endLogo[1] =
	{
		803.0f,388.0f,
		650.0f,175.0f,
		1.0f,1.0f,0.0f
	};

	// スペースキーの位置の変数
	button[2] =
	{
		640.0f,135.0f,
		600.0f,150.0f,
		1.0f,1.0f,0.0f
	};

	button[0] =
	{
		640.0f,button[2].pos.y + button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	button[1] =
	{
		640.0f,button[2].pos.y - button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	startButton[0] =
	{
		640.0f,button[2].pos.y + button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	startButton[1] =
	{
		640.0f,button[2].pos.y - button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	endButton[0] =
	{
		540.0f,button[2].pos.y + button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	endButton[1] =
	{
		760.0f,button[2].pos.y - button[2].size.y / 4.0f,
		600.0f,75.0f,
		1.0f,1.0f,0.0f
	};

	isEaseStart = false;

	efect[0] =
	{
		40.0f,460.0f,
		0.0f,50.0f,
		1.0f,1.0f,0.0f
	};

	efect[1] =
	{
		1240.0f,button[2].pos.y,
		0.0f,25.0f,
		1.0f,1.0f,0.0f
	};

	
	// エフェクトの変数
	efectT[0] = 0.0f;
	efectT[1] = 0.0f;
	efectCoolTime = 60;
	isEfectMove = false;
	isUnderEfectMove = false;
	isMoveEnd = false;
	color[0] = 0xFFFFFFFF;
	returnColor[0] = 0xFFFFFFFF;
	alphaValue[0] = 1.0f;
	color[1] = 0xFFFFFF00;
	returnColor[1] = 0xFFFFFF00;
	alphaValue[1] = 0.0f;
	blinkTimer = 60;
	efectNum = 0;

	cameraPos = mainCamera.GetPosPtr();
	*cameraPos = { 640.0f,360.0f };

	// 画像番号を格納する
	titleLogoGh[0] = Novice::LoadTexture("./Resources/Images/titleLogo3.png");
	titleLogoGh[1] = Novice::LoadTexture("./Resources/Images/titleLogo1.png");
	titleLogoGh[2] = Novice::LoadTexture("./Resources/Images/titleLogo2.png");
	buttonGh[0] = Novice::LoadTexture("./Resources/Images/button1.png");
	buttonGh[1] = Novice::LoadTexture("./Resources/Images/button2.png");
	buttonGh[2] = Novice::LoadTexture("./Resources/Images/button.png");
	bigEfectGh[0] = Novice::LoadTexture("./Resources/Images/bigEfect1.png");
	bigEfectGh[1] = Novice::LoadTexture("./Resources/Images/bigEfect2.png");
	bigEfectGh[2] = Novice::LoadTexture("./Resources/Images/bigEfect3.png");
	bigEfectGh[3] = Novice::LoadTexture("./Resources/Images/bigEfect4.png");
	bigEfectGh[4] = Novice::LoadTexture("./Resources/Images/bigEfect5.png");
	bigEfectGh[5] = Novice::LoadTexture("./Resources/Images/bigEfect6.png");
	bigEfectGh[6] = Novice::LoadTexture("./Resources/Images/bigEfect7.png");
	bigEfectGh[7] = Novice::LoadTexture("./Resources/Images/bigEfect8.png");
	bigEfectGh[8] = Novice::LoadTexture("./Resources/Images/bigEfect9.png");
	smallEfectGh[0] = Novice::LoadTexture("./Resources/Images/smallEfect1.png");
	smallEfectGh[1] = Novice::LoadTexture("./Resources/Images/smallEfect2.png");
	smallEfectGh[2] = Novice::LoadTexture("./Resources/Images/smallEfect3.png");
	smallEfectGh[3] = Novice::LoadTexture("./Resources/Images/smallEfect4.png");
	smallEfectGh[4] = Novice::LoadTexture("./Resources/Images/smallEfect5.png");
	smallEfectGh[5] = Novice::LoadTexture("./Resources/Images/smallEfect6.png");
	smallEfectGh[6] = Novice::LoadTexture("./Resources/Images/smallEfect7.png");
	smallEfectGh[7] = Novice::LoadTexture("./Resources/Images/smallEfect8.png");
	smallEfectGh[8] = Novice::LoadTexture("./Resources/Images/smallEfect9.png");

}

void TitleScene::Update() {

	
	if (efectT[1] >= 0.9f)
	{
		// デタラメ文字列のフェードアウト処理
		if (alphaValue[0] > 0.0f)
		{
			alphaValue[0] -= 0.1f;

			if (alphaValue[0] <= 0.0f)
			{
				alphaValue[0] = 0.0f;
			}

		}

		returnColor[0] = ColorFade(color[0], alphaValue[0]);
	}


	if (efectT[1] >= 1.0f)
	{
		// PressSpaceのフェードイン処理
		if (alphaValue[1] < 1.0f)
		{
			alphaValue[1] += 0.1f;

			if (alphaValue[1] >= 1.0f)
			{
				alphaValue[1] = 1.0f;
			}

		}

		returnColor[1] = ColorFade(color[1], alphaValue[1]);
	}

	if (efectNum > 0)
	{
		// 斬撃エフェクトのアニメーションカウント
		efectNum++;

		if (efectNum >= 16)
		{
			efectNum = 16;
		}
	}

	if (efectCoolTime >= 0)
	{
		// エフェクト開始までの待ち時間処理
		efectCoolTime--;

		if (efectCoolTime == 0)
		{
			isEfectMove = true;
			efectNum = 1;
			mainCamera.shakeRange = { 50.0f,0.0f };
		}
	}
	else if (isEfectMove)
	{
		// エフェクトを横に動かす処理
		efect[0].size.x += 800.0f;

		if (efect[0].size.x >= 3600.0f)
		{
			// エフェクトが右端に到達した時の処理
			isEfectMove = false;
			isUnderEfectMove = true;
			mainCamera.shakeRange = { 50.0f,0.0f };
		}
	}
	else if (isUnderEfectMove)
	{
		// エフェクトを横に動かす処理
		efect[1].size.x += 800.0f;
		efect[1].pos.x -= 100.0f;

		if (efect[1].size.x >= 3600.0f)
		{
			// エフェクトが右端に到達した時の処理	
			isUnderEfectMove = false;
			isEaseStart = true;
			alphaValue[0] = 1.0f;
		
		}

	}
	else if (isEaseStart)
	{
		if (efectT[1] <= 1.0f)
		{
			// ロゴをイージングさせる処理
			efectT[1] += 0.015f;
			button[0].pos.x = Eas::EaseIn(efectT[1], 4.0f, startButton[0].pos.x, endButton[0].pos.x);
			button[1].pos.x = Eas::EaseIn(efectT[1], 4.0f, startButton[1].pos.x, endButton[1].pos.x);
		}

		if (efectT[0] <= 1.0f)
		{
			// ロゴをイージングさせる処理
			efectT[0] += 0.015f;
			logo[1].pos.x = Eas::EaseIn(efectT[0], 4.0f, startLogo[0].pos.x, endLogo[0].pos.x);
			logo[2].pos.x = Eas::EaseIn(efectT[0], 4.0f, startLogo[1].pos.x, endLogo[1].pos.x);
		}
		else
		{
			// イージング終わった時の処理
			isEaseStart = false;
			isMoveEnd = true;
		}
	}
	else if (isMoveEnd)
	{
		// PressSpaceを点滅させる処理
		if (blinkTimer >= 0)
		{
			blinkTimer--;
		}
		else
		{
			blinkTimer = 60;
		}

		// シーン遷移処理
		if (input->GetTriger(DIK_SPACE)) {
			isTransition = true;// こいつをtrueにすると即座にシーン遷移する(シーンのUpdateは止まる)
		}

	}

	mainCamera.Update();
}

void TitleScene::Draw() {
	
	// 背景の描画処理
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222831FF, kFillModeSolid);
	
	if (blinkTimer / 30 == 0)
	{
		// PressSpaceの描画処理
		Render::DrawSprite(button[2], mainCamera, returnColor[1], buttonGh[2]);
	}

	if (efectCoolTime >= 0)
	{
		// ロゴの描画処理
		Render::DrawSprite(logo[0], mainCamera, 0xFFFFFFFF, titleLogoGh[0]);
	}

	if (isMoveEnd)
	{
		// ロゴの描画処理
		Render::DrawSprite(logo[1], mainCamera, 0xFFFFFFFF,titleLogoGh[1]);
		Render::DrawSprite(logo[2], mainCamera, 0xFFFFFFFF, titleLogoGh[2]);
		Render::DrawSprite(button[0], mainCamera, returnColor[0], buttonGh[0]);
		Render::DrawSprite(button[1], mainCamera, returnColor[0], buttonGh[1]);

	}
	else
	{

		if (isEaseStart)
		{
			// ロゴの描画処理
			Render::DrawSprite(logo[1], mainCamera, 0xFFFFFFFF, titleLogoGh[1]);
			Render::DrawSprite(logo[2], mainCamera, 0xFFFFFFFF, titleLogoGh[2]);
		}
		else if (isEfectMove)
		{
			// ロゴの描画処理
			Render::DrawSprite(logo[0], mainCamera, 0xFFFFFFFF, titleLogoGh[0]);
		}
		else if (isUnderEfectMove)
		{
			// ロゴの描画処理
			Render::DrawSprite(logo[1], mainCamera, 0xFFFFFFFF, titleLogoGh[1]);
			Render::DrawSprite(logo[2], mainCamera, 0xFFFFFFFF, titleLogoGh[2]);
			Render::DrawSprite(button[0], mainCamera, returnColor[0], buttonGh[0]);
			Render::DrawSprite(button[1], mainCamera, returnColor[0], buttonGh[1]);

		}

		// デタラメ文字列の描画処理
		Render::DrawSprite(button[0], mainCamera, returnColor[0], buttonGh[0]);
		Render::DrawSprite(button[1], mainCamera, returnColor[0], buttonGh[1]);
		// エフェクトの描画処理
		Render::DrawSprite(efect[0], mainCamera, 0xFFFFFFFF,bigEfectGh[efectNum / 2]);
		Render::DrawSprite(efect[1], mainCamera, 0xFFFFFFFF, smallEfectGh[efectNum / 2]);
	}
}

IScene* TitleScene::GetNextScene() {
	return new SelectScene();
}