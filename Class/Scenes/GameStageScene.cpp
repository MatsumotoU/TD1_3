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

	player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	map.SetCamera(&mainCamera);
	map.SetPlayer(&player);
	map.SetEnemyManager(&enemyManager);
	map.SetBulletManager(&bulletManager);
	
	testPopEnemyPos = { 1024.0f,1024.0f };
	isChangeWave = false;

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
	Novice::DrawBox(0, 0, 1280, 720, 0.0f,0x222831FF, kFillModeSolid);

	map.Draw();
	particleManager.Draw();
	player.Draw();
	bulletManager.Draw();
	enemyManager.Draw();
	WaveUiDraw();
}

void GameStageScene::ImGuiUpdate() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("GameStage = %d Wave = %d",gameStage,wave);
	ImGui::InputFloat("x", &testPopEnemyPos.x);
	ImGui::InputFloat("y", &testPopEnemyPos.y);
	ImGui::SliderFloat("balanceAngle", &balanceAngle, -3.14f, 3.14f);
	if (ImGui::Button("PopEnemy")) {
		enemyManager.SpawnEnemy(testPopEnemyPos, { 64.0f,64.0f });
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
		}
	}

	if (isChangeWave) {

		// 天秤のかご傾き処理
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

		
		if (balanceBasketTransform[0].scale.x >= 1.0f) {

			
		}

		// プレイヤー召喚
		if (frameCount >= 180 || wave >= 4) {
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
									enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", 0);
								bulletManager.ShotBullet(
									enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
									-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", 0);
								enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
							}

							mainCamera.shakeRange += {10.0f, 10.0f};
							stopObjectUpdateFrame = 15;
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
		bulletManager.ShotBullet(player.GetAttackPos(), {64.0f,64.0f}, {0.0f,0.0f}, 0.0f, 10, "player", 0);
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
						enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", 0);
					bulletManager.ShotBullet(
						enemyManager.GetEnemyes()[e].GetPos(), enemyManager.GetEnemyes()[e].GetSize(),
						-enemyManager.GetEnemyes()[e].GetHitDir(), 30.0f, 180, "exprosion", 0);
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

void GameStageScene::WaveUiDraw() {
	if (isChangeWave) {
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000DF, kFillModeSolid);
		Render::DrawSprite(balancePoleTransform, uiCamera, WHITE, balancePoleGH);
		Render::DrawSprite(balanceBasketTransform[0], uiCamera, WHITE, balanceBasketGH);
		Render::DrawSprite(balanceBasketTransform[1], uiCamera, WHITE, balanceBasketGH);
		Render::DrawSprite(waveStringTransform, uiCamera, WHITE, waveStringGH);
	}
}

void GameStageScene::CameraUpdate() {
	Vector2* cameraPos = mainCamera.GetPosPtr();
	*cameraPos = player.GetPos();

	mainCamera.CameraMoveLimit({ 640.0f,370.0f }, { 1408.0f,1678.0f });
}
