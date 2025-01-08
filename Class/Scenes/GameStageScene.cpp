#include "GameStageScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "ResultScene.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

#include "Class/Common/Collision2D.h"

void GameStageScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	mainCamera.Init();

	player.Init();
	player.SetCamera(&mainCamera);
	bulletManager.Init();
	bulletManager.SetCamera(&mainCamera);
	enemyManager.Init();
	enemyManager.SetCamera(&mainCamera);

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	enemyManager.SpawnEnemy({ 100.0f,100.0f }, { 64.0f,64.0f });

	map.LoadMap("Resources/Maps/stage1.txt");
	map.SetPlayer(&player);
	map.SetEnemyManager(&enemyManager);
	map.SetBulletManager(&bulletManager);
	
	testPopEnemyPos = { 1024.0f,1024.0f };
}

void GameStageScene::Update() {
	
	frameCount++;

	ObjectUpdate();
	ObjectCollision();
	ImGuiUpdate();
	
}

void GameStageScene::Draw() {
	map.Draw(&mainCamera);
	particleManager.Draw();
	player.Draw();
	bulletManager.Draw();
	enemyManager.Draw();
}

void GameStageScene::ImGuiUpdate() {
#ifdef _DEBUG

	ImGui::Begin("GameScene");

	ImGui::InputFloat("x", &testPopEnemyPos.x);
	ImGui::InputFloat("y", &testPopEnemyPos.y);
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
	return nullptr;
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
					} else {

						enemyManager.GetEnemyes()[e].GetPhysics()->AddForce(player.GetPhysics()->GetVelocity() * 20.0f, IMPACT);
						player.GetPhysics()->InversVelocity();

						particleManager.SlashEffect(
							enemyManager.GetEnemyes()[e].GetPos(), { 32.0f,32.0f },
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()), 10.0f, 5, 30, 5, 0);
					}
					player.SetIsAttack(false);
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

void GameStageScene::CameraUpdate() {
	Vector2* cameraPos = mainCamera.GetPosPtr();
	*cameraPos = player.GetPos();
}
