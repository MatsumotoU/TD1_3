#include "GameStageScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "ResultScene.h"

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

	enemyManager.SpawnEnemy({ 0.0f,100.0f }, { 64.0f,64.0f });
	enemyManager.SpawnEnemy({ 100.0f,100.0f }, { 64.0f,64.0f });
	enemyManager.SpawnEnemy({ 200.0f,100.0f }, { 64.0f,64.0f });

}

void GameStageScene::Update() {
	
	ObjectUpdate();
	ObjectCollision();
	
}

void GameStageScene::Draw() {
	player.Draw();
	bulletManager.Draw();
	enemyManager.Draw();
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
}

void GameStageScene::ObjectCollision() {

	// 敵の当たり判定
	for (int e = 0; e < EMG::kMaxEnemy; e++) {
		if (enemyManager.GetEnemyes()[e].GetIsAlive()) {
			// プレイヤー
			if (player.GetIsDash()) {
				if (IsHitCollisionEllipse(
					player.GetPos(), enemyManager.GetEnemyes()[e].GetPos(),
					player.GetSize().x * 0.5f, enemyManager.GetEnemyes()[e].GetSize().x * 0.5f)) {

					if (!enemyManager.GetEnemyes()[e].GetIsHitAttack() && player.GetCanAttack()) {
						enemyManager.GetEnemyes()[e].SetIsHitAttack(true);
						enemyManager.GetEnemyes()[e].SetHitAttackDir(
							Normalize(player.GetPos() - enemyManager.GetEnemyes()[e].GetPos()) * MakeRotateMatrix(3.14f * 0.5f));
						player.CountDownRemainAttackChance();
					} else {

						enemyManager.GetEnemyes()[e].GetPhysics()->AddForce(player.GetPhysics()->GetVelocity() * 20.0f, IMPACT);
						player.GetPhysics()->InversVelocity();
					}
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
	}
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
