#define _USE_MATH_DEFINES
#include "SelectScene.h"
#include "TitleScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"
#include "math.h"

#include "Class/Common/Render.h"
#include "Class/Common/MyEasing.h"

void ResultScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	mainCamera.Init();

	subCamera.Init();

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	// ミッションの星の変数
	for (int i = 0; i < starTotalCount; ++i) {
		star[i] = {
			{ 1600.0f,i * 360.0f }, // 位置
			{ 256.0f, 256.0f }, // 大きさ
			{ 1.0f, 1.0f }, // 比率
			2.0f * static_cast<float>(M_PI) / 3.0f * i // 角度
		};

		isStarMoving[i] = false;
		starT[i] = 0.0f;
	}

	for (int i = 0; i < starTotalCount; ++i) {
		missionUI[i] = {
			{ -640.0f,160.0f + i * 200.0f }, // 位置
			{ 720.0f, 80.0f }, // 大きさ
			{ 1.0f, 1.0f }, // 比率
			0.0f // 角度
		};

		isMissionUIMoving[i] = true;
		missionUIT[i] = 0.0f;
	}

	for (int i = 0; i < 2; ++i) {
		button[i] = {
			{ 384.0f + i * 512.0f,-128.0f }, // 位置
			{ 400.0f, 80.0f }, // 大きさ
			{ 0.8f, 0.8f }, // 比率
			0.0f // 角度
		};

		isButtonMoving[i] = false;
		buttonT[i] = 0.0f;
	}

	button[1].scale = { 1.0f,1.0f };

	// ミッションをクリアしたか

	if (sceneObj->isNotDeathClear) {
		shouldClearedMission[0] = true;
		if (!sceneObj->shouldClearedMission[gameStage][0]) {
			sceneObj->shouldClearedMission[gameStage][0] = true;
		}
	} else {
		shouldClearedMission[0] = false;
	}

	if (sceneObj->score >= 10000) {
		shouldClearedMission[1] = true;

		if (!sceneObj->shouldClearedMission[gameStage][1]) {
			sceneObj->shouldClearedMission[gameStage][1] = true;
		}

	} else {
		shouldClearedMission[1] = false;
	}
	if (shouldClearedMission[0] && shouldClearedMission[1]) {
		shouldClearedMission[2] = true;
		if (!sceneObj->shouldClearedMission[gameStage][2]) {
			sceneObj->shouldClearedMission[gameStage][2] = true;
		}
	} else {
		shouldClearedMission[2] = false;
	}

	spaceUI = {
		{-128.0f,-128.0f},
		{192.0f,64.0f},
		{0.8f,0.8f},
		0.0f
	};

	bg = {
		{640.0f,360.0f},
		{1280.0f,720.0f},
		{1.0f,1.0f},
		0.0f
	};

	isBgDrawn = false;

	for (int i = 0; i < 3; ++i) {
		bgColor[i] = 0x22283100;
	}

	for (int i = 0; i < 2; ++i) {
		cracker[i] = {
			{ -128.0f + i * 1536.0f,-128.0f }, // 位置
			{ 256.0f,256.0f }, // 大きさ
			{ 1.0f, 1.0f }, // 比率
			0.0f // 角度
		};

		crackerT[i] = 0.0f;
		crackerAlpha[i] = 255;
		isCrackerMoving[i] = false;
	}

	for (int i = 0; i < 10; ++i) {
		playSEHandle[i] = -1;
	}

	cracker[0].angle = 1.0f / 10.0f * static_cast<float>(M_PI);
	cracker[1].angle = 19.0f / 10.0f * static_cast<float>(M_PI);

	movingOrder = 0;

	// 動く時間
	movingFrameCount = 15.0f;

	shouldPressedRight = true;
	shouldPressedLeft = false;

	//isDuringAnimation = true;

	cameraPos[0] = mainCamera.GetPosPtr();
	*cameraPos[0] = { 640.0f,360.0f };

	cameraPos[1] = subCamera.GetPosPtr();
	*cameraPos[1] = { 640.0f,360.0f };

	cameraZoom = { 1.0f,1.0f };

	flashAlpha = 0;

	starGraphHandle = Novice::LoadTexture("./Resources/Images/missionStar.png");

	missionUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/mission1.png");
	missionUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/mission2.png");
	missionUIGraphHandle[2] = Novice::LoadTexture("./Resources/Images/mission3.png");

	nextSceneUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/retry.png");
	nextSceneUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/select.png");

	spaceUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/spaceUIResult.png");
	spaceUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/spaceUIResultB.png");

	aUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/AbuttonResult.png");
	aUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/AbuttonResultB.png");

	crackerGraphHandle[0] = Novice::LoadTexture("./Resources/Images/cracker1.png");
	crackerGraphHandle[1] = Novice::LoadTexture("./Resources/Images/cracker2.png");

	bgGraphHandle[0] = Novice::LoadTexture("./Resources/Images/bg1.png");
	bgGraphHandle[1] = Novice::LoadTexture("./Resources/Images/bg2.png");
	bgGraphHandle[2] = Novice::LoadTexture("./Resources/Images/bg3.png");

	sEHandle[0] = Novice::LoadAudio("./Resources/Sounds/dicision.mp3");
	sEHandle[1] = Novice::LoadAudio("./Resources/Sounds/cracker.mp3");
	sEHandle[2] = Novice::LoadAudio("./Resources/Sounds/select.mp3");
	sEHandle[3] = Novice::LoadAudio("./Resources/Sounds/slide.mp3");
}

void ResultScene::Update() {
	frameCount++;
	if (frameCount >= 30) {
		if (movingOrder == 0) {
			movingOrder++;
		}
	}

	if (frameCount >= 600) {
		frameCount = 0;
	}

	if (input->GetControl(RIGHT, Press)) {
		if (!shouldPressedRight) {
			shouldPressedRight = true;
			shouldPressedLeft = false;

			playSEHandle[2] = Novice::PlayAudio(sEHandle[2], false, 0.8f);
		}
	}

	if (input->GetControl(LEFT, Press)) {
		if (!shouldPressedLeft) {
			shouldPressedRight = false;
			shouldPressedLeft = true;

			playSEHandle[2] = Novice::PlayAudio(sEHandle[2], false, 0.8f);
		}
	}

	// 決定キーを押してシーンを遷移させる
	if (input->GetControl(ENTER, Triger)) {
		if (movingOrder >= 18) {

			// ステージに遷移する
			if (shouldPressedLeft) {
				if (!shouldPressedRight) {
					nextScene = new GameStageScene();
				}
			}

			if (shouldPressedRight) {
				if (!shouldPressedLeft) {
					nextScene = new SelectScene();
				}
			}

			isTransition = true;

			if (!Novice::IsPlayingAudio(playSEHandle[0]) || playSEHandle[0] == -1) {
				playSEHandle[0] = Novice::PlayAudio(sEHandle[0], false, 0.8f);
			}
		} else {
			movingOrder = 18;
			for (int i = 0; i < starTotalCount; ++i) {
				starT[i] = 1.0f;
				star[i].pos.x = Eas::EaseInOutQuart(starT[i], 1728.0f, 1008.0f);
				star[i].pos.y = Eas::EaseInOutQuart(starT[i], i * 360.0f, 270.0f + i * 160.0f);
				star[i].scale = { 0.8f,0.8f };

				missionUIT[i] = 1.0f;
				missionUI[i].pos.x = Eas::EaseInOutQuart(missionUIT[i], -640.0f, 384.0f);
				missionUI[i].pos.y = Eas::EaseInOutQuart(missionUIT[i], 160.0f + i * 200.0f, 270.0f + i * 160.0f);
				missionUI[i].scale = { 0.8f,0.8f };
			}

			flashAlpha = 255;

			for (int i = 0; i < 2; ++i) {
				buttonT[i] = 1.0f;
				button[i].pos.y = Eas::EaseInOutQuart(buttonT[i], -128.0f, 80.0f);
			}
		}
	}

	if (movingOrder >= 18) {
		if (shouldPressedLeft) {
			button[0].scale = { 1.0f,1.0f };
			button[1].scale = { 0.8f,0.8f };
			spaceUI.pos.x = button[0].pos.x;
			spaceUI.pos.y = button[0].pos.y + 80.0f;
			button[0].pos.y = 80.0f + sinf(star[0].angle * 3.0f) * 4.0f;

			spaceUI.pos.y = button[0].pos.y + 80.0f + cosf(star[1].angle * 3.0f) * 1.0f;
		}

		if (shouldPressedRight) {
			button[0].scale = { 0.8f,0.8f };
			button[1].scale = { 1.0f,1.0f };
			spaceUI.pos.x = button[1].pos.x;
			spaceUI.pos.y = button[1].pos.y + 80.0f;
			button[1].pos.y = 80.0f + sinf(star[1].angle * 3.0f) * 4.0f;

			spaceUI.pos.y = button[1].pos.y + 80.0f + cosf(star[1].angle * 3.0f) * 1.0f;
		}
	}

	if (flashAlpha > 0) {
		flashAlpha -= 8;
	}

	if (flashAlpha <= 10) {
		flashAlpha = 0;
	}

	//================================================================
	// 星の更新処理
	//================================================================

	for (int i = 0; i < starTotalCount; ++i) {
		if (movingOrder == 4) {
			isStarMoving[i] = true;
			if (i < 2) {
				if (!isCrackerMoving[i]) {
					isCrackerMoving[i] = true;
				}
			}
		}

		// 星の縮小の処理

		if (isStarMoving[i]) {
			if (movingOrder < 7) {
				// tに値を加算
				if (starT[i] < 1.0f) {
					starT[i] += 1.0f / 25.0f;
				}

				if (starT[i] >= 1.0f) {
					starT[i] = 1.0f;

					if (isStarMoving[i]) {
						isStarMoving[i] = false;
						movingOrder++;
					}
				}

				if (starT[i] >= 0.75f && starT[i] <= 0.80f) {
					if (i < 2) {
						cracker[i].scale = { 1.4f,1.4f };

						if (!Novice::IsPlayingAudio(playSEHandle[1]) && playSEHandle[1] == -1) {
							playSEHandle[1] = Novice::PlayAudio(sEHandle[1], false, 0.2f);
						}
					}
				}

				if (starT[i] >= 0.80f && starT[i] <= 0.85f) {
					cameraZoom = { 1.18f,1.18f };
					particleManager.CrackerEffect({ 0.0f,0.0f }, { 48.0f,48.0f }, 4.5f / 13.0f * static_cast<float>(M_PI), 60.0f, 2.0f, -2.0f, 60, 24, 0, ColorGradation(0xeeeeeeff, 0xd65a31ff, Random(100.0f, 0.0f) / 100.0f));
					particleManager.CrackerEffect({ 1300.0f,0.0f }, { 48.0f,48.0f }, 8.5f / 13.0f * static_cast<float>(M_PI), 60.0f, 2.0f, -2.0f, 60, 24, 0, ColorGradation(0xeeeeeeff, 0xd65a31ff, Random(100.0f, 0.0f) / 100.0f));
				}

				if (starT[i] < 0.8f) {
					star[i].angle += 1.0f / 20.0f * static_cast<float>(M_PI);
				} else if (starT[i] < 0.9f) {
					star[i].angle += 1.0f / 80.0f * static_cast<float>(M_PI);
				} else {
					star[i].angle += 1.0f / 100.0f * static_cast<float>(M_PI);
				}

				star[i].scale.x = Eas::EaseInOutQuart(starT[i], 6.0f, 1.0f);
				star[i].scale.y = Eas::EaseInOutQuart(starT[i], 6.0f, 1.0f);

				star[i].pos.x = Eas::EaseInOutQuart(starT[i], 1728.0f, 1008.0f);
				star[i].pos.y = Eas::EaseInOutQuart(starT[i], i * 360.0f, 160.0f + i * 200.0f);
			} else {
				// tに値を加算
				if (starT[i] < 1.0f) {
					starT[i] += 1.0f / 25.0f;
				}

				if (starT[i] >= 1.0f) {
					starT[i] = 1.0f;

					if (isStarMoving[i]) {
						isStarMoving[i] = false;
						movingOrder++;
					}
				}

				star[i].angle += 1.0f / 180.0f * static_cast<float>(M_PI);
				star[i].scale.x = Eas::EaseInOutQuart(starT[i], 1.0f, 0.8f);
				star[i].scale.y = Eas::EaseInOutQuart(starT[i], 1.0f, 0.8f);
				star[i].pos.y = Eas::EaseInOutQuart(starT[i], 160.0f + i * 200.0f, 270.0f + i * 160.0f);
			}
		} else {
			star[i].angle += 1.0f / 180.0f * static_cast<float>(M_PI);

			if (movingOrder >= 7 && movingOrder <= 9) {
				star[i].pos.y = (160.0f + i * 200.0f) + sinf(star[i].angle * 3.0f) * 8.0f;
				if (frameCount >= 125) {
					starT[i] = 0.0f;
					isStarMoving[i] = true;
					movingOrder++;
				}
			} else {
				star[i].pos.y = (270.0f + i * 160.0f) + sinf(star[i].angle * 3.0f) * 8.0f;
			}
		}

		if (frameCount % 5 == 0) {
			// ===================================================================================//
			if (shouldClearedMission[i]) { //ミッションをクリアしたか
				//====================================================================================//
				particleManager.PointEffect(
					{ star[i].pos.x + Random(90.0f,0.0f) * cosf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)),
					  star[i].pos.y + Random(90.0f,0.0f) * sinf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)) },
					20, 0, 0xeeeeeeff
				);

				/*particleManager.PointEffect(
					{ star[i].pos.x + Random(90.0f,0.0f) * cosf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)),
					  star[i].pos.y + Random(90.0f,0.0f) * sinf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)) },
					20, 0, ColorGradation(0xeeeeeeff, 0xd65a31ff, Random(100.0f, 0.0f) / 100.0f)
				);*/
			}
		}
	}

	//================================================================
	// クラッカーの更新処理
	//================================================================

	for (int i = 0; i < 2; ++i) {
		if (isCrackerMoving[i]) {
			if (crackerT[i] < 1.0f) {
				crackerT[i] += 1.0f / 13.0f;
			}

			if (crackerT[i] >= 1.0f) {
				crackerT[i] = 1.0f;
				isCrackerMoving[i] = false;
			}

			cracker[i].pos.x = Eas::EaseInOutQuart(crackerT[i], -128.0f + i * 1536.0f, 96.0f + i * 1088.0f);
			cracker[i].pos.y = Eas::EaseInOutQuart(crackerT[i], -128.0f, 96.0f);
		} else {
			if (crackerT[i] == 1.0f) {
				if (cracker[i].scale.x > 1.0f) {
					cracker[i].scale.x -= 0.05f;
				}

				if (cracker[i].scale.y > 1.0f) {
					cracker[i].scale.y -= 0.05f;
				}

				if (crackerAlpha[i] >= 1) {
					crackerAlpha[i] -= 4;

					if (crackerAlpha[i] <= 4) {
						crackerAlpha[i] = 0;
					}
				}
			}
		}
	}

	//================================================================
	// ミッションのUIの更新処理
	//================================================================

	if (movingOrder < 4) {
		for (int i = 0; i < movingOrder; ++i) {
			if (isMissionUIMoving[i]) {

				if (missionUIT[i] == 0.0f) {
					playSEHandle[3] = Novice::PlayAudio(sEHandle[3], false, 0.8f);
				}

				// tに値を加算
				if (missionUIT[i] < 1.0f) {
					missionUIT[i] += 1.0f / movingFrameCount;
				}

				if (missionUIT[i] >= 1.0f) {
					missionUIT[i] = 1.0f;
				}

				missionUI[i].pos.x = Eas::EaseInOutQuart(missionUIT[i], -640.0f, 384.0f);

				if (movingOrder < 4) {
					if (missionUIT[i] >= 1.0f) {
						if (isMissionUIMoving[i]) {
							isMissionUIMoving[i] = false;
							movingOrder++;
							break;
						}
					}
				}
			}
		}
	} else if (movingOrder > 7) {
		for (int i = 0; i < starTotalCount; ++i) {
			if (isMissionUIMoving[i]) {
				if (missionUIT[i] < 1.0f) {
					missionUIT[i] += 1.0f / 25.0f;
				}

				if (missionUIT[i] >= 1.0f) {
					missionUIT[i] = 1.0f;

					if (isMissionUIMoving[i]) {
						isBgDrawn = true;
						isMissionUIMoving[i] = false;
						movingOrder++;
					}
				}

				bgColor[i] = ColorGradation(0x2228310f, 0xffffff0a, missionUIT[i]);

				missionUI[i].scale.x = Eas::EaseInOutQuart(missionUIT[i], 1.0f, 0.8f);
				missionUI[i].scale.y = Eas::EaseInOutQuart(missionUIT[i], 1.0f, 0.8f);
				missionUI[i].pos.y = Eas::EaseInOutQuart(missionUIT[i], 160.0f + i * 200.0f, 270.0f + i * 160.0f);
			} else {
				if (movingOrder == 10) {
					missionUIT[i] = 0.0f;
					isMissionUIMoving[i] = true;
				}
			}
		}
	}

	for (int i = 0; i < 2; ++i) {
		if (isButtonMoving[i]) {
			if (buttonT[i] < 1.0f) {
				buttonT[i] += 1.0f / 25.0f;
			}

			if (buttonT[i] >= 1.0f) {
				buttonT[i] = 1.0f;

				if (isButtonMoving[i]) {
					isButtonMoving[i] = false;
					movingOrder++;
				}
			}

			button[i].pos.y = Eas::EaseInOutQuart(buttonT[i], -128.0f, 80.0f);
		} else {
			if (movingOrder == 10) {
				buttonT[i] = 0.0f;
				isButtonMoving[i] = true;
			}
		}
	}

	if (isBgDrawn) {
		for (int i = 0; i < 3; ++i) {
			if (movingOrder >= 10) {
				bgColor[i] = ColorFade(0xffffffff, fabsf(cosf(star[i].angle)) * (0.15f - i * 0.06f));
			}
		}
	}

	if (cameraZoom.x > 1.0f) {
		cameraZoom.x -= 0.015f;
		if (cameraZoom.x <= 1.0f) {
			cameraZoom.x = 1.0f;
		}
	}

	if (cameraZoom.y > 1.0f) {
		cameraZoom.y -= 0.015f;
		if (cameraZoom.y <= 1.0f) {
			cameraZoom.y = 1.0f;
		}
	}

	mainCamera.SetScale(cameraZoom);

	particleManager.Update();
}

void ResultScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222831FF, kFillModeSolid);

	for (int i = 0; i < 3; ++i) {
		Render::DrawSprite(bg, mainCamera, bgColor[i], bgGraphHandle[i]);
	}

	for (int i = 0; i < starTotalCount; ++i) {
		// ===================================================================================//
		if (shouldClearedMission[i]) { //ミッションをクリアしたか
			//====================================================================================//
			Render::DrawSprite(star[i], mainCamera, 0xEEEEEEFF, starGraphHandle);
		} else {
			Render::DrawSprite(star[i], mainCamera, 0x393E46FF, starGraphHandle);
		}
	}

	for (int i = 0; i < starTotalCount; ++i) {
		Render::DrawSprite(missionUI[i], mainCamera, 0xEEEEEEFF, missionUIGraphHandle[i]);
	}

	for (int i = 0; i < 2; ++i) {
		Render::DrawSprite(button[i], mainCamera, 0xEEEEEEFF, nextSceneUIGraphHandle[i]);
	}

	if (Novice::GetNumberOfJoysticks() == 0) {
		if (input->GetControl(ENTER, Press)) {
			Render::DrawSprite(spaceUI, mainCamera, 0xFFFFFFFF, spaceUIGraphHandle[1]);
		} else {
			Render::DrawSprite(spaceUI, mainCamera, 0xEEEEEEFF, spaceUIGraphHandle[0]);
		}
	} else {
		if (input->GetControl(ENTER, Press)) {
			Render::DrawSprite(spaceUI, mainCamera, 0xFFFFFFFF, aUIGraphHandle[1]);
		} else {
			Render::DrawSprite(spaceUI, mainCamera, 0xEEEEEEFF, aUIGraphHandle[0]);
		}
	}

	particleManager.Draw();

	for (int i = 0; i < 2; ++i) {
		Render::DrawSprite(cracker[i], subCamera, 0xffffff00 | crackerAlpha[i], crackerGraphHandle[i]);
	}

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xffffff00 | flashAlpha, kFillModeSolid);

	//Novice::ScreenPrintf(0, 16, "%d", movingOrder);
	//Novice::ScreenPrintf(0, 32, "%d", frameCount);
}

IScene* ResultScene::GetNextScene() {
	return nextScene;
}
