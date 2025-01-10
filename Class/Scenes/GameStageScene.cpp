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

	stopObjectUpdateFrame = 0;
	exprosionHitStopFrame = 6;

	player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);
	enemyManager.SetPlayerPos(player.GetPosPtr());

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
		{180.0f,-64.0f},
		{256.0f,256.0f},
		{1.0f,1.0f},
		0.0f
	};
	balanceBasketTransform[1] = {
		{-180.0f,-64.0f},
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

	contorolInfoTransform[0] = {
		{-320.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoTransform[1] = {
		{0.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoTransform[2] = {
		{320.0f,-320.0f},
		{256.0f,32.0f},
		{1.0f,1.0f},
		0.0f
	};
	contorolInfoGH[0] = Novice::LoadTexture("./Resources/Images/tutorial1.png");
	contorolInfoGH[1] = Novice::LoadTexture("./Resources/Images/tutorial2.png");
	contorolInfoGH[2] = Novice::LoadTexture("./Resources/Images/tutorial3.png");
}

void GameStageScene::Update() {

	mainCamera.Update();
	frameCount++;

	WaveManager();

	if (!isChangeWave) {
		if (stopObjectUpdateFrame <= 0) {
			ObjectUpdate();
			ObjectCollision();
		} else {
			stopObjectUpdateFrame--;
		}
	}
	ImGuiUpdate();
}

void GameStageScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222831FF, kFillModeSolid);

	map.Draw();
	particleManager.Draw();
	bulletManager.Draw();
	enemyManager.Draw();
	player.Draw();
	WaveUiDraw();
	ControlInfoDraw();
}

void GameStageScene::ImGuiUpdate() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("GameStage = %d Wave = %d", gameStage, wave);
	ImGui::InputFloat("x", &testPopEnemyPos.x);
	ImGui::InputFloat("y", &testPopEnemyPos.y);
	ImGui::SliderFloat("balanceAngle", &balanceAngle, -3.14f, 3.14f);
	if (ImGui::Button("PopEnemy")) {
		enemyManager.SpawnEnemy(testPopEnemyPos, ENM::None);
	}

	if (ImGui::Button("CreateEnemyRoute")) {
		for (int e = 0; e < EMG::kMaxEnemy; e++) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
				enemyManager.GetEnemyes()[e].SetPlayerRoute(map.GetMapStoG(enemyManager.GetEnemyes()[e].GetPos(), player.GetPos()));
			}
		}
	}

	ImGui::End();

#endif // _DEBUG
}

IScene* GameStageScene::GetNextScene() {
	return nextScene;
}

void GameStageScene::WaveManager() {

	if (enemyManager.GetRemainEnemies() <= 0) {
		if (!isChangeWave) {

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

	if (isChangeWave) {

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

		// ウェーブ管理処理演出終了
		if (wave >= 4 || (input->GetControl(ENTER, Triger) && frameCount >= 30)) {
			LoadWave();
			isChangeWave = false;
		}
	}
}

void GameStageScene::LoadWave() {
	player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);
	enemyManager.SetPlayerPos(player.GetPosPtr());
	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	// ステージ切り替え
	if (wave == 1) {
		map.LoadMap("Resources/Maps/stage1w1.txt");
	} else if (wave == 2) {
		map.LoadMap("Resources/Maps/stage1w2.txt");
	} else if (wave == 3) {
		map.LoadMap("Resources/Maps/stage1w3.txt");
	} else {
		// stageClear
		nextScene = new ResultScene();
		isTransition = true;
	}
	map.SpawnEnemy();
}

void GameStageScene::ObjectUpdate() {
	player.Update();
	player.UpdateImGui();
	PlayerLockOn();

	bulletManager.Update();

	enemyManager.Update();
	ExprodeEnemy();
	EnemyMoveToPlayer();
	EnemyAttack();

	CameraUpdate();

	particleManager.Update();
}

void GameStageScene::ObjectCollision() {

	// 敵の当たり判定
	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
			// プレイヤー
			if (player.GetIsAttack()) {
				if (IsHitCollisionEllipse(
					player.GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
					player.GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

					if (!enemyManager.GetEnemyes()[e].GetIsHitAttack() && player.GetCanAttack()) {
						enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
						enemyManager.GetEnemyes()[e].SetHitAttackDir(
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f));
						player.CountDownRemainAttackChance();

						particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f), 10.0f, 5, 30, 5, 0);

						// カメラを揺らす
						mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f) * 100.0f;
					} else {

						enemyManager.GetEnemyes()[e].GetPhysics()->AddForce(player.GetPhysics()->GetVelocity() * 20.0f, IMPACT);
						player.GetPhysics()->InversVelocity();

						particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()), 10.0f, 5, 30, 5, 0);

						// カメラを揺らす
						mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f) * 30.0f;
					}
					player.SetIsAttack(false);
					enemyManager.GetEnemyes()[e].Stun();
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
						}
					}

					// 爆発の当たり判定
					if (bulletManager.GetBullets()[b].GetTag() == "exprosion") {

						if (IsHitCollisionEllipse(
							bulletManager.GetBullets()[b].GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
							bulletManager.GetBullets()[b].GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

							enemyManager.GetEnemyes()[e].SetHitAttackDir(
								Normalize(bulletManager.GetBullets()[b].GetPos() - enemyManager.GetEnemyes()[e].GetPos()));

							enemyManager.GetEnemyes()[e].SetIsAlive(false);

							if (!enemyManager.GetEnemyes()[e].GetIsHitAttack()) {
								bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
									enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
								bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
									-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
								enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
							}

							mainCamera.shakeRange = { 10.0f, 10.0f };
							stopObjectUpdateFrame = exprosionHitStopFrame;
							mainCamera.SetPos(enemyManager.GetEnemyes()[e].GetPos());
							mainCamera.panRange = -0.5f;
						}
					}
				}
			}
		}
	}
	map.EnemyMapCollision();

	// プレイヤーの当たり判定
	if (player.GetDamageCoolDown() <= 0) {
		// 弾
		for (int b = 0; b < BMG::kBulletMax; b++) {
			if (bulletManager.GetBullets()[b].GetIsShot()) {

				// 爆発の当たり判定
				if (bulletManager.GetBullets()[b].GetTag() == "exprosion") {

					if (IsHitCollisionEllipse(
						bulletManager.GetBullets()[b].GetPos(), player.GetPos(),
						bulletManager.GetBullets()[b].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

						player.Damage();
						player.GetPhysics()->AddForce(player.GetPos() - bulletManager.GetBullets()[b].GetPos(), IMPACT);

						// カメラを揺らす
						mainCamera.shakeRange += Normalize(player.GetPos() - bulletManager.GetBullets()[b].GetPos()) * 100.0f;
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
					}
				}
			}
		}
		// 敵
		for (int e = 0; e < EMG::kMaxEnemy; e++) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
				if (enemyManager.GetEnemyes()[e].GetType() == ENM::Melee) {
					if (enemyManager.GetEnemyes()[e].GetIsAttack()) {

						if (IsHitCollisionEllipse(
							enemyManager.GetEnemyes()[e].GetPos(), player.GetPos(),
							enemyManager.GetEnemyes()[e].GetSize().x * 0.5f, player.GetSize().x * 0.5f)) {

							player.Damage();
							player.GetPhysics()->AddForce(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos(), IMPACT);

							// カメラを揺らす
							mainCamera.shakeRange += Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * 100.0f;
						}
					}
				}
			}
		}

		map.PlayerMapCollision();
	}

	// 弾の当たり判定
	map.BulletMapCollision();
}

void GameStageScene::Attack() {
	// プレイヤーの攻撃
	if (player.GetIsAttack()) {
		player.SetIsAttack(false);
		bulletManager.ShotBullet(player.GetAttackPos(), { 64.0f,64.0f }, { 0.0f,0.0f }, 0.0f, 10, "player", 0);
	}
}

void GameStageScene::PlayerLockOn() {
	if (Length(enemyManager.NearEnemy(player.GetPos()) - player.GetPos()) <= 256.0f) {
		player.SetIsLockOn(true);
		player.SetTargetPos(enemyManager.NearEnemy(player.GetPos()));
	} else {
		player.SetIsLockOn(false);
	}
}

void GameStageScene::ExprodeEnemy() {

	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (player.GetIsSheathe()) {
			if (enemyManager.GetEnemyes()[e].GetIsAlive() &&
				enemyManager.GetEnemyes()[e].GetIsHitAttack()) {

				enemyManager.GetEnemyes()[e].SetIsAlive(false);

				bulletManager.ShotBullet(
					enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
					enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
				bulletManager.ShotBullet(
					enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
					-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", slashGH);
			}
		}
	}

	if (player.GetIsSheathe()) {
		player.SetIsSheathe(false);
		player.SetRemainAttackChance(PLR::kMaxAttackChance);
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
		Render::DrawSprite(balancePoleTransform, uiCamera, WHITE, balancePoleGH);

		for (int i = 0; i < EMG::kMaxEnemy + 1; i++) {

			if (baranceObjects[i].GetIsActive()) {
				baranceObjects[i].Draw();
			}
		}

		Render::DrawSprite(balanceBasketTransform[0], uiCamera, WHITE, balanceBasketGH);
		Render::DrawSprite(balanceBasketTransform[1], uiCamera, WHITE, balanceBasketGH);
		Render::DrawSprite(waveStringTransform, uiCamera, WHITE, waveStringGH);
	}
}

void GameStageScene::ControlInfoDraw() {

	if (Length(input->GetControlDir()) > 0.0f) {
		Render::DrawSprite(contorolInfoTransform[0], uiCamera, 0x232323FF, contorolInfoGH[0]);
	} else {
		Render::DrawSprite(contorolInfoTransform[0], uiCamera, WHITE, contorolInfoGH[0]);
	}
	
	if (player.GetIsDash()) {
		Render::DrawSprite(contorolInfoTransform[1], uiCamera, 0x232323FF, contorolInfoGH[1]);
	} else {
		Render::DrawSprite(contorolInfoTransform[1], uiCamera, WHITE, contorolInfoGH[1]);
	}
	
	if (player.GetIsSheathe()) {
		Render::DrawSprite(contorolInfoTransform[2], uiCamera, 0x232323FF, contorolInfoGH[2]);
	} else {
		Render::DrawSprite(contorolInfoTransform[2], uiCamera, WHITE, contorolInfoGH[2]);
	}
	
}

void GameStageScene::CameraUpdate() {
	Vector2* cameraPos = mainCamera.GetPosPtr();
	*cameraPos = player.GetPos();

	mainCamera.CameraMoveLimit({ 640.0f,370.0f }, { 1408.0f,1678.0f });
}
