#include "Enemy.h"
#include "Class/Common/MyEasing.h"
#include "Class/Common/Mapchip.h"

Enemy::Enemy() {
	transform.pos = { 0.0f,0.0f };
	transform.angle = 0.0f;
	transform.scale = { 1.0f,1.0f };
	transform.size = { 32.0f,32.0f };

	drawTransform = transform;

	physics.Init();
	isActive = false;

	isAlive = false;
	enemyGH = 0;
	color = WHITE;

	isHitAttack = false;
	hitDir = { 0.0f,0.0f };

	isExprosion = false;

	targetRoute.clear();
	nextRouteNum = 0;

	moveSpeed = 0.5f;

	deathFrame = 60;

	stunFrame = 0;
	angleDir = { 1.0f,0.0f };
	moveDir = { 0.0f,0.0f };
	enemyGH = 0;

	canAttack = false;
	isSeePlayer = false;
	type = ENM::None;
	playerPos = nullptr;
	attackRange = 0.0f;
	isAttacking = false;
	attackCoolDown = 0;
	attackAnticipationFrame = 0;
	maxAttackAnticipationFrame = 0;

	swordGH = 0;
	swordTransform.pos = transform.pos;
	swordTransform.angle = 0.0f;
	swordTransform.scale = { 0.8f,0.8f };
	swordTransform.size = { 128.0f,32.0f };

	isExprosion = false;
	map = nullptr;

	isSpawning = false;
}

void Enemy::Init() {
	attackRange = 0.0f;
	stunFrame = 0;
	type = ENM::None;
	isAttacking = false;
	attackCoolDown = 0;
	isHitAttack = false;
	isExprosion = false;
	isActive = false;
	isAlive = false;
	isSpawning = false;
	canAttack = false;
	oldTransform = transform;

	exprosionRadius = 0.0f;
	for (int i = 0; i < ENM::kCircleResolution; i++) {
		exprosionRange[i] = {
			cosf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius,
			sinf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius };
		exprosionMaxRange[i] = exprosionRange[i];
	}
	rotateSpeed = 0.2f;
	spawnFrame = 60;

	spawnScale = { 0.0f,0.0f };
}

void Enemy::Update() {

	if (isSpawning) {
		if (spawnFrame > 0) {
			spawnFrame--;
			return;
		} else {
			isSpawning = false;
		}
	}
	Eas::SimpleEaseIn(&spawnScale.x, 1.0f, 0.3f);
	Eas::SimpleEaseIn(&spawnScale.y, 1.0f, 0.3f);

	oldTransform = transform;

	if (isAlive) {
		if (stunFrame <= 0) {
			Move();
			LockOn();
			Attack();
		}
	}
	//UpdateSword();
	StateCheck();

	physics.Update(&transform.pos);

	if (!map->GetIsFromToVisionClear(oldTransform.pos, transform.pos)) {
		transform.pos = oldTransform.pos;
	}

	for (int i = 0; i < ENM::kCircleResolution; i++) {
		if (map->GetIsFromToVisionClear(transform.pos, exprosionRange[i] + transform.pos)) {
			/*exprosionRange[i] = {
				cosf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius,
				sinf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius };*/
			if (Length(exprosionRange[i]) <= exprosionRadius) {
				exprosionRange[i] += {
					cosf((6.28f / static_cast<float>(ENM::kCircleResolution))* static_cast<float>(i))* ((170.0f / static_cast<float>(ENM::kMaxStunFrame)) * 2.0f),
						sinf((6.28f / static_cast<float>(ENM::kCircleResolution))* static_cast<float>(i))* ((170.0f / static_cast<float>(ENM::kMaxStunFrame)) * 2.0f)};
			}
		} else {
			exprosionRange[i].x -= (exprosionRange[i].x) * 0.1f;
			exprosionRange[i].y -= (exprosionRange[i].y) * 0.1f;

			exprosionMaxRange[i].x -= (exprosionMaxRange[i].x) * 0.1f;
			exprosionMaxRange[i].y -= (exprosionMaxRange[i].y) * 0.1f;
		}

		exprosionMaxRange[i] = {
			cosf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * 170.0f,
			sinf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * 170.0f };
	}
}

void Enemy::Draw() {
	if (isSpawning) {

		Render::DrawEllipse(transform.pos,
			{ 24.0f * (1.0f - (static_cast<float>(spawnFrame) / 60.0f)),24.0f * (1.0f - (static_cast<float>(spawnFrame) / 60.0f)) },
			0.0f, *camera, 0xD65A31FF, kFillModeSolid);
		Render::DrawEllipse(transform.pos,
			{ 24.0f,24.0f},
			0.0f, *camera, 0xD65A31FF, kFillModeWireFrame);

	} else {

		if (stunFrame > 0) {
			for (int i = 0; i < ENM::kCircleResolution; i++) {

				Render::DrawLine(
					exprosionMaxRange[i] + transform.pos,
					exprosionMaxRange[(i + 1) % ENM::kCircleResolution] + transform.pos,
					*camera, 0xD65A31FF);

				Render::DrawTriangle(
					transform.pos,
					exprosionRange[i] + transform.pos,
					exprosionRange[(i + 1) % ENM::kCircleResolution] + transform.pos,
					*camera, 0xD65A3180, kFillModeSolid);
			}
		}

		if (isAlive) {
			Render::DrawSprite(drawTransform, *camera, color, *enemyGH);
		}
	}

	/*if (isHitAttack) {
		Render::DrawLine(transform.pos, transform.pos + hitDir * 100.0f, *camera, RED);
		Render::DrawLine(transform.pos, transform.pos + -hitDir * 100.0f, *camera, RED);
	}*/

	//DrawSword();

#ifdef _DEBUG
	for (int i = static_cast<int>(targetRoute.size() - 1); i > 0; i--) {
		Render::DrawLine(targetRoute[i], targetRoute[i - 1], *camera, RED);
	}
#endif // _DEBUG

}

void Enemy::SetCamera(Camera* set) {
	camera = set;
}

void Enemy::SetIsAlive(int set) {
	isAlive = set;
}

void Enemy::SetIsHitAttack(int set) {
	isHitAttack = set;
}

void Enemy::SetHitAttackDir(Vector2 set) {
	hitDir = set;
}

void Enemy::SetPlayerRoute(std::vector<Vector2> set) {
	targetRoute.clear();
	targetRoute = set;
	nextRouteNum = static_cast<int>(targetRoute.size());
}

void Enemy::SetDeathFrame(int set) {
	deathFrame = set;
}

void Enemy::SetEnemyType(ENM::Type set) {
	type = set;
}

void Enemy::SetCanAttack(int set) {
	canAttack = set;
}

void Enemy::SetIsSeePlayer(int set) {
	isSeePlayer = set;
}

void Enemy::SetPlayerPos(Vector2* set) {
	playerPos = set;
}

void Enemy::SetIsShot(int set) {
	isShot = set;
}

void Enemy::SetIsExprosion(int set) {
	isExprosion = set;
}

void Enemy::SetGH(int* set) {
	enemyGH = set;
}

void Enemy::SetMapchip(Mapchip* set) {
	map = set;
}

void Enemy::SetStunFrame(int set) {
	stunFrame = set;
}

void Enemy::SetIsSpawning(int set) {
	isSpawning = set;
}

int Enemy::GetIsAlive() {
	return isAlive;
}

int Enemy::GetIsHitAttack() {
	return isHitAttack;
}

Vector2 Enemy::GetHitDir() {
	return hitDir;
}

Vector2* Enemy::GetPosPtr() {
	return &transform.pos;
}

int Enemy::GetGraphHandle() {
	return *enemyGH;
}

ENM::Type Enemy::GetType() {
	return type;
}

int Enemy::GetIsAttack() {
	return isAttack;
}

int Enemy::GetIsShot() {
	return isShot;
}

Vector2 Enemy::GetAngleDir() {
	return { cosf(transform.angle),sinf(transform.angle) };
}

int Enemy::GetIsReqestExprosion() {
	return isExprosion;
}

Vector2 Enemy::GetScreenPos() {
	Vector2 result = { 0.0f };
	result = result * camera->GetWvpVpMatrix(transform.pos, transform.scale, transform.angle);
	return result;
}

int Enemy::GetIsSpawning() {
	return isSpawning;
}

void Enemy::Move() {


	if (isAttacking) {
		return;
	}

	// 攻撃範囲内なら止まる
	if (isSeePlayer) {
		if (attackRange >= Length(transform.pos - *playerPos)) {
			canAttack = true;
			return;
		} else {
			canAttack = false;
		}
	}

	// 目標めがけて行く
	if (isSeePlayer) {

		// プレイヤーめがけて突撃
		moveDir = -Normalize(transform.pos - *playerPos);
		physics.AddForce(moveDir * moveSpeed, IMPACT);

	} else {

		// ラインに沿って動く
		if (nextRouteNum > 0) {
			moveDir = -Normalize(transform.pos - targetRoute[nextRouteNum - 1]);
			physics.AddForce(moveDir * moveSpeed, IMPACT);

			if (Length(transform.pos - targetRoute[nextRouteNum - 1]) <= 32.0f) {

				nextRouteNum--;
			}
		}
	}
}

void Enemy::LockOn() {

	if (type == ENM::Melee) {
		if (isAttacking) {
			return;
		}
	}

	if (isSeePlayer) {

		// プレイヤーを見る
		angleDir = { cosf(transform.angle),sinf(transform.angle) };
		if (Cross(angleDir, Normalize(*playerPos - transform.pos)) >= 0.0f) {
			transform.angle += Length(angleDir - Normalize(*playerPos - transform.pos)) * rotateSpeed;
		} else {
			transform.angle -= Length(angleDir - Normalize(*playerPos - transform.pos)) * rotateSpeed;
		}

	} else {

		// 移動方向を見る
		angleDir = { cosf(transform.angle),sinf(transform.angle) };
		if (Cross(angleDir, moveDir) >= 0.0f) {
			transform.angle += Length(angleDir - moveDir) * rotateSpeed;
		} else {
			transform.angle -= Length(angleDir - moveDir) * rotateSpeed;
		}
	}


}

void Enemy::Attack() {

	if (type == ENM::Melee) {
		if (!isAttack) {
			if (canAttack) {
				if (attackCoolDown <= 0) {
					if (!isAttacking) {

						isAttacking = true;
						attackCoolDown = 180;
						attackAnticipationFrame = maxAttackAnticipationFrame;
					}
				}
			}

			if (isAttacking) {
				if (attackAnticipationFrame > 0) {
					attackAnticipationFrame--;
				} else {
					if (!isAttack) {
						isAttacking = false;
						isAttack = true;
						physics.AddForce(angleDir * 60.0f, IMPACT);
					}
				}
			}
		}

		if (isAttack) {
			if (Length(physics.GetVelocity()) <= 3.0f) {
				isAttack = false;
			}
		}

		if (!isAttack && !isAttacking) {
			if (attackCoolDown > 0) {
				attackCoolDown--;
			}
		}
	}

	if (type == ENM::Shot) {
		if (!isShot) {
			if (canAttack && isSeePlayer) {
				if (attackCoolDown <= 0) {
					if (!isAttacking) {

						isAttacking = true;
						attackCoolDown = 60;
						attackAnticipationFrame = maxAttackAnticipationFrame;
					}
				}
			}

			if (isAttacking) {
				if (attackAnticipationFrame > 0) {
					attackAnticipationFrame--;
				} else {
					if (!isAttack) {
						isAttacking = false;
						isShot = true;
					}
				}
			}
		}

		if (!isShot && !isAttacking) {
			if (attackCoolDown > 0) {
				attackCoolDown--;
			}
		}
	}

}

void Enemy::StateCheck() {

	// スタンしてたら動かない
	if (stunFrame > 0) {
		stunFrame--;
	}

	// スタン値
	drawTransform = transform;
	if (stunFrame <= 0) {
		if (isHitAttack) {
			isExprosion = true;
		}

		drawTransform = transform;
	} else {

		float shakeEnm = static_cast<float>(stunFrame) / static_cast<float>(ENM::kMaxStunFrame);

		drawTransform.scale = { 1.0f + (hitDir.x * shakeEnm) * 0.5f,1.0f + (hitDir.y * shakeEnm) * 0.5f };

		drawTransform.pos += {
			Random(transform.size.x * 0.3f * shakeEnm, -transform.size.x * 0.3f * shakeEnm),
				Random(transform.size.y * 0.3f * shakeEnm, -transform.size.y * 0.3f * shakeEnm)};

		exprosionRadius = Eas::EaseIn(static_cast<float>(stunFrame) / static_cast<float>(ENM::kMaxStunFrame), 2.0f, 170.0f, 0.0f);
	}

	// 死んでるか
	if (!isAlive) {
		if (deathFrame > 0) {
			deathFrame--;
			drawTransform.scale = { 0.0f,0.0f };
			/*drawTransform.scale = {
				powf(static_cast<float>(deathFrame) / static_cast<float>(ENM::kMaxDeathFrame),3.0f) ,
				powf(static_cast<float>(deathFrame) / static_cast<float>(ENM::kMaxDeathFrame),3.0f) };*/
			drawTransform.angle += (static_cast<float>(deathFrame) / static_cast<float>(ENM::kMaxDeathFrame));
		} else {
			isActive = false;
		}
	}

	// 攻撃してるかどうか
	if (isAttacking) {
		drawTransform.scale += {
			(1.0f - static_cast<float>(attackAnticipationFrame) / static_cast<float>(maxAttackAnticipationFrame)) * 0.5f,
			(1.0f - static_cast<float>(attackAnticipationFrame) / static_cast<float>(maxAttackAnticipationFrame)) * 0.5f};
	}
}

void Enemy::UpdateExprodeCircle(int count) {

	for (int p = 0; p < count; p++) {
		for (int i = 0; i < ENM::kCircleResolution; i++) {
			if (map->GetIsFromToVisionClear(transform.pos, exprosionRange[i] + transform.pos)) {
				/*exprosionRange[i] = {
					cosf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius,
					sinf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * exprosionRadius };*/
				if (Length(exprosionRange[i]) <= exprosionRadius) {
					exprosionRange[i] += {
						cosf((6.28f / static_cast<float>(ENM::kCircleResolution))* static_cast<float>(i))* ((170.0f / static_cast<float>(ENM::kMaxStunFrame)) * 2.0f),
							sinf((6.28f / static_cast<float>(ENM::kCircleResolution))* static_cast<float>(i))* ((170.0f / static_cast<float>(ENM::kMaxStunFrame)) * 2.0f)};
				}
			} else {
				exprosionRange[i].x -= (exprosionRange[i].x) * 0.1f;
				exprosionRange[i].y -= (exprosionRange[i].y) * 0.1f;

				exprosionMaxRange[i].x -= (exprosionMaxRange[i].x) * 0.1f;
				exprosionMaxRange[i].y -= (exprosionMaxRange[i].y) * 0.1f;
			}

			exprosionMaxRange[i] = {
				cosf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * 170.0f,
				sinf((6.28f / static_cast<float>(ENM::kCircleResolution)) * static_cast<float>(i)) * 170.0f };
		}
	}
}

void Enemy::UpdateSword() {
	if (isHitAttack) {
		if (isAlive) {

			Vector2 localSwordPos = { 0.0f,48.0f + 16.0f * (sinf(static_cast<float>(stunFrame) * 0.1f) * 0.5f) };
			swordTransform.pos = localSwordPos + transform.pos;
			swordTransform.angle = -3.14f * 0.5f;
		} else {

			Vector2 localSwordPos = { 0.0f,Eas::EaseIn(static_cast<float>(deathFrame) / static_cast<float>(ENM::kMaxDeathFrame),5.0f,0.0f,128.0f) };
			swordTransform.pos = localSwordPos + transform.pos;
			swordTransform.angle = -3.14f * 0.5f;
		}
	}
}

void Enemy::DrawSword() {
	if (isHitAttack) {
		Render::DrawSprite(swordTransform, *camera, WHITE, swordGH);
	}
}

void Enemy::Stun() {
	stunFrame = ENM::kMaxStunFrame;
}

void Enemy::TypeInit() {
	switch (type)
	{
	case ENM::Melee:
		attackRange = 256.0f;
		moveSpeed = 0.0f;
		transform.size = { 64.0f,64.0f };
		attackAnticipationFrame = 0;
		maxAttackAnticipationFrame = 60;
		rotateSpeed = 0.2f;
		break;
	case ENM::Shot:
		attackRange = 512.0f;
		moveSpeed = 0.2f;
		transform.size = { 64.0f,64.0f };
		attackAnticipationFrame = 0;
		maxAttackAnticipationFrame = 120;
		rotateSpeed = 0.2f;
		break;
	case ENM::Shield:
		attackRange = 128.0f;
		moveSpeed = 0.1f;
		transform.size = { 64.0f,64.0f };
		attackAnticipationFrame = 0;
		maxAttackAnticipationFrame = 120;
		rotateSpeed = 0.02f;
		break;
	default:
		break;
	}
}
