#include "ContorolTutorialUI.h"
#include "Class/Common/MyEasing.h"
#include "Class/Player/Player.h"
#include "Class/Enemy/EnemyManager.h"
#include "Class/Common/Collision2D.h"

void ContorolTutorialUI::Init() {
	alpha = 1.0f;

	transform = { 0 };
	transform.pos = { -900.0f,-260.0f };
	transform.scale = { 0.8f,0.8f };
	transform.size = { 480.0f,192.0f };
	tutorialCount = 0;

	hintTransform = transform;
	hintTransform.scale = { 0.5f,0.5f };
	hintTransform.pos.y = -280.0f;

	hintGH[0] = Novice::LoadTexture("./Resources/Images/hint1.png");
	hintGH[1] = Novice::LoadTexture("./Resources/Images/hint2.png");

	windowGH = Novice::LoadTexture("./Resources/Images/controlrTutorialWindow.png");

	keyTutorialGH[0] = Novice::LoadTexture("./Resources/Images/keyTutorial1.png");
	keyTutorialGH[1] = Novice::LoadTexture("./Resources/Images/keyTutorial2.png");
	keyTutorialGH[2] = Novice::LoadTexture("./Resources/Images/keyTutorial3.png");
	keyTutorialGH[3] = Novice::LoadTexture("./Resources/Images/keyTutorial4.png");

	keyTutorialPushGH[0] = Novice::LoadTexture("./Resources/Images/keyTutorialPush1.png");
	keyTutorialPushGH[1] = Novice::LoadTexture("./Resources/Images/keyTutorialPush2.png");
	keyTutorialPushGH[2] = Novice::LoadTexture("./Resources/Images/keyTutorialPush3.png");

	controllerTutorialGH[0] = Novice::LoadTexture("./Resources/Images/controllerTutorial1.png");
	controllerTutorialGH[1] = Novice::LoadTexture("./Resources/Images/controllerTutorial2.png");
	controllerTutorialGH[2] = Novice::LoadTexture("./Resources/Images/controllerTutorial3.png");
	controllerTutorialGH[3] = Novice::LoadTexture("./Resources/Images/controllerTutorial4.png");

	controllerTutorialPushGH[0] = Novice::LoadTexture("./Resources/Images/controllerTutorialPush1.png");
	controllerTutorialPushGH[1] = Novice::LoadTexture("./Resources/Images/controllerTutorialPush2.png");
	controllerTutorialPushGH[2] = Novice::LoadTexture("./Resources/Images/controllerTutorialPush3.png");

	isHideUI = false;
	isInScreeenUI = true;
	enemyManager = nullptr;
	tutorialStep = 0;
	frameCount = 0;
	isActive = true;
}

void ContorolTutorialUI::Update() {

	frameCount++;

	if (isActive) {

		if (input->GetTriger(DIK_H) || Novice::IsTriggerButton(0, kPadButton12)) {
			if (isInScreeenUI) {
				isInScreeenUI = false;
			} else {
				isInScreeenUI = true;
			}
		}
		
		Vector2 zeroVec = { 0.0f,0.0f };
		if ((isHideUI || enemyManager->GetIsHitScreenEnemies({ 240.0f,600.0f }, transform.size)) && !isInScreeenUI) {
			Eas::SimpleEaseIn(&alpha, 0.3f, 0.2f);
		} else {
			Eas::SimpleEaseIn(&alpha, 1.0f, 0.1f);
		}
	}

	if (tutorialCount == 0) {
		if (Length(input->GetControlDir()) > 0.0f) {
			tutorialStep++;
		}
	}

	if (tutorialCount == 1) {
		if (input->GetControl(DASH, Triger)) {
			tutorialStep+=20;
		}
	}

	if (tutorialCount == 2) {
		if (input->GetTriger(DIK_E) || input->GetControl(ATTACK, Triger)) {
			tutorialStep += 20;
		}
	}

	if (tutorialStep >= 100 && tutorialCount < 2) {
		tutorialCount++;
		tutorialStep = 0;
	}

	if (isInScreeenUI) {
		Eas::SimpleEaseIn(&transform.pos.x, -400.0f, 0.3f);
		Eas::SimpleEaseIn(&hintTransform.pos.x, -900.0f, 0.3f);

	} else {
		Eas::SimpleEaseIn(&transform.pos.x, -900.0f, 0.2f);
		Eas::SimpleEaseIn(&hintTransform.pos.x, -480.0f, 0.2f);

	}

	transform.pos.y += sinf(static_cast<float>(frameCount) * 0.1f)*0.3f;
}

void ContorolTutorialUI::Draw() {

	if (!isActive) {
		return;
	}

	Render::DrawSprite(transform, *camera, ColorFade(WHITE,alpha), windowGH);
	if (isActive) {
		if (Novice::GetNumberOfJoysticks() > 0) {
			Render::DrawSprite(hintTransform, *camera, ColorFade(WHITE, alpha), hintGH[1]);
		} else {
			Render::DrawSprite(hintTransform, *camera, ColorFade(WHITE, alpha), hintGH[0]);
		}
	}

	if (Novice::GetNumberOfJoysticks() > 0) {

		if (input->GetControl(DASH, Press)) {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), controllerTutorialPushGH[1]);
		}

		if (input->GetPress(DIK_E) || input->GetControl(ATTACK, Press)) {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), controllerTutorialPushGH[2]);
		}

		Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), controllerTutorialGH[tutorialCount % 4]);
		
		if (tutorialCount == 0 ||tutorialCount >= 2) {
			if (Length(input->GetControlDir()) > 0) {
				Transform drawStickTransform = transform;
				drawStickTransform.pos += input->GetControlDir() * 4.0f;

				Render::DrawSprite(drawStickTransform, *camera, ColorFade(0xd65a31FF, alpha), controllerTutorialPushGH[0]);
			} else {
				Render::DrawSprite(transform, *camera, ColorFade(0xEEEEEEFF, alpha), controllerTutorialPushGH[0]);
			}
		} else {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), controllerTutorialPushGH[0]);
		}

	} else {

		if (Length(input->GetControlDir()) > 0) {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), keyTutorialPushGH[0]);
		}

		if (input->GetControl(DASH, Press)) {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), keyTutorialPushGH[1]);
		}

		if (input->GetPress(DIK_E) || input->GetControl(ATTACK, Press)) {
			Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), keyTutorialPushGH[2]);
		}

		Render::DrawSprite(transform, *camera, ColorFade(WHITE, alpha), keyTutorialGH[tutorialCount % 4]);
	}
	
}

void ContorolTutorialUI::SetCamera(Camera* set) {
	camera = set;
}

void ContorolTutorialUI::SetPlayer(Player* set) {
	player = set;
}

void ContorolTutorialUI::SetIsInScreen(int set) {
	isInScreeenUI = set;
}

void ContorolTutorialUI::SetEnemyManager(EnemyManager* set) {
	enemyManager = set;
}
