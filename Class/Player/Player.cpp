#include "Player.h"
#include "Resources/ConstantVariables/filePath.h"
#include "Class/Common/Mapchip.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // DEBUG



Player::Player() {
	frameCount = 0;

	transform.pos = kMapCenter;
	transform.angle = 0.0f;
	transform.scale = { 1.0f,1.0f };
	transform.size = { 32.0f,32.0f };
	
	physics.Init();
	isActive = true;

	camera = nullptr;
	maxHp = 3;
	hp = maxHp;
	isAlive = true;

	isMove = false;
	moveStackFrame = 0;
	moveSpeed = 2.0f;

	isDash = false;
	dashCoolDown = 0;
	dashPower = 100.0f;
	dashAfterimageRemainFrame = 10;
	dashAfterimageRemainInterval = 20;

	isAttack = false;
	attackCoolDown = 0;

	isSheathe = false;
	sheatheCoolDown = 0;

	angleDir = { cosf(transform.angle),sinf(transform.angle) };

	isLockOn = false;
	targetPos = { 0.0f,0.0f };

	remainAttackChance = PLR::kMaxAttackChance;

	damageCoolDown = 0;

	particleManager.Init();
	particleManager.SetCamera(camera);
	
	playerGH = Novice::LoadTexture("./Resources/Images/player.png");
	
}

void Player::Init() {
	frameCount = 0;
	physics.Init();
	particleManager.Init();
	particleManager.SetCamera(camera);

	LoadVariables();
}

void Player::Update() {
	
	frameCount++;

	transform.scale = { sinf(static_cast<float>(frameCount)*0.1f),sinf(static_cast<float>(frameCount)*0.1f) };

	particleManager.SetCamera(camera);
	particleManager.Update();
	angleDir = { cosf(transform.angle),sinf(transform.angle) };

	Move();
	LockOn();
	Dash();
	//Attack();
	Sheathe();
	StateCheck();
}

void Player::Draw() {
	
	particleManager.Draw();

	if (isAlive) {
		if (damageCoolDown % 6) {
			Render::DrawSprite(transform, *camera, 0xFF0000AF, playerGH);

		} else {
			Render::DrawSprite(transform, *camera, WHITE, playerGH);
			if (isAttack) {
				Render::DrawSprite(transform, *camera, RED, playerGH);
			}
		}

		Render::DrawLine(transform.pos, transform.pos + input->GetControlDir() * 100.0f, *camera, RED);
		Render::DrawLine(transform.pos, transform.pos + angleDir * 100.0f, *camera, GREEN);
	}
}

void Player::Move() {

	// 移動阻害
	if (moveStackFrame > 0) {
		moveStackFrame--;
		return;
	}

	// 動かしているかどうか
	if (Length(input->GetControlDir()) > 0.1f) {
		isMove = true;

	} else {
		isMove = false;
	}

	// 移動処理
	physics.AddForce(input->GetControlDir() * moveSpeed, IMPACT);
}

void Player::LockOn() {

	if (isLockOn) {

		if (Cross(angleDir, Normalize(targetPos - transform.pos)) >= 0.0f) {
			transform.angle += Length(angleDir - Normalize(targetPos - transform.pos)) * 0.35f;
		} else {
			transform.angle -= Length(angleDir - Normalize(targetPos - transform.pos)) * 0.35f;
		}

	} else {

		// 移動方向を見る
		if (isMove) {
			if (Cross(angleDir, input->GetControlDir()) >= 0.0f) {
				transform.angle += Length(angleDir - input->GetControlDir()) * 0.15f;
			} else {
				transform.angle -= Length(angleDir - input->GetControlDir()) * 0.15f;
			}
		}
	}
}

void Player::Dash() {
	// ダッシュをする処理
	if (input->GetControl(DASH, Triger)) {
		if (dashCoolDown <= 0) {

			dashCoolDown = PLR::kMaxDashCoolDown;

			if (isMove) {
				physics.AddForce(input->GetControlDir() * dashPower, IMPACT);
			} else {
				physics.AddForce(angleDir * dashPower, IMPACT);
			}

			isDash = true;
			isAttack = true;
		}
	}

	// ダッシュのクールダウン処理
	if (dashCoolDown > 0) {
		dashCoolDown--;
	}

	if (isDash) {
		if (dashCoolDown <= 0) {
			isDash = false;
		}
	}

	// ダッシュの攻撃判定
	if (isAttack) {
		if (dashCoolDown <= PLR::kMaxDashCoolDown / 5.0f) {
			isAttack = false;
		}
	}

	// ダッシュ中なら残像を残す
	if (isDash) {

		if (frameCount % (60 / (dashAfterimageRemainInterval + 1)) == 0) {
			particleManager.SpriteEffect(transform.pos, transform.size, transform.angle, dashAfterimageRemainFrame, playerGH);
		}
	}
}

void Player::Attack() {
	// 攻撃をする処理
	if (input->GetTriger(DIK_SPACE)) {
		if (attackCoolDown <= 0) {
			if (!isAttack) {

				moveStackFrame = PLR::kMaxMoveStackFrame;
				attackCoolDown = PLR::kMaxAttackCoolDown;
				isAttack = true;
			}
		}
	}

	// 攻撃クールダウン
	if (attackCoolDown > 0) {
		attackCoolDown--;
	}
}

void Player::Sheathe() {
	// 納刀する処理
	if (input->GetTriger(DIK_E) || input->GetControl(ATTACK,Triger)) {
		if (sheatheCoolDown <= 0) {
			if (!isSheathe && !isAttack) {

				moveStackFrame = PLR::kMaxMoveStackFrame*3;
				sheatheCoolDown = PLR::kMaxSheatheCoolDown;
				isSheathe = true;
			}
		}
	}

	// 納刀クールダウン
	if (sheatheCoolDown > 0) {
		sheatheCoolDown--;
	}
}

void Player::StateCheck() {
	// 死亡判定
	if (hp <= 0) {
		if (isAlive) {
			isAlive = false;
		}
	}
	
	// 無敵時間減少
	if (damageCoolDown > 0) {
		damageCoolDown--;
	}

	// 物理更新
	physics.Update(&transform.pos);
}

void Player::LoadVariables() {
	value = SJN::LoadJsonData(FPH::playerVariablesData);

	transform.pos.x = static_cast<float>(value["transform"]["pos"]["x"]);
	transform.pos.y = static_cast<float>(value["transform"]["pos"]["y"]);
	moveSpeed = static_cast<float>(value["moveSpeed"]);
	dashAfterimageRemainFrame = static_cast<int>(value["dashAfterimageRemainFrame"]);
	dashAfterimageRemainInterval = static_cast<int>(value["dashAfterimageRemainInterval"]);
}

void Player::SaveVariables() {
	value["moveSpeed"] = moveSpeed;
	value["dashAfterimageRemainFrame"] = dashAfterimageRemainFrame;
	value["dashAfterimageRemainInterval"] = dashAfterimageRemainInterval;

	SJN::SaveJsonData("Player", value);
}

void Player::UpdateImGui() {
#ifdef _DEBUG
	ImGui::Begin("Player");

	if (ImGui::TreeNode("transform")) {
		ImGui::Text("pos");
		ImGui::InputFloat("x", &transform.pos.x);
		ImGui::InputFloat("y", &transform.pos.y);
		ImGui::TreePop();
	}

	ImGui::InputFloat("moveSpeed", &moveSpeed);
	ImGui::InputInt("dashAfterimageRemainFrame", &dashAfterimageRemainFrame);
	ImGui::InputInt("dashAfterimageRemainInterval", &dashAfterimageRemainInterval);

	if (ImGui::TreeNode("data")) {
		if (ImGui::Button("save")) {
			SaveVariables();
		}

		if (ImGui::Button("load")) {
			LoadVariables();
		}
		ImGui::TreePop();
	}

	ImGui::End();
#endif // DEBUG
}

void Player::SetIsLockOn(int set) {
	isLockOn = set;
}

void Player::SetTargetPos(Vector2 set) {
	targetPos = set;
}

void Player::SetCamera(Camera* set) {
	camera = set;
}

void Player::SetIsAttack(int set) {
	isAttack = set;
}

void Player::SetIsSheathe(int set) {
	isSheathe = set;
}

void Player::SetRemainAttackChance(int set) {
	remainAttackChance = set;
}

void Player::SetIsDash(int set) {
	isDash = set;
}

int Player::GetIsAttack() {
	return isAttack;
}

int Player::GetIsSheathe() {
	return isSheathe;
}

int Player::GetIsDash() {
	return isDash;
}

int Player::GetRemainAttackChance() {
	return remainAttackChance;
}

int Player::GetCanAttack() {
	if (GetRemainAttackChance() > 0) {
		return true;
	}
	return false;
}

int Player::GetDamageCoolDown() {
	return damageCoolDown;
}

Vector2 Player::GetAttackPos() {
	return transform.pos + angleDir * PLR::kAttackReach;
}

Vector2* Player::GetPosPtr() {
	return &transform.pos;
}

void Player::CountDownRemainAttackChance() {
	remainAttackChance--;
	if (remainAttackChance <= 0) {
		remainAttackChance = 0;
	}
}

void Player::Damage() {
	if (damageCoolDown <= 0) {
		hp--;
		damageCoolDown = PLR::kMaxDamageCoolDown;
	}
}
