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
	map.LoadMap("Resources/Maps/stage1w1.txt");

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
	gameScore.SetSize({ 128.0f,128.0f });
	gameScore.SetPos({ 580.0f,310.0f });
	gameScore.SetLocalScale({ 0.5f,0.5f });

	scoreTitle = { 0.0f };
	scoreTitle.pos = { 128.0f,310.0f };
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
	timeNum.Init();
	timeNum.SetSize({ 128.0f,128.0f });
	timeNum.SetPos({ 0.0f,0.0f });
	timeNum.SetLocalScale({ 3.0f,3.0f });
	timeNum.SetColor(0xEEEEEE13);

	enemyBloodGH = Novice::LoadTexture("./Resources/Images/ScoreTitle.png");

	exprosionGH[0] = Novice::LoadTexture("./Resources/Images/Explosion1.png");
	exprosionGH[1] = Novice::LoadTexture("./Resources/Images/Explosion2.png");
	exprosionGH[2] = Novice::LoadTexture("./Resources/Images/Explosion3.png");
	exprosionGH[3] = Novice::LoadTexture("./Resources/Images/Explosion4.png");
	exprosionGH[4] = Novice::LoadTexture("./Resources/Images/Explosion5.png");
	exprosionGH[5] = Novice::LoadTexture("./Resources/Images/Explosion6.png");
	exprosionGH[6] = Novice::LoadTexture("./Resources/Images/Explosion7.png");

	comboTrigerCooldown = 0;
}

void GameStageScene::Update() {

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
	
	if (gameTime <= 0) {

		sceneObj->isNotDeathClear = player.GetIsAlive();

		isTransition = true;
		nextScene = new ResultScene();
		return;
	}
	timeNum.Update();
	timeNum.SetTargetNum(gameTime / 60);

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
		scoreUIManager.Draw();
		playerHpUI.Draw();
		WaveUiDraw();
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

	if (flashScreenFrame > 0) {
		if (flashScreenFrame % 6 <= 3) {
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFFFFFF23, kFillModeSolid);
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

	if (enemyManager.GetRemainEnemies() <= 0 || gameTime % 1000 == 999) {
		wave++;
		if (wave <= 6) {
			LoadWave();
		} else {

			sceneObj->isNotDeathClear = player.GetIsAlive();
			isTransition = true;
			nextScene = new ResultScene();

			for (int i = 0; i < wave; i++) {
				enemyManager.SpawnEnemy({ Random(64.0f,900.0f),Random(64.0f,900.0f) }, ENM::Melee);
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
				}

				if (!player.GetIsAlive()) {
					isNotDeath = false;
					sceneObj->isNotDeathClear = isNotDeath;
					isTransition = true;
					nextScene = new ResultScene();
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
			if (wave == 1) {
				map.LoadMap("Resources/Maps/stage1w1.txt");
			} else if (wave == 2) {
				map.LoadMap("Resources/Maps/stage1w2.txt");
			} else if (wave == 3) {
				map.LoadMap("Resources/Maps/stage1w3.txt");
			}

			targetScoreNum.Init();
			targetScoreNum.SetTargetNum(1000000);

			comboRemainFrame = 0;
			exprosionComboCount = 0;
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
			targetScoreNum.SetPos({ 24.0f * static_cast<float>(targetScoreNum.GetDigit()),targetScoreNum.GetPosPtr()->y });
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
			//LoadWave();
			isChangeWave = false;
			isClearStage = false;
			lastHitEnemyNum = -1;

			contorolTutorialUI.SetIsActive(true);
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
	if (wave == 1) {
		map.LoadMap("Resources/Maps/stage1w1.txt");
	} else if (wave == 2) {
		map.LoadMap("Resources/Maps/stage1w2.txt");
	} else if (wave == 3) {
		map.LoadMap("Resources/Maps/stage1w3.txt");
	} else {
		// stageClear
		/*sceneObj->isNotDeathClear = isNotDeath;
		nextScene = new ResultScene();
		isTransition = true;*/
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

		if (!isChangeWave) {
			gameTime--;
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
								mainCamera.shakeRange += Normalize(player.GetPos() - bulletManager.GetBullets()[b].GetPos()) * 100.0f;

								playerAttackStopFrame = 0;

								PlayerDeath();
							}
						}

						// 爆発の当たり判定
						if (bulletManager.GetBullets()[b].GetTag() == "enemy") {

							if (IsHitCollisionEllipse(
								bulletManager.GetBullets()[b].GetPos(), player.GetPos(),
								bulletManager.GetBullets()[b].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

								player.Damage();
								player.GetPhysics()->AddForce(player.GetPos() - bulletManager.GetBullets()[b].GetPos(), IMPACT);

								// カメラを揺らす
								mainCamera.shakeRange += Normalize(player.GetPos() - bulletManager.GetBullets()[b].GetPos()) * 100.0f;

								playerAttackStopFrame = 0;

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
								mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * 100.0f;

								playerAttackStopFrame = 0;

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
	//map.BulletMapCollision();
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

						/*particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f), 0.00f, 5, 120, 10, enemyBloodGH);*/

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

						particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()), 10.0f, 5, 30, 5, 0);
					}
					player.SetIsAttack(false);
					// カメラを揺らす
					mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f) * 20.0f;

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
							bulletManager.GetBullets()[b].GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

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
									comboTrigerCooldown = GMScene::kMaxComboTrigerCooldown;
								}
							}
							enemyManager.GetEnemyes()[e].SetIsAlive(false);

							int tempScore = 100 * (exprosionComboCount + 1);
							score += tempScore;
							scoreUIManager.SpawnScore(enemyManager.GetEnemyes()[e].GetPos(), tempScore);

							// ラストヒット
							/*if (enemyManager.GetRemainEnemies() <= 0) {
								if (lastHitEnemyNum == -1) {
									lastHitEnemyNum = e;
									stopObjectUpdateFrame = 30;
									flashScreenFrame = 30;
									return;
								}
							}*/

							if (playerAttackStopFrame > 0) {
								playerAttackStopFrame = GMScene::maxPlayerAttackStopFrame / (playerAttackHitCount + 1);
							}

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
				/*if (enemyManager.GetRemainEnemies() <= 0) {
					if (lastHitEnemyNum == -1) {
						lastHitEnemyNum = e;
						stopObjectUpdateFrame = 30;
						flashScreenFrame = 30;
						return;
					}
				}*/

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
						enemyManager.GetEnemyes()[e].GetAngleDir(), 10.0f, 180, "enemy", 0);
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
		player.GetPhysics()->AddForce({Random(10.0f,-10.0f),Random(10.0f,-10.0f) }, IMPACT);

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

		contorolInfoTransform[2].scale.x = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;
		contorolInfoTransform[2].scale.y = 1.0f + sinf(static_cast<float>(frameCount) * 0.1f) * 0.1f;

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

		if (Novice::GetNumberOfJoysticks() > 0) {
			Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, rcContorolInfoGH[3]);
		} else {
			Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, contorolInfoGH[3]);
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

		mainCamera.shakeRange = {10.0f,10.0f };
		//mainCamera.panRange = -Eas::EaseInOutQuart(static_cast<float>(clearStageTimeBuffer) / static_cast<float>(GMScene::maxClearStageTimeBuffer), 0.1f, 1.0f);

	} else {
		*cameraPos = player.GetPos();
	}

	//mainCamera.CameraMoveLimit({ 640.0f,370.0f }, { 1408.0f,1678.0f });
}
