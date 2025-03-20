#define _USE_MATH_DEFINES
#include "SelectScene.h"
#include "TitleScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"
#include "math.h"

#include "Class/Common/Render.h"
#include "Class/Common/MyEasing.h"

void SelectScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = sceneObj->gameStage;

	mainCamera.Init();

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	// ミッションの星の変数
	for (int i = 0; i < starTotalCount; ++i) {
		star[i] = {
			{ 320.0f + i * 320.0f, 560.0f }, // 位置
			{ 256.0f, 256.0f }, // 大きさ
			{ 1.0f, 1.0f }, // 比率
			2.0f * static_cast<float>(M_PI) / 3.0f * i // 角度
		};

		isStarMoving[i] = false;
		starT[i] = 0.0f;
		starColor[i] = 0xeeeeeeff;
	}

	// ステージアイコンの変数
	stageIconTheta = 0.0f;
	notSelectedStageScale = 0.6f;
	for (int i = 0; i < stageTotalCount; ++i) {
		stageIcon[i] = {
			{ 640.0f + i * 640.0f - gameStage * 640.0f, 288.0f },
			{ 256.0f, 256.0f },
			{ 1.0f, 1.0f },
			0.0f
		};

		stageIconT[i] = 0.0f;

		if (gameStage != i) {
			stageIcon[i].scale = { notSelectedStageScale,notSelectedStageScale };
		}
	}

	// AとDの矢印のUIの変数
	for (int i = 0; i < 2; ++i) {
		arrow[i] = {
			{250.0f + i * 780.0f,288.0f},
			{160.0f,160.0f},
			{1.0f,1.0f},
			0.0f
		};

		arrowTheta[i] = 0.0f;
	}

	arrow[0].scale = { 0.0f,0.0f };

	spaceUI = {
		{640.0f,64.0f},
		{448.0f,64.0f},
		{1.0f,1.0f},
		0.0f
	};

	bg = {
		{640.0f,360.0f},
		{1280.0f,720.0f},
		{1.0f,1.0f},
		0.0f
	};

	for (int i = 0; i < 3; ++i) {
		bgTheta[i] = 2.0f * static_cast<float>(M_PI) / 3.0f * i; // 角度
		bgColor[i] = ColorFade(0xffffffff, fabsf(sinf(star[i].angle)) * (0.15f - i * 0.06f));
	}

	// ミッションをクリアしたか
	starCount = 0;
	for (int i = 0; i < stageTotalCount; ++i) {
		for (int j = 0; j < starTotalCount; ++j) {
			shouldClearedMission[i][j] = sceneObj->shouldClearedMission[i][j];

			if (shouldClearedMission[i][j]) {
				starCount++;
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		playSEHandle[i] = -1;
	}

	playBGMHandle = -1;

	// 左右キーを押したときステージアイコンなどが動く時間
	movingFrameCount = 25.0f;

	if (starCount >= 2) {
		unlocking[0] = true;
	} else {
		unlocking[0] = false;
	}

	if (starCount >= 5) {
		unlocking[1] = true;
	} else {
		unlocking[1] = false;
	}

	isUnlocking = false;
	unlockingInterval = 180;
	unlockingTimes = 0;

	isZoom = false;

	shouldPressedRight = false;
	shouldPressedLeft = false;

	cameraPos = mainCamera.GetPosPtr();
	*cameraPos = { 640.0f,360.0f };

	zoomT = 0.0f;
	cameraZoom = { 1.0f,1.0f };
	mainCamera.SetScale(cameraZoom);

	tempGH = Novice::LoadTexture("./Resources/Images/tmpStageIcon.png");

	stageIconGraphHandle[0] = Novice::LoadTexture("./Resources/Images/stageIcon1.png");
	stageIconGraphHandle[1] = Novice::LoadTexture("./Resources/Images/stageIcon2.png");
	stageIconGraphHandle[2] = Novice::LoadTexture("./Resources/Images/stageIcon3.png");

	lockIconGraphHandle[0] = Novice::LoadTexture("./Resources/Images/lockStageIcon1.png");
	lockIconGraphHandle[1] = Novice::LoadTexture("./Resources/Images/lockStageIcon2.png");

	starGraphHandle = Novice::LoadTexture("./Resources/Images/missionStar.png");

	arrowGraphHandle[0] = Novice::LoadTexture("./Resources/Images/stageSelectArrow1.png");
	arrowGraphHandle[1] = Novice::LoadTexture("./Resources/Images/stageSelectArrow2.png");

	arrowPadGraphHandle[0] = Novice::LoadTexture("./Resources/Images/stageSelectArrowPad1.png");
	arrowPadGraphHandle[1] = Novice::LoadTexture("./Resources/Images/stageSelectArrowPad2.png");

	spaceUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/spaceUI.png");
	spaceUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/spaceUIB.png");

	aUIGraphHandle[0] = Novice::LoadTexture("./Resources/Images/A_DONE.png");
	aUIGraphHandle[1] = Novice::LoadTexture("./Resources/Images/A_DONEB.png");

	bgGraphHandle[0] = Novice::LoadTexture("./Resources/Images/bg1.png");
	bgGraphHandle[1] = Novice::LoadTexture("./Resources/Images/bg2.png");
	bgGraphHandle[2] = Novice::LoadTexture("./Resources/Images/bg3.png");

	sEHandle[0] = Novice::LoadAudio("./Resources/Sounds/dicision.mp3");
	sEHandle[1] = Novice::LoadAudio("./Resources/Sounds/slide.mp3");
	sEHandle[2] = Novice::LoadAudio("./Resources/Sounds/lock.mp3");
	sEHandle[3] = Novice::LoadAudio("./Resources/Sounds/break.mp3");

	numGH[0] = Novice::LoadTexture("./Resources/Images/Number1.png");
	numGH[1] = Novice::LoadTexture("./Resources/Images/Number2.png");
	numGH[2] = Novice::LoadTexture("./Resources/Images/Number3.png");
	numGH[3] = Novice::LoadTexture("./Resources/Images/Number4.png");
	numGH[4] = Novice::LoadTexture("./Resources/Images/Number5.png");
	numGH[5] = Novice::LoadTexture("./Resources/Images/Number6.png");
	numGH[6] = Novice::LoadTexture("./Resources/Images/Number7.png");
	numGH[7] = Novice::LoadTexture("./Resources/Images/Number8.png");
	numGH[8] = Novice::LoadTexture("./Resources/Images/Number9.png");
	numGH[9] = Novice::LoadTexture("./Resources/Images/Number10.png");

	highScore.Init();
	highScore.SetPos({ 246.0f + 64.0f + 32.0f,64.0f });
	highScore.SetSize({ 128.0f,128.0f });
	highScore.SetLocalScale({ 0.5f,0.5f });
	highScore.SetIsFillZero(true);

	crownGH = Novice::LoadTexture("./Resources/Images/crown.png");
	crownTransform = { 0.0f };
	crownTransform.pos = { 64.0f,70.0f };
	crownTransform.size = { 64.0f,64.0f };
	crownTransform.scale = { 1.0f,1.0f };
	crownTransform.angle = 0.0f;
	IconShakeRange = 0.0f;

	bGMHandle = Novice::LoadAudio("./Resources/Sounds/sceneBGM.mp3");
}

void SelectScene::Update() {

	mainCamera.Update();

	highScore.Update();
	highScore.SetTargetNum(sceneObj->stageHighScore[gameStage]);

	if (!Novice::IsPlayingAudio(playBGMHandle) || playBGMHandle == -1) {
		playBGMHandle = Novice::PlayAudio(bGMHandle, true, 0.2f);
	}

	frameCount++;
	if (frameCount >= 60) {
		frameCount = 0;
	}

	if (input->GetControl(RIGHT, Press)) {
		if (!shouldPressedRight) {
			if (!shouldPressedLeft) {
				if (!isZoom) {
					if (gameStage < stageTotalCount - 1) {
						gameStage++;
						shouldPressedRight = true;
						isUnlocking = false;
						for (int i = 0; i < starTotalCount; ++i) {
							starT[i] = 0.0f;
							isStarMoving[i] = true;
							star[i].scale = { 6.0f,6.0f };
						}

						for (int i = 0; i < stageTotalCount; ++i) {
							stageIconT[i] = 0.0f;
							stageIcon[i].pos.y = 288.0f;
							stageIconTheta = 0.0f;
						}

						for (int i = 0; i < 2; ++i) {
							arrowTheta[i] = 0.0f;
							arrow[i].angle = 0.0f;
						}

						playSEHandle[1] = Novice::PlayAudio(sEHandle[1], false, 0.8f);
					}
				}
			}
		}
	}

	if (input->GetControl(LEFT, Press)) {
		if (!shouldPressedRight) {
			if (!shouldPressedLeft) {
				if (!isZoom) {
					if (gameStage > 0) {
						gameStage--;
						shouldPressedLeft = true;
						isUnlocking = false;
						for (int i = 0; i < starTotalCount; ++i) {
							starT[i] = 0.0f;
							isStarMoving[i] = true;
							star[i].scale = { 6.0f,6.0f };
						}

						for (int i = 0; i < stageTotalCount; ++i) {
							stageIconT[i] = 0.0f;
							stageIcon[i].pos.y = 288.0f;
							stageIconTheta = 0.0f;
						}

						for (int i = 0; i < 2; ++i) {
							arrowTheta[i] = 0.0f;
							arrow[i].angle = 0.0f;
						}

						playSEHandle[1] = Novice::PlayAudio(sEHandle[1], false, 0.8f);
					}
				}
			}
		}
	}

	// 決定キーを押してシーンを遷移させる
	if (input->GetControl(ENTER, Triger)) {

		// ステージロック
		if (gameStage == 1 && !unlocking[0] || gameStage == 2 && !unlocking[1]) {

			mainCamera.shakeRange = { 14.0f,0.0f };
			IconShakeRange = 14.0f;

			if (!isUnlocking) {
				isUnlocking = true;
				unlockingInterval = 120;
				unlockingTimes = 0;
			}

			if (isUnlocking) {
				unlockingInterval--;
				unlockingTimes++;

				if (unlockingInterval <= 0) {
					isUnlocking = false;
					unlockingInterval = 120;
					unlockingTimes = 0;
					playSEHandle[2] = Novice::PlayAudio(sEHandle[2], false, 0.1f);
				} else {
					if (unlockingTimes >= 10) {
						if (gameStage == 1) {
							unlocking[0] = true;
							particleManager.SlashEffect({ stageIcon[1].pos.x, stageIcon[1].pos.y }, { 48.0f,48.0f }, { 1.0f,1.0f }, 20.0f, 100, 60, 64, 0);
						} else if (gameStage == 2) {
							unlocking[1] = true;
							particleManager.SlashEffect({ stageIcon[2].pos.x, stageIcon[2].pos.y }, { 48.0f,48.0f }, { 1.0f,1.0f }, 20.0f, 100, 60, 64, 0);
						}

						mainCamera.shakeRange = { 60.0f,20.0f };
						IconShakeRange = 60.0f;

						if (!Novice::IsPlayingAudio(playSEHandle[3]) || playSEHandle[3] == -1) {
							playSEHandle[3] = Novice::PlayAudio(sEHandle[3], false, 0.4f);
						}
					} else {
						playSEHandle[2] = Novice::PlayAudio(sEHandle[2], false, 0.1f);
					}
				}
			}

		} else {

			// ステージに遷移する
			if (!isZoom) {
				isZoom = true;
				if (!Novice::IsPlayingAudio(playSEHandle[0]) || playSEHandle[0] == -1) {
					playSEHandle[0] = Novice::PlayAudio(sEHandle[0], false, 0.8f);
				}
			}
		}
	}

	//================================================================
	// ステージアイコンの更新処理
	//================================================================

	// ステージアイコンの移動
	if (shouldPressedRight) {
		for (int i = 0; i < stageTotalCount; ++i) {
			// tに値を加算
			if (stageIconT[i] < 1.0f) {
				stageIconT[i] += 1.0f / movingFrameCount;
			}

			if (stageIconT[i] >= 1.0f) {
				stageIconT[i] = 1.0f;
				shouldPressedRight = false;
			}

			stageIcon[i].pos.x =
				Eas::EaseInOutQuart(
					stageIconT[i],
					(640.0f * stageTotalCount - (gameStage + 1.0f) * 640.0f) + (i * 640.0f),
					(640.0f * stageTotalCount - (gameStage + 2.0f) * 640.0f) + (i * 640.0f)
				);

			if (gameStage == i) {
				stageIcon[i].scale.x = Eas::EaseInOutQuart(stageIconT[i], notSelectedStageScale, 1.0f);
				stageIcon[i].scale.y = Eas::EaseInOutQuart(stageIconT[i], notSelectedStageScale, 1.0f);
			} else if (gameStage - 1 == i) {
				stageIcon[i].scale.x = Eas::EaseInOutQuart(stageIconT[i], 1.0f, notSelectedStageScale);
				stageIcon[i].scale.y = Eas::EaseInOutQuart(stageIconT[i], 1.0f, notSelectedStageScale);
			}

		}

		arrowTheta[1] += 1.0f / movingFrameCount * static_cast<float>(M_PI);
		arrow[1].pos.y = 288.0f + sinf(arrowTheta[1]) * 32.0f;

		if (gameStage == stageTotalCount - 1) {
			arrow[1].scale.x = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 0.0f);
			arrow[1].scale.y = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 0.0f);
			if (stageIconT[0] < 0.7f) {
				arrow[1].angle -= 1.0f / 8.0f * static_cast<float>(M_PI);
			} else if (stageIconT[0] < 0.8f) {
				arrow[1].angle -= 1.0f / 4.0f * static_cast<float>(M_PI);
			} else {
				arrow[1].angle -= 1.0f / 1.5f * static_cast<float>(M_PI);
			}
		} else {
			arrow[1].scale.x = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 1.0f);
			arrow[1].scale.y = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 1.0f);
		}

		if (gameStage == 1) {
			arrow[0].scale.x = Eas::EaseInOutQuart(stageIconT[0], 0.0f, 1.0f);
			arrow[0].scale.y = Eas::EaseInOutQuart(stageIconT[0], 0.0f, 1.0f);
		}
	}

	if (shouldPressedLeft) {
		for (int i = 0; i < stageTotalCount; ++i) {
			// tに値を加算
			if (stageIconT[i] < 1.0f) {
				stageIconT[i] += 1.0f / movingFrameCount;
			}

			if (stageIconT[i] >= 1.0f) {
				stageIconT[i] = 1.0f;
				shouldPressedLeft = false;
			}

			stageIcon[i].pos.x =
				Eas::EaseInOutQuart(
					stageIconT[i],
					(640.0f * stageTotalCount - (gameStage + 3.0f) * 640.0f) + (i * 640.0f),
					(640.0f * stageTotalCount - (gameStage + 2.0f) * 640.0f) + (i * 640.0f)
				);

			if (gameStage == i) {
				stageIcon[i].scale.x = Eas::EaseInOutQuart(stageIconT[i], notSelectedStageScale, 1.0f);
				stageIcon[i].scale.y = Eas::EaseInOutQuart(stageIconT[i], notSelectedStageScale, 1.0f);
			} else  if (gameStage + 1 == i) {
				stageIcon[i].scale.x = Eas::EaseInOutQuart(stageIconT[i], 1.0f, notSelectedStageScale);
				stageIcon[i].scale.y = Eas::EaseInOutQuart(stageIconT[i], 1.0f, notSelectedStageScale);
			}
		}

		arrowTheta[0] += 1.0f / movingFrameCount * static_cast<float>(M_PI);
		arrow[0].pos.y = 256.0f + sinf(arrowTheta[0]) * 32.0f;

		if (gameStage == 0) {
			arrow[0].scale.x = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 0.0f);
			arrow[0].scale.y = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 0.0f);
			if (stageIconT[0] < 0.7f) {
				arrow[0].angle += 1.0f / 8.0f * static_cast<float>(M_PI);
			} else if (stageIconT[0] < 0.8f) {
				arrow[0].angle += 1.0f / 4.0f * static_cast<float>(M_PI);
			} else {
				arrow[0].angle += 1.0f / 1.5f * static_cast<float>(M_PI);
			}
		} else {
			arrow[0].scale.x = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 1.0f);
			arrow[0].scale.y = Eas::EaseInOutQuart(stageIconT[0], 1.3f, 1.0f);
		}

		if (gameStage == stageTotalCount - 2) {
			arrow[1].scale.x = Eas::EaseInOutQuart(stageIconT[0], 0.0f, 1.0f);
			arrow[1].scale.y = Eas::EaseInOutQuart(stageIconT[0], 0.0f, 1.0f);
		}
	}

	for (int i = 0; i < stageTotalCount; ++i) {
		if (gameStage == i) {
			if (!shouldPressedLeft && !shouldPressedRight) {
				stageIconTheta -= 1.0f / 90.0f * static_cast<float>(M_PI);
				stageIcon[i].pos.y = 288.0f + sinf(stageIconTheta) * 8.0f;
			}
		}
	}

	for (int i = 0; i < 2; ++i) {
		if (!shouldPressedLeft && !shouldPressedRight) {
			arrowTheta[i] += 1.0f / 90.0f * static_cast<float>(M_PI);
			arrow[i].pos.y = 288.0f + sinf(arrowTheta[i]) * 4.0f;
		}
	}

	spaceUI.pos.y = 64.0f + cosf(stageIconTheta) * 1.0f;

	//================================================================
	// 星の更新処理
	//================================================================

	for (int i = 0; i < starTotalCount; ++i) {
		// 星の縮小の処理
		if (isStarMoving[i]) {

			// tに値を加算
			if (starT[i] < 1.0f) {
				starT[i] += 1.0f / movingFrameCount;
			}

			if (starT[i] >= 1.0f) {
				starT[i] = 1.0f;

				if (isStarMoving[i]) {
					isStarMoving[i] = false;
				}
			}

			if (starT[i] < 0.8f) {
				star[i].angle += 1.0f / 10.0f * static_cast<float>(M_PI);
			} else if (starT[i] < 0.9f) {
				star[i].angle += 1.0f / 60.0f * static_cast<float>(M_PI);
			} else {
				star[i].angle += 1.0f / 120.0f * static_cast<float>(M_PI);
			}

			star[i].scale.x = Eas::EaseInOutQuart(starT[i], 6.0f, 1.0f);
			star[i].scale.y = Eas::EaseInOutQuart(starT[i], 6.0f, 1.0f);

			star[i].pos.x = Eas::EaseInOutQuart(starT[i], i * 640.0f, 320.0f + i * 320.0f);
			star[i].pos.y = Eas::EaseInOutQuart(starT[i], 1488.0f, 560.0f);
		} else {
			star[i].angle += 1.0f / 180.0f * static_cast<float>(M_PI);
			star[i].pos.y = 560.0f + sinf(star[i].angle * 3.0f) * 8.0f;
		}

		// ===================================================================================//
		if (shouldClearedMission[gameStage][i]) { //ミッションをクリアしたか
			//====================================================================================//
			if (frameCount % 5 == 0) {
				particleManager.PointEffect(
					{ star[i].pos.x + Random(90.0f,0.0f) * cosf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)),
					  star[i].pos.y + Random(90.0f,0.0f) * sinf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)) },
					20, 0, 0xeeeeeeff
				);

				/*particleManager.PointEffect(
					{ star[i].pos.x + Random(90.0f,0.0f) * cosf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)),
					  star[i].pos.y + Random(90.0f,0.0f) * sinf(Random(180.0f, -180.0f) / 180.0f * static_cast<float>(M_PI)) },
					20, 0, ColorGradation(0xeeeeeeff, 0xe8c9beff, Random(100.0f, 0.0f) / 100.0f)
				);*/
			}

			//starColor[i] = ColorGradation(0xeeeeeeff, 0xe8c9beff, fabsf(sinf(star[i].angle)));
			//starColor[i] = ColorGradation(0xeeeeeeff, 0xe8c9beff, fabsf(sinf(star[i].angle)));
		}
	}

	for (int i = 0; i < 3; ++i) {
		bgTheta[i] += 1.0f / 180.0f * static_cast<float>(M_PI);
		bgColor[i] = ColorFade(0xffffffff, fabsf(sinf(bgTheta[i])) * (0.15f - i * 0.06f));
	}

	if (isZoom) {
		if (zoomT < 1.0f) {
			zoomT += 1.0f / 35.0f;
		}

		if (zoomT >= 1.0f) {
			zoomT = 1.0f;
			Novice::StopAudio(playBGMHandle);
			nextScene = new GameStageScene();
			isTransition = true;
			sceneObj->gameStage = gameStage;
		}

		cameraZoom.x = Eas::EaseInOutQuart(zoomT, 1.0f, 0.55f);
		cameraZoom.y = Eas::EaseInOutQuart(zoomT, 1.0f, 0.55f);

		cameraPos->y = Eas::EaseInOutQuart(zoomT, 360.0f, 288.0f);
	}

	mainCamera.SetScale(cameraZoom);

	particleManager.Update();
}

void SelectScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222831FF, kFillModeSolid);

	for (int i = 0; i < 3; ++i) {
		Render::DrawSprite(bg, mainCamera, bgColor[i], bgGraphHandle[i]);
	}


	for (int i = 0; i < stageTotalCount; ++i) {

		if (i == 0) {
			Render::DrawSprite(stageIcon[i], mainCamera, 0xffffffFF, stageIconGraphHandle[i]);
		}
		if (i == 1) {
			if (unlocking[0]) {
				Render::DrawSprite(stageIcon[i], mainCamera, 0xffffffFF, stageIconGraphHandle[i]);
			} else {
				Render::DrawSprite(stageIcon[i], mainCamera, 0xffffffFF, lockIconGraphHandle[0]);
			}

		}
		if (i == 2) {
			if (unlocking[1]) {
				Render::DrawSprite(stageIcon[i], mainCamera, 0xffffffFF, stageIconGraphHandle[i]);
			} else {
				Render::DrawSprite(stageIcon[i], mainCamera, 0xffffffFF, lockIconGraphHandle[1]);
			}
		}

	}
	particleManager.Draw();

	for (int i = 0; i < starTotalCount; ++i) {
		// ===================================================================================//
		if (shouldClearedMission[gameStage][i]) { //ミッションをクリアしたか
			//====================================================================================//
			Render::DrawSprite(star[i], mainCamera, starColor[i], starGraphHandle);
		} else {
			Render::DrawSprite(star[i], mainCamera, 0xeeeeee22, starGraphHandle);
		}
	}

	for (int i = 0; i < 2; ++i) {
		if (Novice::GetNumberOfJoysticks() == 0) {
			Render::DrawSprite(arrow[i], mainCamera, 0xffffffff, arrowGraphHandle[i]);
		} else {
			Render::DrawSprite(arrow[i], mainCamera, 0xffffffff, arrowPadGraphHandle[i]);
		}
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

	// ハイスコア表示
	highScore.Draw(&mainCamera, numGH);
	Render::DrawSprite(crownTransform, mainCamera, WHITE, crownGH);
}

IScene* SelectScene::GetNextScene() {
	return nextScene;
}
