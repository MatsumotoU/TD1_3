#include "Player.h"
#include "Resources/ConstantVariables/filePath.h"
#include "Class/Common/Mapchip.h"
#include "Class/Common/MyEasing.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // DEBUG

Player::Player() {
	frameCount = 0;

	oldTransform = transform;

	swordGH = Novice::LoadTexture("./Resources/Images/sword.png");

	hpUiDrawFrame = 0;
	for (int i = 0; i < maxHp; i++) {
		hpTransform[0] = {
		{0.0f,64.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	}
	hpGH = Novice::LoadTexture("./Resources/Images/hp.png");
	lostHpGH = 0;

	haloTransform = {
		{-16.0f,0.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	haloGH = Novice::LoadTexture("./Resources/Images/playerHalo.png");
	orangeLightGH = Novice::LoadTexture("./Resources/Images/orangeLight.png");
	haloExprosionGH[0] = Novice::LoadTexture("./Resources/Images/haloExprosion1.png");
	haloExprosionGH[1] = Novice::LoadTexture("./Resources/Images/haloExprosion2.png");
	haloExprosionGH[2] = Novice::LoadTexture("./Resources/Images/haloExprosion3.png");
	haloExprosionGH[3] = Novice::LoadTexture("./Resources/Images/haloExprosion4.png");

	flapping = 0.0f;
	leftWingTransform = {
		{-16.0f,16.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	rightWingTransform = {
		{-16.0f,-16.0f},
		{32.0f,32.0f},
		{1.0f,-1.0f},
		0.0f };
	wingGH = Novice::LoadTexture("./Resources/Images/playerWing.png");
	featherGH = Novice::LoadTexture("./Resources/Images/feather.png");

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
	dashOP = Novice::LoadAudio("./Resources/Sounds/dash.mp3");

	isAttack = false;
	attackCoolDown = 0;

	isSheathe = false;
	sheatheCoolDown = 0;

	angleDir = { cosf(transform.angle),sinf(transform.angle) };

	isLockOn = false;
	targetPos = { 0.0f,0.0f };
	lockOnGH = Novice::LoadTexture("./Resources/Images/lockOn.png");
	targetTransform = {
		{0.0f,0.0f},
		{64.0f,64.0f},
		{1.2f,1.2f},
		0.0f };

	remainAttackChance = PLR::kMaxAttackChance;

	damageCoolDown = 0;

	particleManager.Init();
	particleManager.SetCamera(camera);

	playerGH = Novice::LoadTexture("./Resources/Images/player.png");

	seVolume = 0.5f;

	rightSowrdLocalTransform = {
		{24.0f,32.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		1.0f };
	leftSowrdLocalTransform = {
		{24.0f,-32.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		-1.0f };

	rightArm = {
		{24.0f,32.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		1.0f };
	leftArm = {
		{24.0f,-32.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		1.0f };
}

void Player::Init() {
	frameCount = 0;

	hpUiDrawFrame = 0;
	for (int i = 0; i < maxHp; i++) {
		hpTransform[i] = {
		{0.0f + 16.0f * static_cast<float>(i),64.0f},
		{32.0f,32.0f},
		{0.0f,0.0f},
		0.0f };
	}
	hpGH = Novice::LoadTexture("./Resources/Images/hp.png");
	lostHpGH = Novice::LoadTexture("./Resources/Images/lostHp.png");

	haloTransform = {
		{-16.0f,0.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	haloGH = Novice::LoadTexture("./Resources/Images/playerHalo.png");
	orangeLightGH = Novice::LoadTexture("./Resources/Images/orangeLight.png");
	haloExprosionGH[0] = Novice::LoadTexture("./Resources/Images/haloExprosion1.png");
	haloExprosionGH[1] = Novice::LoadTexture("./Resources/Images/haloExprosion2.png");
	haloExprosionGH[2] = Novice::LoadTexture("./Resources/Images/haloExprosion3.png");
	haloExprosionGH[3] = Novice::LoadTexture("./Resources/Images/haloExprosion4.png");

	flapping = 0.0f;
	leftWingTransform = {
		{-16.0f,16.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	rightWingTransform = {
		{-16.0f,-16.0f},
		{32.0f,32.0f},
		{1.0f,-1.0f},
		0.0f };
	wingGH = Novice::LoadTexture("./Resources/Images/playerWing.png");
	featherGH = Novice::LoadTexture("./Resources/Images/feather.png");

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
	attackRadius = 0.0f;

	isSheathe = false;
	sheatheCoolDown = 0;

	angleDir = { cosf(transform.angle),sinf(transform.angle) };

	isLockOn = false;
	targetPos = { 0.0f,0.0f };
	lockOnGH = Novice::LoadTexture("./Resources/Images/lockOn.png");
	targetTransform = {
		{0.0f,0.0f},
		{64.0f,64.0f},
		{1.2f,1.2f},
		0.0f };

	remainAttackChance = PLR::kMaxAttackChance;

	damageCoolDown = 0;

	particleManager.Init();
	particleManager.SetCamera(camera);

	playerGH = Novice::LoadTexture("./Resources/Images/player.png");

	LoadVariables();
	oldTransform = transform;

	isDrawLockOn = true;

	rightSowrdLocalTransform = {
		{0.0f,40.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		1.2f };
	leftSowrdLocalTransform = {
		{0.0f,-40.0f},
		{128.0f,32.0f},
		{0.5f,0.5f},
		-1.2f };
}

void Player::Update() {

	if (!isAlive) {
		transform.angle += 0.5f;
		physics.Update(&transform.pos);

		if (frameCount % 2) {
			particleManager.SlashEffect(transform.pos, { 32.0f,32.0f }, -angleDir, 1.0f, 100, 30, 1, featherGH);
		}
	}

	oldTransform = transform;

	frameCount++;

	particleManager.SetCamera(camera);
	particleManager.Update();
	angleDir = { cosf(transform.angle),sinf(transform.angle) };

	if (isAlive) {
		Move();
		LockOn();
		Dash();
		//Sheathe();
		StateCheck();
	}

	UpdateSword();
	HaloMove();
	WingMove();

	UpdateHpUi();

	if (input->GetTriger(DIK_F)) {
		Damage();
	}

	if (!map->GetIsFromToVisionClear(oldTransform.pos, transform.pos)) {
		transform.pos = oldTransform.pos;
	}
}

void Player::Draw() {

	particleManager.Draw();

	if (isActive) {

		// ダッシュ可能円
		/*Render::DrawEllipse(transform.pos,
			{ 64.0f * Eas::EaseInOutQuart(flapping,0.0f,1.0f),64.0f * Eas::EaseInOutQuart(flapping,0.0f,1.0f) },
			0.0f, *camera, 0xEEEEEEFF, kFillModeWireFrame);*/

		// 攻撃範囲
		if (GetAttackRadius() > transform.size.x * 0.6f) {
			Render::DrawEllipse(transform.pos, { GetAttackRadius(),GetAttackRadius() }, 0.0f, *camera, 0xD65A3123, kFillModeSolid);
			Render::DrawEllipse(transform.pos, { GetAttackRadius(),GetAttackRadius() }, 0.0f, *camera, 0xD65A31FF, kFillModeWireFrame);
		}

		// 本体
		if (damageCoolDown % 6 || (frameCount % 20 < 10 && hp <= 1 && damageCoolDown <= 0)) {
			Render::DrawSprite(transform, *camera, 0xFF0000AF, playerGH);

		} else {
			Render::DrawSprite(transform, *camera, WHITE, playerGH);
			/*if (isAttack) {
				Render::DrawSprite(transform, *camera, RED, playerGH);
			}*/
		}

		DrawSword();
		WingDraw();

		// ヘイロー
		if (damageCoolDown % 6 || (frameCount % 20 < 10 && hp <= 1 && damageCoolDown <= 0)) {
			Render::DrawSprite(haloTransform, *camera, 0xFF0000AF, haloGH);
		} else {
			Render::DrawSprite(haloTransform, *camera, WHITE, haloGH);
		}

		DrawHpUi();

		//Render::DrawLine(transform.pos, transform.pos + input->GetControlDir() * 100.0f, *camera, RED);
		//Render::DrawLine(transform.pos, transform.pos + angleDir * 100.0f, *camera, GREEN);

		if (isLockOn) {
			Render::DrawSprite(targetTransform, *camera, WHITE, lockOnGH);
		}
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

		targetTransform.pos = targetPos;
		targetTransform.angle += 0.1f;
		targetTransform.scale = { 1.5f,1.5f };
		targetTransform.scale.x += sinf(static_cast<float>(frameCount) * 0.2f) * 0.5f;
		targetTransform.scale.y += sinf(static_cast<float>(frameCount) * 0.2f) * 0.5f;

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

			transform.scale = { 2.0f,0.5f };
			leftWingTransform.scale = { 2.0f,2.0f };
			rightWingTransform.scale = { 2.0f,-2.0f };

			particleManager.SlashEffect(transform.pos, { 32.0f,32.0f }, -angleDir, 1.0f, 100, 30, 2, featherGH);

			camera->shakeRange += angleDir * 5.0f;
			camera->panRange -= 0.2f;

			Novice::PlayAudio(dashOP, false, seVolume);
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
			particleManager.SpriteEffect(rightWingTransform.pos, rightWingTransform.size, rightWingTransform.angle, dashAfterimageRemainFrame, wingGH);
			particleManager.SpriteEffect(leftWingTransform.pos, leftWingTransform.size, leftWingTransform.angle, dashAfterimageRemainFrame, wingGH);
			particleManager.SpriteEffect(haloTransform.pos, haloTransform.size, haloTransform.angle, dashAfterimageRemainFrame, haloGH);
		}

		if (frameCount % 5 == 0) {
			particleManager.SlashEffect(transform.pos, { 32.0f,32.0f }, -angleDir, 1.0f, 50, 30, 1, featherGH);
		}
	}

	// ダッシュ中の変形
	Eas::SimpleEaseIn(&transform.scale.x, 1.0f, 0.1f);
	Eas::SimpleEaseIn(&transform.scale.y, 1.0f, 0.1f);
	Eas::SimpleEaseIn(&leftWingTransform.scale.x, 1.0f, 0.1f);
	Eas::SimpleEaseIn(&leftWingTransform.scale.y, 1.0f, 0.1f);
	Eas::SimpleEaseIn(&rightWingTransform.scale.x, 1.0f, 0.1f);
	Eas::SimpleEaseIn(&rightWingTransform.scale.y, -1.0f, 0.1f);

	// ダッシュしてるなら攻撃範囲増加
	if (isAttack) {
		Eas::SimpleEaseIn(&attackRadius, PLR::kMaxAttackRadius, 0.5f);
	} else {
		Eas::SimpleEaseIn(&attackRadius, 0.0f, 0.3f);
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
	if (input->GetTriger(DIK_E) || input->GetControl(ATTACK, Triger)) {
		if (sheatheCoolDown <= 0) {
			if (!isSheathe && !isAttack) {

				if (remainAttackChance < 2) {
					moveStackFrame = PLR::kMaxMoveStackFrame * 3;
					sheatheCoolDown = PLR::kMaxSheatheCoolDown;
					isSheathe = true;

					particleManager.FromToEffect(haloTransform.pos, &transform.pos, { 32.0f,32.0f }, PLR::kMaxSheatheCoolDown, 10, orangeLightGH, WHITE);
					particleManager.AnimEffect(haloTransform.pos, { 256.0f,256.0f }, Random(6.28f, 0.0f), 4, 3, false, haloExprosionGH);

					camera->panRange -= 0.2f;
				}
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

	// 攻撃回数
	if (remainAttackChance <= 2) {
		remainAttackChance = 2;
	}

	// 物理更新
	physics.Update(&transform.pos);
}

void Player::HaloMove() {
	haloTransform = {
		{-16.0f,0.0f},
		{32.0f,32.0f},
		{1.0f,1.0f},
		0.0f };
	float sheatheCoolT = 1.0f - (static_cast<float>(sheatheCoolDown) / static_cast<float>(PLR::kMaxSheatheCoolDown));
	haloTransform.scale = { powf(sheatheCoolT,3.0f) ,powf(sheatheCoolT,3.0f) };
	haloTransform.pos = haloTransform.pos * MakeAffineMatrix(transform.scale, transform.angle, transform.pos);
}

void Player::WingMove() {
	flapping = static_cast<float>(dashCoolDown) / static_cast<float> (PLR::kMaxDashCoolDown);

	leftWingTransform.pos = { -16.0f,24.0f };
	leftWingTransform.pos = leftWingTransform.pos * MakeAffineMatrix(transform.scale, transform.angle + (sinf(static_cast<float>(frameCount) * 0.2f) * 0.1f) + (flapping * 0.5f), transform.pos);
	leftWingTransform.angle = transform.angle + sinf(static_cast<float>(frameCount) * 0.2f) * 0.1f + (flapping * 1.2f);

	rightWingTransform.pos = { -16.0f,-24.0f };
	rightWingTransform.pos = rightWingTransform.pos * MakeAffineMatrix(transform.scale, transform.angle + (-sinf(static_cast<float>(frameCount) * 0.2f) * 0.1f) + (-flapping * 0.5f), transform.pos);
	rightWingTransform.angle = transform.angle - sinf(static_cast<float>(frameCount) * 0.2f) * 0.1f + (-flapping * 1.2f);
}

void Player::WingDraw() {
	if (damageCoolDown % 6 || (frameCount % 20 < 10 && hp <= 1 && damageCoolDown <= 0)) {
		Render::DrawSprite(leftWingTransform, *camera, 0xFF0000AF, wingGH);
		Render::DrawSprite(rightWingTransform, *camera, 0xFF0000AF, wingGH);
	} else {
		Render::DrawSprite(leftWingTransform, *camera, ColorFade(WHITE, 1.0f - flapping), wingGH);
		Render::DrawSprite(rightWingTransform, *camera, ColorFade(WHITE, 1.0f - flapping), wingGH);
	}
}

void Player::UpdateHpUi() {

	if (hp == 1) {
		hpUiDrawFrame = 60;
	}

	for (int i = 0; i < maxHp; i++) {
		hpTransform[i].pos = { 0.0f, 48.0f * hpTransform[i].scale.x };
		if (hp <= i) {
			hpTransform[i].pos += {Random(3.0f, -3.0f), Random(3.0f, -3.0f)};
		}
		hpTransform[i].pos.y += sinf(static_cast<float>(frameCount) * 0.1f) * 8.0f;
		hpTransform[i].pos = hpTransform[i].pos * MakeRotateMatrix(2.0f * static_cast<float>(i) + Length(hpTransform[i].scale) - 1.414f);
		hpTransform[i].pos += transform.pos;
		hpTransform[i].angle = 2.0f * static_cast<float>(i) + Length(hpTransform[i].scale) - 1.414f;

		if (hp == 1 && frameCount % 60 == 0) {
			hpTransform[0].scale = { 1.2f,1.2f };
		}
	}

	if (hpUiDrawFrame > 0) {
		hpUiDrawFrame--;
		for (int i = 0; i < maxHp; i++) {
			Eas::SimpleEaseIn(&hpTransform[i].scale.x, 1.0f, 0.2f);
			Eas::SimpleEaseIn(&hpTransform[i].scale.y, 1.0f, 0.2f);
		}
	} else {
		for (int i = 0; i < maxHp; i++) {
			Eas::SimpleEaseIn(&hpTransform[i].scale.x, 0.0f, 0.2f);
			Eas::SimpleEaseIn(&hpTransform[i].scale.y, 0.0f, 0.2f);
		}
	}
}

void Player::DrawHpUi() {
	for (int i = 0; i < hp; i++) {
		if (Length(hpTransform[i].scale) >= 0.1f) {
			Render::DrawSprite(hpTransform[i], *camera, WHITE, hpGH);
		}
	}

	for (int i = Clamp(hp, 0, 2); i < maxHp; i++) {
		if (Length(hpTransform[i].scale) >= 0.1f) {
			Render::DrawSprite(hpTransform[i], *camera, WHITE, lostHpGH);
		}
	}
}

void Player::UpdateSword() {

	float attackT = attackRadius / PLR::kMaxAttackRadius;
	float armRotateVal = 3.0f;
	rightArm.pos = rightSowrdLocalTransform.pos * MakeAffineMatrix({ 1.0f,1.0f }, -attackT * armRotateVal, { 0.0f,0.0f });
	leftArm.pos = leftSowrdLocalTransform.pos * MakeAffineMatrix({ 1.0f,1.0f }, attackT * armRotateVal, { 0.0f,0.0f });

	rightArm.pos = rightArm.pos * MakeAffineMatrix(transform.scale, transform.angle, transform.pos);
	leftArm.pos = leftArm.pos * MakeAffineMatrix(transform.scale, transform.angle, transform.pos);
	rightArm.angle = transform.angle + rightSowrdLocalTransform.angle - (armRotateVal * attackT);
	leftArm.angle = transform.angle + leftSowrdLocalTransform.angle + (armRotateVal * attackT);
	
}

void Player::DrawSword() {

	Render::DrawSprite(rightArm, *camera, WHITE, swordGH);
	Render::DrawSprite(leftArm, *camera, WHITE, swordGH);

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

void Player::SetMapchip(Mapchip* set) {
	map = set;
}

void Player::SetDrawLockOn(int set) {
	isDrawLockOn = set;
}

int Player::GetIsAlive() {
	return isAlive;
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

int Player::GetGraphHandle() {
	return playerGH;
}

int Player::GetHp() {
	return hp;
}

int Player::GetMaxHp() {
	return maxHp;
}

Vector2 Player::GetAngleDir() {
	return angleDir;
}

float Player::GetAttackRadius() {
	return attackRadius + (transform.size.x * 0.5f);
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
		hpUiDrawFrame = 120;
		camera->panRange -= 0.5f;
	}
}
