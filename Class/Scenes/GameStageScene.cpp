#include "GameStageScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "ResultScene.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

#include "Class/Common/MyEasing.h"
#include "Class/Common/Collision2D.h"

void GameStageScene::Init() {
	frameCount = 0;
	wave = 0;
	isTransition = false;
	gameStage = 0;
	nextScene = nullptr;
	mainCamera.Init();
	isClearStage = true;
	clearStageTimeBuffer = 0;

	seVolume = 0.5f;

	exprosionComboCount = 0;
	comboRemainFrame = 0;
	comboOP[0] = Novice::LoadAudio("./Resources/Sounds/combo1.mp3");
	comboOP[1] = Novice::LoadAudio("./Resources/Sounds/combo2.mp3");
	comboOP[2] = Novice::LoadAudio("./Resources/Sounds/combo3.mp3");
	comboOP[3] = Novice::LoadAudio("./Resources/Sounds/combo4.mp3");
	comboOP[4] = Novice::LoadAudio("./Resources/Sounds/combo5.mp3");

	playerAttackOP = Novice::LoadAudio("./Resources/Sounds/playerAttack.mp3");

	flashScreenFrame = 0;

	stopObjectUpdateFrame = 0;
	exprosionHitStopFrame = 7;

	player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	bulletManager.SetLightManager(&lightManager);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);
	enemyManager.SetPlayerPos(player.GetPosPtr());
	enemyManager.SetMapchip(&map);
	lastHitEnemyNum = -1;

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	map.SetCamera(&mainCamera);
	map.SetPlayer(&player);
	map.SetEnemyManager(&enemyManager);
	map.SetBulletManager(&bulletManager);
	if (sceneObj->gameStage == 0) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage1w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage1w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage1w3.txt");
		}
	} else if (sceneObj->gameStage == 1) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage2w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage2w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage2w3.txt");
		}
	} else if (sceneObj->gameStage == 2) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage3w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage3w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage3w3.txt");
		}
	}

	testPopEnemyPos = { 1024.0f,1024.0f };
	isChangeWave = false;

	for (int i = 0; i < EMG::kMaxEnemy + 1; i++) {
		baranceObjects[i].Init();
		baranceObjects[i].SetCamera(&mainCamera);
	}
	balanceAngle = 0.0f;
	balancePoleTransform = {
		{0.0f,-64.0f},
		{300.0f,400.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketTransform[0] = {
		{240.0f,-64.0f},
		{256.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketTransform[1] = {
		{-240.0f,-64.0f},
		{256.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketGH = Novice::LoadTexture("./Resources/Images/balanceBasket.png");
	balancePoleGH = Novice::LoadTexture("./Resources/Images/balancePole.png");

	waveStringTransform = {
		{0.0f,256.0f},
		{512.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	waveStringGH = Novice::LoadTexture("./Resources/Images/wave.png");

	playerWeightGH = Novice::LoadTexture("./Resources/Images/playerWeight.png");
	enemyWeightGH = Novice::LoadTexture("./Resources/Images/enemyWeight.png");

	slashGH = Novice::LoadTexture("./Resources/Images/slash.png");

	shakeContorolInfoExprosion = 0.0f;
	contorolInfoTransform[0] = {
		{-160.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoTransform[1] = {
		{160.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoTransform[2] = {
		{0.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoGH[0] = Novice::LoadTexture("./Resources/Images/tutorial1.png");
	contorolInfoGH[1] = Novice::LoadTexture("./Resources/Images/tutorial2.png");
	contorolInfoGH[2] = Novice::LoadTexture("./Resources/Images/tutorial3.png");
	contorolInfoGH[3] = Novice::LoadTexture("./Resources/Images/tutorial4.png");

	rcContorolInfoGH[0] = Novice::LoadTexture("./Resources/Images/RCtutorial1.png");
	rcContorolInfoGH[1] = Novice::LoadTexture("./Resources/Images/RCtutorial2.png");
	rcContorolInfoGH[2] = Novice::LoadTexture("./Resources/Images/RCtutorial3.png");
	rcContorolInfoGH[3] = Novice::LoadTexture("./Resources/Images/RCtutorial4.png");

	hitEffectGH[0] = Novice::LoadTexture("./Resources/Images/hiteffect256_1.png");
	hitEffectGH[1] = Novice::LoadTexture("./Resources/Images/hiteffect256_2.png");
	hitEffectGH[2] = Novice::LoadTexture("./Resources/Images/hiteffect256_3.png");

	contorolTutorialUI.Init();
	contorolTutorialUI.SetCamera(&uiCamera);
	contorolTutorialUI.SetPlayer(&player);
	contorolTutorialUI.SetEnemyManager(&enemyManager);

	playerHpUI.Init();
	playerHpUI.SetCamera(&uiCamera);
	playerHpUI.SetPlayer(&player);
	player.SetMapchip(&map);

	targetScoreNum.Init();
	targetScoreNum.SetPos({ 0.0f,-128.0f });
	targetScoreNum.SetSize({ 128.0f,128.0f });
	enemyRemainNumGH[0] = Novice::LoadTexture("./Resources/Images/Number1.png");
	enemyRemainNumGH[1] = Novice::LoadTexture("./Resources/Images/Number2.png");
	enemyRemainNumGH[2] = Novice::LoadTexture("./Resources/Images/Number3.png");
	enemyRemainNumGH[3] = Novice::LoadTexture("./Resources/Images/Number4.png");
	enemyRemainNumGH[4] = Novice::LoadTexture("./Resources/Images/Number5.png");
	enemyRemainNumGH[5] = Novice::LoadTexture("./Resources/Images/Number6.png");
	enemyRemainNumGH[6] = Novice::LoadTexture("./Resources/Images/Number7.png");
	enemyRemainNumGH[7] = Novice::LoadTexture("./Resources/Images/Number8.png");
	enemyRemainNumGH[8] = Novice::LoadTexture("./Resources/Images/Number9.png");
	enemyRemainNumGH[9] = Novice::LoadTexture("./Resources/Images/Number10.png");
	targetScoreNum.SetTargetNum(map.GetEnemyNum());

	clossGH = Novice::LoadTexture("./Resources/Images/X.png");

	waveNumber.Init();
	waveNumber.SetSize({ 128.0f,128.0f });
	waveNumber.SetLocalScale({ 1.5f,1.5f });

	targetEnemyUiGH = Novice::LoadTexture("./Resources/Images/targetEnemy.png");
	missionGH = Novice::LoadTexture("./Resources/Images/mission.png");

	// 一番最初の位置バグ修正用
	player.Update();
	mainCamera.SetPos(player.GetPos());

	lightManager.Init();
	lightManager.SetCamera(&mainCamera);

	cameraLocalScale = 1.45f;
	//cameraLocalScale = 1.0f;
	mainCamera.SetLocalScale({ cameraLocalScale,cameraLocalScale });

	comboUI.Init();
	comboUI.SetCamera(&uiCamera);
	comboUI.SetCombo(&exprosionComboCount, &comboRemainFrame);
	playerAttackStopFrame = 0;

	playerAttackHitCount = 0;
	playerStopClockUI.Init();
	playerStopClockUI.SetCamera(&uiCamera);
	playerStopClockUI.SetPlayerAttackStopFrame(&playerAttackStopFrame);
	playerStopClockUI.SetPlayerAttackComboCount(&playerAttackHitCount);

	scoreUIManager.Init();
	scoreUIManager.SetCamera(&mainCamera);

	score = 0;

	gameScore.Init();
	gameScore.SetIsFillZero(true);
	gameScore.SetSize({ 128.0f,128.0f });
	gameScore.SetPos({ 580.0f,310.0f });
	gameScore.SetLocalScale({ 0.5f,0.5f });

	scoreTitle = { 0.0f };
	scoreTitle.pos = { 240.0f,310.0f };
	scoreTitle.size = { 512.0f,128.0f };
	scoreTitle.scale = { 0.5f,0.5f };
	scoreTitleGH = Novice::LoadTexture("./Resources/Images/ScoreTitle.png");

	isNotDeath = true;
	isSlowFrame = false;
	slowFrameScoreRatio = 1.0f;

	scoreRatio.Init();
	scoreRatio.SetSize({ 128.0f,128.0f });
	scoreRatio.SetPos({ 580.0f,230.0f });
	scoreRatio.SetLocalScale({ 0.7f,0.7f });

	//stageStartGH = Novice::LoadTexture("./Resources/Images/StageStart.png");

	gameTime = 3600;
	//gameTime = 1200;
	timeNum.Init();
	timeNum.SetSize({ 128.0f,128.0f });
	timeNum.SetPos({ 0.0f,0.0f });
	timeNum.SetLocalScale({ 3.0f,3.0f });
	timeNum.SetColor(0xEEEEEE13);

	enemyBloodGH = Novice::LoadTexture("./Resources/Images/blood.png");

	exprosionGH[0] = Novice::LoadTexture("./Resources/Images/Explosion1.png");
	exprosionGH[1] = Novice::LoadTexture("./Resources/Images/Explosion2.png");
	exprosionGH[2] = Novice::LoadTexture("./Resources/Images/Explosion3.png");
	exprosionGH[3] = Novice::LoadTexture("./Resources/Images/Explosion4.png");
	exprosionGH[4] = Novice::LoadTexture("./Resources/Images/Explosion5.png");
	exprosionGH[5] = Novice::LoadTexture("./Resources/Images/Explosion6.png");
	exprosionGH[6] = Novice::LoadTexture("./Resources/Images/Explosion7.png");

	enemyBulletGH = Novice::LoadTexture("./Resources/Images/enemyBullet.png");

	playerHitGH[0] = Novice::LoadTexture("./Resources/Images/Hitmark1.png");
	playerHitGH[1] = Novice::LoadTexture("./Resources/Images/Hitmark2.png");
	playerHitGH[2] = Novice::LoadTexture("./Resources/Images/Hitmark3.png");
	playerHitGH[3] = Novice::LoadTexture("./Resources/Images/Hitmark4.png");
	playerHitGH[4] = Novice::LoadTexture("./Resources/Images/Hitmark5.png");

	comboTrigerCooldown = 0;

	 isStartingGame = false;
	 startGameBufferFrame = 0;
	 startGH = Novice::LoadTexture("./Resources/Images/start.png");

	 enemySpawnFrame = 0;
	 isEndGame = false;

	 isTimeUp = false;
	 timeUpTransitionFrame = 0;
	 timeUpGH = Novice::LoadTexture("./Resources/Images/timeUp.png");

	 playHandleBgm = -1;
	 opBgHandleBgm = Novice::LoadAudio("./Resources/Sounds/sceneBGM.mp3");

	 if (Novice::IsPlayingAudio(playHandleBgm) == 0 || playHandleBgm == -1) {
		 playHandleBgm = Novice::PlayAudio(opBgHandleBgm, true, 0.2f);
	 }
	 selectSE = Novice::LoadAudio("./Resources/Sounds/dicision.mp3");
	 playerHitSE = Novice::LoadAudio("./Resources/Sounds/playerHit.mp3");

	 bgGraphHandle[0] = Novice::LoadTexture("./Resources/Images/bg1.png");
	 bgGraphHandle[1] = Novice::LoadTexture("./Resources/Images/bg2.png");
	 bgGraphHandle[2] = Novice::LoadTexture("./Resources/Images/bg3.png");
}

void GameStageScene::Update() {

	if (isTimeUp) {

		if (timeUpTransitionFrame > 0) {
			timeUpTransitionFrame--;
		} else {
			sceneObj->isNotDeathClear = player.GetIsAlive();
			isTransition = true;
			nextScene = new ResultScene();
			Novice::StopAudio(playHandleBgm);

			if (sceneObj->stageHighScore[sceneObj->gameStage] < score) {
				sceneObj->stageHighScore[sceneObj->gameStage] = score;
			}
			sceneObj->SaveScore();
		}
		return;
	}

	map.Update();
	timeNum.SetPos({ 48.0f * static_cast<float>(timeNum.GetDigit()),0.0f });

	//mainCamera.SetLocalScale({ cameraLocalScale,cameraLocalScale });

	mainCamera.Update();
	frameCount++;

	WaveManager();
	ControlInfoUpdate();
	contorolTutorialUI.Update();
	playerHpUI.Update();
	lightManager.Update();
	comboUI.Update();
	playerStopClockUI.Update();
	scoreUIManager.Update();
	gameScore.Update();
	gameScore.SetTargetNum(score);

	scoreRatio.Update();
	scoreRatio.SetTargetNum(static_cast<int>(slowFrameScoreRatio));

	// 時間制限遷移
	if (gameTime <= 0) {

		//Novice::ConsolePrintf("----------TimeTransition!----------\n");
		isTimeUp = true;
		timeUpTransitionFrame = 120;
		return;
	}

	timeNum.Update();
	timeNum.SetTargetNum(gameTime / 60);

	if (gameTime <= 600) {
		if (gameTime % 30 > 15) {
			timeNum.SetColor(0xEEEEEEAF);
		} else {
			timeNum.SetColor(0xEEEEEE23);
		}
	}

	if (!isChangeWave) {
		if (stopObjectUpdateFrame <= 0) {
			ObjectUpdate();
			ObjectCollision();
		} else {
			stopObjectUpdateFrame--;
		}
	}

	/*if (enemyManager.GetRemainEnemies() <= 0) {
		if (stopObjectUpdateFrame > 0) {
			Eas::SimpleEaseIn(&mainCamera.GetPosPtr()->x, enemyManager.GetEnemyes()[lastHitEnemyNum].GetPos().x, 0.3f);
			Eas::SimpleEaseIn(&mainCamera.GetPosPtr()->y, enemyManager.GetEnemyes()[lastHitEnemyNum].GetPos().y, 0.3f);
		}
	}*/
	ImGuiUpdate();

	if (flashScreenFrame > 0) {
		flashScreenFrame--;
	}

	if (playerAttackStopFrame > 0) {
		playerAttackStopFrame--;
		slowFrameScoreRatio += 0.01f;
	} else {
		playerAttackHitCount = 0;
	}

	sceneObj->score = score;
}

void GameStageScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222831FF, kFillModeSolid);

	Transform bg = {
		{640.0f,360.0f},
		{1280.0f,720.0f},
		{1.0f,1.0f},
		0.0f
	};
	for (int i = 0; i < 3; ++i) {
		//Novice::DrawSprite(0, 0, bgGraphHandle[i], 1.0f, 1.0f, 0.0f, ColorFade(0xeeeeee23, fabsf(sinf(static_cast<float>(frameCount + i * 30) * 0.1f)) * (0.15f - i * 0.06f)));
	}

	//map.DrawTile();

	if (!isChangeWave && player.GetIsAlive()) {
		timeNum.Draw(&uiCamera, enemyRemainNumGH);
		playerStopClockUI.Draw();
	}

	if (playerAttackStopFrame <= 0) {

		bulletManager.Draw();
		enemyManager.Draw();
		player.Draw();
		map.Draw();

	} else {

		Novice::SetBlendMode(kBlendModeExclusion);
		bulletManager.Draw();
		enemyManager.Draw();
		map.Draw();
		Novice::SetBlendMode(kBlendModeNormal);

		player.Draw();
	}

	if (player.GetIsAlive()) {

		if (!isChangeWave) {
			scoreUIManager.Draw();
			playerHpUI.Draw();
		}
		
		if (!isStartingGame) {
			WaveUiDraw();
		}
		
		ControlInfoDraw();
		contorolTutorialUI.Draw();
		comboUI.Draw();
	}

	particleManager.Draw();
	lightManager.Draw();

	if (!isChangeWave && player.GetIsAlive()) {

		/*Novice::DrawBox(1100, 170,
			static_cast<int>(140.0f * (-1.0f + slowFrameScoreRatio)) - (140 * static_cast<int>(-1.0f + slowFrameScoreRatio)),
			16, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(1100, 170, 140, 16, 0.0f, WHITE, kFillModeWireFrame);
		Novice::DrawSprite(1132 - 32 * scoreRatio.GetDigit(), 100, clossGH, 0.5f, 0.5f, 0.0f, WHITE);*/
		gameScore.Draw(&uiCamera, enemyRemainNumGH);
		//scoreRatio.Draw(&uiCamera, enemyRemainNumGH);

		Render::DrawSprite(scoreTitle, uiCamera, WHITE, scoreTitleGH);
	}

	if (isStartingGame) {
		float eventT = 1.0f - static_cast<float>(startGameBufferFrame) / static_cast<float>(GMScene::startEventMaxFrame);
		//for (int i = 0; i < 18; i++) {

		//	/*if (i % 2) {
		//		Novice::DrawBox(0 - static_cast<int>(640.0f * powf(eventT, 3.0f * static_cast<float>(i + 1))), 40 * i, 640, 40, 0.0f, 0x393E46FF, kFillModeSolid);
		//		Novice::DrawBox(640 + static_cast<int>(640.0f * powf(eventT, 3.0f * static_cast<float>(i + 1))), 40 * i, 640, 40, 0.0f, 0x393E46FF, kFillModeSolid);
		//	} else {
		//		Novice::DrawBox(0 - static_cast<int>(640.0f * powf(eventT, 3.0f * static_cast<float>(i + 1))), 40 * i, 640, 40, 0.0f, 0x222831FF, kFillModeSolid);
		//		Novice::DrawBox(640 + static_cast<int>(640.0f * powf(eventT, 3.0f * static_cast<float>(i + 1))), 40 * i, 640, 40, 0.0f, 0x222831FF, kFillModeSolid);
		//	}*/

		//	
		//	
		//}

		if (startGameBufferFrame >= GMScene::startEventMaxFrame / 2) {
			Novice::DrawSprite(0, static_cast<int>(Eas::EaseOut(eventT * 2.0f, 6.0f, -480.0f, 0.0f)), startGH, 1.0f, 1.0f, 0.0f, WHITE);
		} else {
			Novice::DrawSprite(0, static_cast<int>(Eas::EaseIn(eventT * 2.0f, 4.0f, -480.0f,0.0f )), startGH, 1.0f, 1.0f, 0.0f, WHITE);
		}
		
		
	}

	if (flashScreenFrame > 0) {
		if (flashScreenFrame % 6 <= 3) {
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFFFFFF23, kFillModeSolid);
		}
	}

	if (isTimeUp) {
		float eventT = 1.0f - static_cast<float>(timeUpTransitionFrame) / static_cast<float>(120);

		if (timeUpTransitionFrame >= 120 / 2) {
			Novice::DrawSprite(0, static_cast<int>(Eas::EaseOut(eventT * 2.0f, 6.0f, -480.0f, 0.0f)), timeUpGH, 1.0f, 1.0f, 0.0f, WHITE);
		} else {
			Novice::DrawSprite(0, static_cast<int>(Eas::EaseIn(eventT * 2.0f, 4.0f, -480.0f, 0.0f)), timeUpGH, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}

	//Novice::ScreenPrintf(0, 80, "%f", slowFrameScoreRatio);
}

void GameStageScene::ImGuiUpdate() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::InputFloat("cameraScale", &cameraLocalScale);

	ImGui::Text("GameStage = %d Wave = %d", gameStage, wave);
	ImGui::Text("combo = %d :%d", exprosionComboCount, comboRemainFrame);
	ImGui::InputFloat("x", &testPopEnemyPos.x);
	ImGui::InputFloat("y", &testPopEnemyPos.y);
	ImGui::SliderFloat("balanceAngle", &balanceAngle, -3.14f, 3.14f);
	if (ImGui::Button("PopEnemy")) {
		enemyManager.SpawnEnemy(testPopEnemyPos, ENM::Melee);
	}

	if (ImGui::Button("CreateEnemyRoute")) {
		for (int e = 0; e < EMG::kMaxEnemy; e++) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
				enemyManager.GetEnemyes()[e].SetPlayerRoute(map.GetMapStoG(enemyManager.GetEnemyes()[e].GetPos(), player.GetPos()));
			}
		}
	}

	ImGui::End();

	player.UpdateImGui();

#endif // _DEBUG
}

IScene* GameStageScene::GetNextScene() {
	return nextScene;
}

void GameStageScene::WaveManager() {
	
	if (!isChangeWave) {
		enemySpawnFrame++;
	}

	if (enemyManager.GetRemainEnemies() <= 0 || enemySpawnFrame >= 1200) {
		wave++;
		if (wave <= 3) {
			LoadWave();
			enemySpawnFrame = 0;
		} else {
			// test
			if (enemyManager.GetRemainEnemies() <= 0 ) {
				sceneObj->isNotDeathClear = player.GetIsAlive();
				/*isTransition = true;
				nextScene = new ResultScene();*/
				
				if (!isEndGame) {
					clearStageTimeBuffer = GMScene::maxClearStageTimeBuffer;
					isClearStage = true;
					isEndGame = true;
				}
				
			}
		}
	}

	if (isClearStage || !player.GetIsAlive()) {
		if (!isChangeWave) {
			player.SetDrawLockOn(false);
			frameCount = 0;

			// ステージクリア後の演出時間
			if (isClearStage) {

				if (clearStageTimeBuffer > 0) {
					clearStageTimeBuffer--;
					return;
				} else {

					// ステージ上のすべての敵殲滅遷移
					if (wave >= 3) {
						sceneObj->isNotDeathClear = player.GetIsAlive();
						isTransition = true;
						nextScene = new ResultScene();
						Novice::StopAudio(playHandleBgm);
						//Novice::ConsolePrintf("----------StageClearTransition!----------\n");
						if (sceneObj->stageHighScore[sceneObj->gameStage] < score) {
							sceneObj->stageHighScore[sceneObj->gameStage] = score;
						}
						sceneObj->SaveScore();
						return;
					}
				}

				// プレイヤーが死んだときの遷移
				if (!player.GetIsAlive()) {
					isNotDeath = false;
					sceneObj->isNotDeathClear = isNotDeath;
					isTransition = true;
					nextScene = new ResultScene();
					Novice::StopAudio(playHandleBgm);
					//Novice::ConsolePrintf("----------PlayerDeathTransition!----------\n");
					if (sceneObj->stageHighScore[sceneObj->gameStage] < score) {
						sceneObj->stageHighScore[sceneObj->gameStage] = score;
					}
					sceneObj->SaveScore();
					return;
				}

			} else {

				isClearStage = true;
				clearStageTimeBuffer = GMScene::maxClearStageTimeBuffer;
				frameCount = 0;
				return;
			}

			// ステージ切り替え用オブジェクト初期化
			isChangeWave = true;
			if (player.GetIsAlive()) {
				//wave++;
			}
			waveStringTransform.pos.y = 400.0f;
			/*waveNumber.SetPos({ 256.0f + 32.0f,400.0f });
			waveNumber.SetTargetNum(wave);
			waveNumber.SetLocalScale({ 1.5f,1.5f });*/
			targetScoreNum.SetPos({ 0.0f,-600.0f });
			clossTransform = targetScoreNum.GetTransform();
			clossTransform.pos.x = 0.0f;
			enemyTargetTransform = targetScoreNum.GetTransform();
			enemyTargetTransform.pos.x *= -1.0f;
			enemyTargetTransform.size = { 256.0f,256.0f };
			missionTransform = clossTransform;
			missionTransform.size = { 512.0f,128.0f };
			missionTransform.pos.y = -600.0f;

			// ステージ切り替え
			if (sceneObj->gameStage == 0) {
				if (wave == 1) {
					map.LoadMap("Resources/Maps/stage1w1.txt");
				} else if (wave == 2) {
					map.LoadMap("Resources/Maps/stage1w2.txt");
				} else if (wave == 3) {
					map.LoadMap("Resources/Maps/stage1w3.txt");
				}
			} else if (sceneObj->gameStage == 1) {
				if (wave == 1) {
					map.LoadMap("Resources/Maps/stage2w1.txt");
				} else if (wave == 2) {
					map.LoadMap("Resources/Maps/stage2w2.txt");
				} else if (wave == 3) {
					map.LoadMap("Resources/Maps/stage2w3.txt");
				}
			} else if (sceneObj->gameStage == 2) {
				if (wave == 1) {
					map.LoadMap("Resources/Maps/stage3w1.txt");
				} else if (wave == 2) {
					map.LoadMap("Resources/Maps/stage3w2.txt");
				} else if (wave == 3) {
					map.LoadMap("Resources/Maps/stage3w3.txt");
				}
			}

			targetScoreNum.Init();
			targetScoreNum.SetTargetNum(sceneObj->targetScore[sceneObj->gameStage]);

			/*comboRemainFrame = 0;
			exprosionComboCount = 0;*/
		}
	}

	if (isChangeWave) {

		// 時間別イベント
		if (frameCount <= 60) {
			Eas::SimpleEaseIn(&waveStringTransform.pos.y, 200.0f + 32.0f, 0.3f);
			//Eas::SimpleEaseIn(&waveNumber.GetPosPtr()->y, 156.0f + 32.0f, 0.3f);
		}
		if (frameCount >= 60) {
			//waveNumber.Update();
		}
		if (ScopeVar(frameCount, 60, 120)) {
			Eas::SimpleEaseIn(&targetScoreNum.GetPosPtr()->y, 0.0f, 0.5f);
		}
		if (frameCount >= 120) {
			targetScoreNum.Update();
			targetScoreNum.SetPos({ 27.0f * static_cast<float>(targetScoreNum.GetDigit()),targetScoreNum.GetPosPtr()->y });
		}

		// 継続イベント
		waveStringTransform.scale = {
			1.0f - sinf(static_cast<float>(frameCount) * 0.1f) * 0.01f,
			1.0f - sinf(static_cast<float>(frameCount) * 0.1f) * 0.01f };
		clossTransform = targetScoreNum.GetTransform();
		clossTransform.pos.x = 0.0f;
		clossTransform.scale = { 1.0f,1.0f };
		waveNumber.SetLocalScale({
			1.5f - sinf(static_cast<float>(frameCount) * 0.1f) * 0.05f,
			1.5f - sinf(static_cast<float>(frameCount) * 0.1f) * 0.05f });
		enemyTargetTransform = targetScoreNum.GetTransform();
		enemyTargetTransform.pos.x *= -1.1f;
		enemyTargetTransform.size = { 256.0f,256.0f };
		missionTransform = clossTransform;
		missionTransform.size = { 512.0f,128.0f };
		missionTransform.pos.y += 152.0f;

		targetScoreNum.SetLocalScale(waveStringTransform.scale);

		contorolTutorialUI.SetIsActive(false);

		// ウェーブ管理処理演出終了
		if (wave >= 4 || (input->GetControl(ENTER, Triger) && frameCount >= 60)) {
			
			if (!isStartingGame) {
				isStartingGame = true;
				startGameBufferFrame = GMScene::startEventMaxFrame;
				flashScreenFrame = 10;
				Novice::PlayAudio(selectSE, false, seVolume);
			}
			
		}

		// スタート演出用
		if (isStartingGame) {
			if (startGameBufferFrame >= 0) {
				startGameBufferFrame--;
			} else {
				
				isStartingGame = false;
				isChangeWave = false;
				isClearStage = false;
				lastHitEnemyNum = -1;

				contorolTutorialUI.SetIsActive(true);
			}
		}
	}

	// 敵を殲滅したときのやつ(2)
	if (enemyManager.GetRemainEnemies() <= 0) {
		if (clearStageTimeBuffer <= 0) {
			if (wave > 3) {
				sceneObj->isNotDeathClear = player.GetIsAlive();
				isTransition = true;
				nextScene = new ResultScene();
				Novice::StopAudio(playHandleBgm);
				score += 200 * gameTime;
				//Novice::ConsolePrintf("----------EnemyDeathTransition!----------\n");
				if (sceneObj->stageHighScore[sceneObj->gameStage] < score) {
					sceneObj->stageHighScore[sceneObj->gameStage] = score;
				}
				sceneObj->SaveScore();
				return;
			}
		}
	}
}

void GameStageScene::LoadWave() {
	/*player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);
	enemyManager.SetPlayerPos(player.GetPosPtr());
	particleManager.Init();
	particleManager.SetCamera(&mainCamera);*/

	// ステージ切り替え
	if (sceneObj->gameStage == 0) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage1w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage1w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage1w3.txt");
		}
	} else if (sceneObj->gameStage == 1) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage2w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage2w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage2w3.txt");
		}
	} else if (sceneObj->gameStage == 2) {
		if (wave == 1) {
			map.LoadMap("Resources/Maps/stage3w1.txt");
		} else if (wave == 2) {
			map.LoadMap("Resources/Maps/stage3w2.txt");
		} else if (wave == 3) {
			map.LoadMap("Resources/Maps/stage3w3.txt");
		}
	}
	map.SpawnEnemy();
}

void GameStageScene::ObjectUpdate() {

	CameraUpdate();
	particleManager.Update();

	// ステージをクリアしてるならコマ送り
	if (isClearStage) {
		if (frameCount % 3 != 0) {
			return;
		}
	}

	player.Update();


	PlayerLockOn();

	if (playerAttackStopFrame % GMScene::kSecondPerPlayerAttackStopFrame <= 0) {
		bulletManager.Update();

		enemyManager.Update();
		ExprodeEnemy();
		EnemyMoveToPlayer();
		EnemyAttack();

		if (!isChangeWave && !isClearStage) {
			gameTime--;
			if (gameTime <= 0) {
				gameTime = 0;
			}
		}

		if (comboTrigerCooldown > 0) {
			comboTrigerCooldown--;
		}
	}
}

void GameStageScene::ObjectCollision() {

	EnemyCollision();

	// プレイヤーの当たり判定
	if (!isClearStage) {
		if (player.GetDamageCoolDown() <= 0) {
			// 弾
			for (int b = 0; b < BMG::kBulletMax; b++) {
				if (bulletManager.GetBullets()[b].GetIsShot()) {

					if (map.GetIsFromToVisionClear(bulletManager.GetBullets()[b].GetPos(), player.GetPos())) {

						// 爆発の当たり判定
						if (bulletManager.GetBullets()[b].GetTag() == "exprosion") {

							if (IsHitCollisionEllipse(
								bulletManager.GetBullets()[b].GetPos(), player.GetPos(),
								bulletManager.GetBullets()[b].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

								player.Damage();
								player.GetPhysics()->AddForce(player.GetPos() - bulletManager.GetBullets()[b].GetPos(), IMPACT);

								// カメラを揺らす
								mainCamera.shakeRange += {100.0f, 100.0f};

								particleManager.AnimEffect(player.GetPos(), { 256.0f,256.0f }, Random(6.24f, 0.0f), 5, 2, false, playerHitGH);
								particleManager.Update();
								stopObjectUpdateFrame = 10;
								playerAttackStopFrame = 0;
								input->GetControllerManager()->VibrationController(60000, 60000, 10);
								Novice::PlayAudio(playerHitSE, false, seVolume);
								PlayerDeath();
							}
						}

						// 爆発の当たり判定
						if (bulletManager.GetBullets()[b].GetTag() == "enemy") {

							if (IsHitCollisionEllipse(
								bulletManager.GetBullets()[b].GetPos(), player.GetPos(),
								bulletManager.GetBullets()[b].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

								bulletManager.GetBullets()[b].SetIsShot(false);
								bulletManager.GetBullets()[b].SetIsActive(false);

								player.Damage();
								player.GetPhysics()->AddForce(player.GetPos() - bulletManager.GetBullets()[b].GetPos(), IMPACT);

								// カメラを揺らす
								mainCamera.shakeRange += {100.0f, 100.0f};

								stopObjectUpdateFrame = 10;
								playerAttackStopFrame = 0;

								particleManager.AnimEffect(bulletManager.GetBullets()[b].GetPos(), { 256.0f,256.0f }, Random(6.24f, 0.0f), 5, 3, false, playerHitGH);
								particleManager.Update();
								input->GetControllerManager()->VibrationController(60000, 60000, 10);
								Novice::PlayAudio(playerHitSE, false, seVolume);
								PlayerDeath();
							}
						}
					}
				}
			}
			// 敵
			for (int e = 0; e < EMG::kMaxEnemy; e++) {
				if (enemyManager.GetEnemyes()[e].GetIsAlive() && !enemyManager.GetEnemyes()[e].GetIsSpawning()) {

					if (enemyManager.GetEnemyes()[e].GetType() == ENM::Melee) {
						if (enemyManager.GetEnemyes()[e].GetIsAttack()) {

							if (IsHitCollisionEllipse(
								enemyManager.GetEnemyes()[e].GetPos(), player.GetPos(),
								enemyManager.GetEnemyes()[e].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

								player.Damage();
								player.GetPhysics()->AddForce(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos(), IMPACT);

								// カメラを揺らす
								mainCamera.shakeRange += {100.0f, 100.0f};

								stopObjectUpdateFrame = 10;
								playerAttackStopFrame = 0;
								particleManager.AnimEffect(enemyManager.GetEnemyes()[e].GetPos(), { 256.0f,256.0f }, Random(6.24f, 0.0f), 5, 3, false, playerHitGH);
								particleManager.Update();
								input->GetControllerManager()->VibrationController(60000, 60000, 10);
								Novice::PlayAudio(playerHitSE, false, seVolume);
								PlayerDeath();
							}
						}
					}

					CollisionEllipse(
						player.GetPosPtr(), enemyManager.GetEnemyes()[e].GetPosPtr(),
						player.GetPhysics()->GetVelocity(), enemyManager.GetEnemyes()[e].GetPhysics()->GetVelocity(),
						Length(player.GetPhysics()->GetVelocity()), Length(enemyManager.GetEnemyes()[e].GetPhysics()->GetVelocity()),
						player.GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f, true, false, false);
				}
			}
		}
	}
	map.PlayerMapCollision();

	// 弾の当たり判定
	map.BulletMapCollision();
}

void GameStageScene::EnemyCollision() {
	// 敵の当たり判定
	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (enemyManager.GetEnemyes()[e].GetIsAlive() && enemyManager.GetEnemyes()[e].GetIsActive() && !enemyManager.GetEnemyes()[e].GetIsSpawning()) {
			// プレイヤー
			if (player.GetIsAttack()) {
				if (IsHitCollisionEllipse(
					player.GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
					player.GetAttackRadius(), enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

					if (!enemyManager.GetEnemyes()[e].GetIsHitAttack() && player.GetCanAttack()) {

						enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
						enemyManager.GetEnemyes()[e].SetHitAttackDir(
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f));
						player.CountDownRemainAttackChance();

						particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f), 20.00f, 5, 120, 10, enemyBloodGH);

						// カメラを揺らす
						mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f) * 20.0f;

						enemyManager.GetEnemyes()[e].Stun();

						if (playerAttackStopFrame > 0) {
							playerAttackHitCount++;
						}

						// SE
						Novice::PlayAudio(playerAttackOP, false, seVolume);

						//if (enemyManager.GetRemainEnemies() > 1) {
						//	playerAttackStopFrame = GMScene::maxPlayerAttackStopFrame / (playerAttackHitCount + 1);

						//	if (!isSlowFrame) {
						//		isSlowFrame = true;
						//	}
						//}

						if (exprosionComboCount > 0) {
							comboRemainFrame = GMScene::maxComboRemainFrame;
						}

						// 爆発
						particleManager.AnimEffect(enemyManager.GetEnemyes()[e].GetPos(), { 256.0f,256.0f }, Random(6.24f, 0.0f), 3, 3, false, hitEffectGH);

					} else {

						enemyManager.GetEnemyes()[e].GetPhysics()->AddForce(player.GetPhysics()->GetVelocity() * 20.0f, IMPACT);
						player.GetPhysics()->InversVelocity();

					}
					player.SetIsAttack(false);
					// カメラを揺らす
					mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f) * 20.0f;

					input->GetControllerManager()->VibrationController(65000, 65000, 5);

					particleManager.SlashEffect(
						enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
						Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()), 10.0f, 5, 30, 5, 0);

					/*particleManager.SlashEffect(
						player.GetPos(), { 32.0f,32.0f },
						{ 1.0f,1.0f }, 10.0f, 5, 120, 5, enemyBloodGH);*/

				}
			}

			// 弾
			for (int b = 0; b < BMG::kBulletMax; b++) {
				if (bulletManager.GetBullets()[b].GetIsShot()) {
					// 刀の当たり判定
					if (bulletManager.GetBullets()[b].GetTag() == "player") {

						if (IsHitCollisionEllipse(
							bulletManager.GetBullets()[b].GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
							bulletManager.GetBullets()[b].GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

							bulletManager.GetBullets()[b].SetIsShot(false);

							enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
							enemyManager.GetEnemyes()[e].SetHitAttackDir(
								Normalize(bulletManager.GetBullets()[b].GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f));

							// 爆発
							particleManager.AnimEffect(enemyManager.GetEnemyes()[e].GetPos(), { 256.0f,256.0f }, Random(6.24f, 0.0f), 3, 3, false, hitEffectGH);
						}
					}

					// 爆発の当たり判定
					if (bulletManager.GetBullets()[b].GetTag() == "exprosion") {

						if (IsHitCollisionEllipse(
							bulletManager.GetBullets()[b].GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
							bulletManager.GetBullets()[b].GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x)) {

							enemyManager.GetEnemyes()[e].SetHitAttackDir(
								Normalize(bulletManager.GetBullets()[b].GetPos() - enemyManager.GetEnemyes()[e].GetPos()));

							if (!enemyManager.GetEnemyes()[e].GetIsHitAttack()) {
								/*bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
									enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
								bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
									-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
								enemyManager.GetEnemyes()[e].SetIsHitAttack(true);*/

								bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), { GMScene::exprodeRange,GMScene::exprodeRange },
									enemyManager.GetEnemyes()[e].GetHitDir(), 0.0f, 5, "exprosion", 0);
								enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
							}

							mainCamera.shakeRange += { 10.0f, 10.0f };
							stopObjectUpdateFrame = exprosionHitStopFrame;
							//mainCamera.SetPos(enemyManager.GetEnemyes()[e].GetPos());
							mainCamera.panRange = -0.13f;

							// 爆発
							particleManager.AnimEffect(enemyManager.GetEnemyes()[e].GetPos(), { 340.0f,340.0f }, Random(6.24f, 0.0f), 7, 3, false, exprosionGH);

							// コンボ加算
							if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
								// SE
								Novice::PlayAudio(comboOP[Clamp(exprosionComboCount, 0, 4)], false, seVolume);

								if (comboTrigerCooldown <= 0) {
									exprosionComboCount++;
									comboRemainFrame = GMScene::maxComboRemainFrame;
									//comboTrigerCooldown = GMScene::kMaxComboTrigerCooldown;
								}
							}
							enemyManager.GetEnemyes()[e].SetIsAlive(false);

							int tempScore = 100 * (exprosionComboCount + 1);
							score += tempScore;
							scoreUIManager.SpawnScore(enemyManager.GetEnemyes()[e].GetPos(), tempScore);

							// ラストヒット
							if (wave >= 3 && enemyManager.GetRemainEnemies() <= 0) {
								if (lastHitEnemyNum == -1) {
									lastHitEnemyNum = e;
									stopObjectUpdateFrame = 30;
									flashScreenFrame = 30;
									return;
								}
							}

							if (playerAttackStopFrame > 0) {
								playerAttackStopFrame = GMScene::maxPlayerAttackStopFrame / (playerAttackHitCount + 1);
							}

							input->GetControllerManager()->VibrationController(65000, 65000, 10);
							return;
						}
					}
				}
			}
		}
	}
	map.EnemyMapCollision();
}

void GameStageScene::Attack() {
	// プレイヤーの攻撃
	if (player.GetIsAttack()) {
		player.SetIsAttack(false);
		bulletManager.ShotBullet(player.GetAttackPos(), { 64.0f,64.0f }, { 0.0f,0.0f }, 0.0f, 10, "player", 0);
	}
}

void GameStageScene::PlayerLockOn() {
	if (Length(enemyManager.NearEnemy(player.GetPos()) - player.GetPos()) <= 256.0f &&
		map.GetIsFromToVisionClear(player.GetPos(), enemyManager.NearEnemy(player.GetPos()))) {

		player.SetIsLockOn(true);
		player.SetTargetPos(enemyManager.NearEnemy(player.GetPos()));
	} else {
		player.SetIsLockOn(false);
	}
}

void GameStageScene::ExprodeEnemy() {

	if (isSlowFrame) {
		if (playerAttackStopFrame <= 0) {

			for (int e = 0; e < EMG::kMaxEnemy; e++) {
				if (enemyManager.GetEnemyes()[e].GetIsAlive() && enemyManager.GetEnemyes()[e].GetIsHitAttack()) {
					enemyManager.GetEnemyes()[e].SetStunFrame(1);
					enemyManager.GetEnemyes()[e].UpdateExprodeCircle(200);
				}
			}
			isSlowFrame = false;
			stopObjectUpdateFrame = 15;
			/*score *= static_cast<int>(slowFrameScoreRatio);
			slowFrameScoreRatio = 1.0f;*/

			return;
		}
	}

	for (int e = 0; e < EMG::kMaxEnemy; e++) {

		if (enemyManager.GetEnemyes()[e].GetIsReqestExprosion()) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive()) {

				enemyManager.GetEnemyes()[e].SetIsAlive(false);
				enemyManager.GetEnemyes()[e].SetIsExprosion(false);

				bulletManager.ShotBullet(
					enemyManager.GetEnemyes()[e].GetPos(), { GMScene::exprodeRange,GMScene::exprodeRange },
					enemyManager.GetEnemyes()[e].GetHitDir(), 0.0f, 5, "exprosion", 0);

				/*bulletManager.ShotBullet(
					enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
					enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
				bulletManager.ShotBullet(
					enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
					-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);*/

					// 爆発
				particleManager.AnimEffect(enemyManager.GetEnemyes()[e].GetPos(), { 340.0f,340.0f }, Random(6.24f, 0.0f), 7, 3, false, exprosionGH);

				int tempScore = 100 * (exprosionComboCount + 1);
				score += tempScore;
				scoreUIManager.SpawnScore(enemyManager.GetEnemyes()[e].GetPos(), tempScore);

				// SE
				Novice::PlayAudio(comboOP[Clamp(exprosionComboCount, 0, 4)], false, seVolume);

				// ラストヒット
				if (wave >= 3 && enemyManager.GetRemainEnemies() <= 0) {
					if (lastHitEnemyNum == -1) {
						lastHitEnemyNum = e;
						stopObjectUpdateFrame = 30;
						flashScreenFrame = 30;
						return;
					}
				}
				input->GetControllerManager()->VibrationController(60000, 60000, 5);
				mainCamera.shakeRange += {10.0f, 10.0f};
			}
		}
	}

	if (player.GetIsSheathe()) {
		player.SetIsSheathe(false);
		player.SetRemainAttackChance(PLR::kMaxAttackChance);
	}

	// コンボを0に戻す
	if (comboRemainFrame > 0) {
		comboRemainFrame--;
	} else {
		exprosionComboCount = 0;
	}
}

void GameStageScene::EnemyMoveToPlayer() {
	if (frameCount % (60 + 1) == 0) {

		for (int e = 0; e < EMG::kMaxEnemy; e++) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
				enemyManager.GetEnemyes()[e].SetPlayerRoute(map.GetMapStoG(enemyManager.GetEnemyes()[e].GetPos(), player.GetPos()));
			}
		}
	}
}

void GameStageScene::EnemyAttack() {
	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (enemyManager.GetEnemyes()[e].GetIsAlive()) {

			if (map.GetIsFromToVisionClear(enemyManager.GetEnemyes()[e].GetPos(), player.GetPos())) {

				enemyManager.GetEnemyes()[e].SetIsSeePlayer(true);
				Render::DrawLine(enemyManager.GetEnemyes()[e].GetPos(), player.GetPos(), mainCamera, WHITE);

			} else {
				enemyManager.GetEnemyes()[e].SetIsSeePlayer(false);
			}

			if (enemyManager.GetEnemyes()[e].GetType() == ENM::Shot) {
				if (enemyManager.GetEnemyes()[e].GetIsShot()) {

					bulletManager.ShotBullet(
						enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
						enemyManager.GetEnemyes()[e].GetAngleDir(), 10.0f, 180, "enemy", enemyBulletGH);
					enemyManager.GetEnemyes()[e].SetIsShot(false);
				}
			}
		}
	}
}

void GameStageScene::WaveUiDraw() {
	if (isChangeWave) {
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000DF, kFillModeSolid);
		targetScoreNum.Draw(&uiCamera, enemyRemainNumGH);
		//waveNumber.Draw(&uiCamera, enemyRemainNumGH);
		//Render::DrawNum({ 0.0f,0.0f }, { 128.0f,128.0f }, { 1.0f,1.0f }, 0.0f, uiCamera, 0, enemyRemainNumGH, WHITE);

		/*Render::DrawSprite(balancePoleTransform, uiCamera, WHITE, balancePoleGH);

		for (int i = 0; i < EMG::kMaxEnemy + 1; i++) {

			if (baranceObjects[i].GetIsActive()) {
				baranceObjects[i].Draw();
			}
		}
		Render::DrawSprite(balanceBasketTransform[0], uiCamera, WHITE, balanceBasketGH);
		Render::DrawSprite(balanceBasketTransform[1], uiCamera, WHITE, balanceBasketGH);*/
		//Render::DrawSprite(clossTransform, uiCamera, WHITE, clossGH);
		Render::DrawSprite(waveStringTransform, uiCamera, WHITE, waveStringGH);
		//Render::DrawSprite(enemyTargetTransform, uiCamera, WHITE, targetEnemyUiGH);
		//Render::DrawSprite(missionTransform, uiCamera, WHITE, missionGH);
		//Render::DrawNum({ 0.0f,waveStringTransform.pos.y - 128.0f }, { 128.0f,128.0f }, { 1.0f,1.0f }, 0.0f, uiCamera, wave, enemyRemainNumGH, WHITE);
	}
}

void GameStageScene::BalanceUpdate() {
	if (enemyManager.GetRemainEnemies() <= 0) {
		if (!isChangeWave) {

			// ステージクリア後の演出時間
			if (isClearStage) {

				if (clearStageTimeBuffer > 0) {
					clearStageTimeBuffer--;
					return;
				}

			} else {

				isClearStage = true;
				clearStageTimeBuffer = GMScene::maxClearStageTimeBuffer;
				return;
			}

			// ステージ切り替え用オブジェクト初期化
			isChangeWave = true;
			wave++;
			balancePoleTransform.pos = { 0.0f,100.0f };
			balancePoleTransform.scale = { 0.0f,0.0f };
			balanceBasketTransform[0].scale = { 0.0f,0.0f };
			balanceBasketTransform[1].scale = { 0.0f,0.0f };
			balanceBasketSwingWidth = 1.0f;
			//balancePoleTransform.angle = 2.0f;
			frameCount = 0;

			// ステージ切り替え
			if (wave == 1) {
				map.LoadMap("Resources/Maps/stage1w1.txt");
			} else if (wave == 2) {
				map.LoadMap("Resources/Maps/stage1w2.txt");
			} else if (wave == 3) {
				map.LoadMap("Resources/Maps/stage1w3.txt");
			}

			// 天秤に乗るオブジェクト初期化
			for (int i = 0; i < map.GetEnemyNum(); i++) {
				baranceObjects[i % EMG::kMaxEnemy].Init();
				baranceObjects[i % EMG::kMaxEnemy].SetCamera(&uiCamera);
			}
			baranceObjects[0].SetPos({ -220.0f,400.0f });
			baranceObjects[0].SetSize({ 64.0f,64.0f });
			baranceObjects[0].SetIsActive(true);
			baranceObjects[0].SetGraphHandle(playerWeightGH);
			for (int i = 1; i < map.GetEnemyNum() + 1; i++) {
				baranceObjects[i].SetIsActive(true);
				baranceObjects[i].SetPos({ 220.0f + Random(80.0f,-80.0f),400.0f + Random(300.0f,0.0f) });
				baranceObjects[i].SetGraphHandle(enemyWeightGH);
			}
			balanceAngle = 0.0f;
			rightWeight = 0.0f;
			leftWeight = 0.0f;
		}
	}
#pragma region Balance
	// 天秤のかご傾き処理
	Eas::SimpleEaseIn(&balanceAngle, rightWeight - leftWeight * 0.25f, 0.01f);
	balanceAngle = Clamp(balanceAngle, -0.3f, 0.3f);
	balanceBasketTransform[0] = {
		{220.0f,0.0f},
		{256.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketTransform[1] = {
		{-220.0f,0.0f},
		{256.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketTransform[0].pos = balanceBasketTransform[0].pos * MakeRotateMatrix(balanceAngle);
	balanceBasketTransform[1].pos = balanceBasketTransform[1].pos * MakeRotateMatrix(balanceAngle);
	balanceBasketTransform[0].pos.y -= 64.0f;
	balanceBasketTransform[1].pos.y -= 64.0f;

	// 天秤が上下にちょっと揺れる
	balancePoleTransform.pos.y += sinf(static_cast<float>(frameCount) * 0.1f) * 0.5f;
	balanceBasketTransform[0].pos.y += cosf(static_cast<float>(frameCount) * 0.1f) * 0.5f;
	balanceBasketTransform[1].pos.y += cosf(static_cast<float>(frameCount) * 0.1f) * 0.5f;
	waveStringTransform.pos.y += sinf(static_cast<float>(frameCount) * 0.1f) * 0.5f;

	// 天秤の柱召喚
	Eas::SimpleEaseIn(&balancePoleTransform.pos.y, -64.0f, 0.3f);
	Eas::SimpleEaseIn(&balancePoleTransform.scale.x, 1.0f, 0.2f);
	Eas::SimpleEaseIn(&balancePoleTransform.scale.y, 1.0f, 0.2f);

	// 天秤のかご召喚
	if (balancePoleTransform.scale.x >= 1.0f) {
		Eas::SimpleEaseIn(&balanceBasketTransform[0].scale.x, 1.0f, 0.2f);
		Eas::SimpleEaseIn(&balanceBasketTransform[0].scale.y, 1.0f, 0.2f);
		Eas::SimpleEaseIn(&balanceBasketTransform[1].scale.x, 1.0f, 0.2f);
		Eas::SimpleEaseIn(&balanceBasketTransform[1].scale.y, 1.0f, 0.2f);

		balanceBasketTransform[0].angle = sinf(static_cast<float>(frameCount) * 0.2f) * balanceBasketSwingWidth;
		balanceBasketTransform[1].angle = cosf(static_cast<float>(frameCount) * 0.2f) * balanceBasketSwingWidth;
		balanceBasketSwingWidth *= 0.92f;
	}

	// プレイヤー召喚
	if (balanceBasketTransform[0].scale.x >= 1.0f) {
		if (baranceObjects[0].GetIsActive()) {
			baranceObjects[0].Update();
		}

		if (IsHitRectangle(
			baranceObjects[0].GetPos(), baranceObjects[0].GetSize(),
			{ balanceBasketTransform[1].pos.x,balanceBasketTransform[1].pos.y - balanceBasketTransform[1].size.y * 0.5f },
			{ balanceBasketTransform[1].size.x,balanceBasketTransform[1].size.y * 0.3f })) {

			baranceObjects[0].SetFalling(false);
			baranceObjects[0].GetPhysics()->SetVelocity(ZeroVector2);
			baranceObjects[0].GetPhysics()->SetAcceleration(ZeroVector2);
			baranceObjects[0].ParentObject(&balanceBasketTransform[1]);
			rightWeight = 1.2f;
		}
	}

	if (!baranceObjects[0].GetFalling()) {
		for (int i = 1; i < EMG::kMaxEnemy + 1; i++) {

			if (baranceObjects[i].GetIsActive()) {
				baranceObjects[i].Update();
			}

			if (IsHitRectangle(
				baranceObjects[i].GetPos(), baranceObjects[i].GetSize(),
				{ balanceBasketTransform[0].pos.x,balanceBasketTransform[0].pos.y - balanceBasketTransform[0].size.y * 0.5f },
				{ balanceBasketTransform[0].size.x,balanceBasketTransform[0].size.y * 0.3f })) {

				baranceObjects[i].GetPhysics()->SetVelocity(ZeroVector2);
				baranceObjects[i].GetPhysics()->SetAcceleration(ZeroVector2);
				baranceObjects[i].ParentObject(&balanceBasketTransform[0]);

				if (baranceObjects[i].GetFalling()) {
					leftWeight += 0.1f;
					baranceObjects[i].SetFalling(false);
				}
			}

			if (i < EMG::kMaxEnemy + 1) {
				if (IsHitRectangle(
					baranceObjects[i].GetPos(), baranceObjects[i].GetSize(),
					baranceObjects[i + 1].GetPos(), baranceObjects[i + 1].GetSize())) {
					if (!baranceObjects[i + 1].GetFalling()) {

						baranceObjects[i].GetPhysics()->SetVelocity(ZeroVector2);
						baranceObjects[i].GetPhysics()->SetAcceleration(ZeroVector2);
						baranceObjects[i].ParentObject(&balanceBasketTransform[0]);

						if (baranceObjects[i].GetFalling()) {
							leftWeight += 3.0f;
							baranceObjects[i].SetFalling(false);
						}
					}
				}
			}
		}
	}
#pragma endregion
}

void GameStageScene::PlayerDeath() {
	if (player.GetHp() <= 0) {
		stopObjectUpdateFrame = 60;
		player.GetPhysics()->SetResistance(1.0f);
		player.GetPhysics()->SetVelocity({ 10.0f,10.0f });

		flashScreenFrame = 30;
		mainCamera.angleShakeRange = 10.0f;
		mainCamera.panRange -= 0.5f;

		mainCamera.shakeRange += {100.0f, 100.0f};
	}
}

void GameStageScene::ControlInfoUpdate() {
	if (shakeContorolInfoExprosion > 0.0f) {
		shakeContorolInfoExprosion--;
	}

	if (isChangeWave) {

		if (isStartingGame) {

			contorolInfoTransform[2].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 1.0f) * 0.1f;
			contorolInfoTransform[2].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 1.0f) * 0.1f;
		} else {
			contorolInfoTransform[2].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;
			contorolInfoTransform[2].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;
		}

	} else {

		if (Length(input->GetControlDir()) > 0.0f) {
			Eas::SimpleEaseIn(&contorolInfoTransform[0].scale.x, 0.9f, 0.3f);
			Eas::SimpleEaseIn(&contorolInfoTransform[0].scale.y, 0.8f, 0.3f);
		} else {
			contorolInfoTransform[0].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;
			contorolInfoTransform[0].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;
		}

		if (player.GetIsDash()) {
			Eas::SimpleEaseIn(&contorolInfoTransform[1].scale.x, 0.9f, 0.3f);
			Eas::SimpleEaseIn(&contorolInfoTransform[1].scale.y, 0.8f, 0.3f);
		} else {
			contorolInfoTransform[1].scale.x = 1.0f + sinf(static_cast<float>(frameCount + 10) * 0.1f) * 0.1f;
			contorolInfoTransform[1].scale.y = 1.0f + sinf(static_cast<float>(frameCount + 10) * 0.1f) * 0.1f;
		}

		/*if (enemyManager.GetIsThereHitEnemy() || player.GetRemainAttackChance() <= 0) {
			contorolInfoTransform[2].scale.x = 1.0f + sinf(static_cast<float>(frameCount + 20) * 0.3f) * 0.1f;
			contorolInfoTransform[2].scale.y = 1.0f + sinf(static_cast<float>(frameCount + 20) * 0.3f) * 0.1f;

		} else {
			Eas::SimpleEaseIn(&contorolInfoTransform[2].scale.x, 0.9f, 0.3f);
			Eas::SimpleEaseIn(&contorolInfoTransform[2].scale.y, 0.8f, 0.3f);

			if (input->GetTriger(DIK_E) || input->GetControl(ATTACK, Triger)) {
				shakeContorolInfoExprosion = 30.0f;
			}

			contorolInfoTransform[2].pos = { 320.0f + shakeContorolInfoExprosion* sinf(static_cast<float>(frameCount)) ,-320.0f};

		}*/
	}
}

void GameStageScene::ControlInfoDraw() {

	if (isChangeWave) {

		if (isStartingGame) {
			
			if (Novice::GetNumberOfJoysticks() > 0) {

				if (startGameBufferFrame > 30) {
					if (frameCount % 2) {
						Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, rcContorolInfoGH[3]);
					} else {
						Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0xFFFFFF23, rcContorolInfoGH[3]);
					}
				}
			} else {

				if (startGameBufferFrame > 30) {
					if (frameCount % 2) {
						Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, contorolInfoGH[3]);
					} else {
						Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0xFFFFFF23, contorolInfoGH[3]);
					}
				}
			}

			
			
		} else {
			if (Novice::GetNumberOfJoysticks() > 0) {
				Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, rcContorolInfoGH[3]);
			} else {
				Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, contorolInfoGH[3]);
			}
		}

		
	}
	//else {

	//	if (Novice::GetNumberOfJoysticks() > 0) {
	//		if (Length(input->GetControlDir()) > 0.0f) {
	//			Render::DrawSprite(contorolInfoTransform[0], uiCamera, 0x232323FF, rcContorolInfoGH[0]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[0], uiCamera, WHITE, rcContorolInfoGH[0]);
	//		}

	//		if (player.GetIsDash()) {
	//			Render::DrawSprite(contorolInfoTransform[1], uiCamera, 0x232323FF, rcContorolInfoGH[1]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[1], uiCamera, WHITE, rcContorolInfoGH[1]);
	//		}

	//		/*if (enemyManager.GetIsThereHitEnemy() || player.GetRemainAttackChance() <= 0) {
	//			Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0xD65A31FF, rcContorolInfoGH[2]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0x232323FF, rcContorolInfoGH[2]);
	//		}*/
	//	} else {
	//		if (Length(input->GetControlDir()) > 0.0f) {
	//			Render::DrawSprite(contorolInfoTransform[0], uiCamera, 0x232323FF, contorolInfoGH[0]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[0], uiCamera, WHITE, contorolInfoGH[0]);
	//		}

	//		if (player.GetIsDash()) {
	//			Render::DrawSprite(contorolInfoTransform[1], uiCamera, 0x232323FF, rcContorolInfoGH[1]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[1], uiCamera, WHITE, contorolInfoGH[1]);
	//		}

	//		/*if (enemyManager.GetIsThereHitEnemy() || player.GetRemainAttackChance() <= 0) {
	//			Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0xD65A31FF, rcContorolInfoGH[2]);
	//		} else {
	//			Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0x232323FF, contorolInfoGH[2]);
	//		}*/
	//	}


	//}
}

void GameStageScene::CameraUpdate() {
	Vector2* cameraPos = mainCamera.GetPosPtr();
	if (isClearStage) {
		if (player.GetIsAlive()) {
			Eas::SimpleEaseIn(&mainCamera.GetPosPtr()->x, enemyManager.GetEnemyes()[lastHitEnemyNum].GetPos().x, 0.1f);
			Eas::SimpleEaseIn(&mainCamera.GetPosPtr()->y, enemyManager.GetEnemyes()[lastHitEnemyNum].GetPos().y, 0.1f);

		}

		mainCamera.shakeRange = { 10.0f,10.0f };
		//mainCamera.panRange = -Eas::EaseInOutQuart(static_cast<float>(clearStageTimeBuffer) / static_cast<float>(GMScene::maxClearStageTimeBuffer), 0.1f, 1.0f);

	} else {
		*cameraPos = player.GetPos();
	}

	//mainCamera.CameraMoveLimit({ 640.0f,370.0f }, { 1408.0f,1678.0f });
}
