#include "ContorolTutorialUI.h"
#include "Class/Common/MyEasing.h"
#include "Class/Player/Player.h"

void ContorolTutorialUI::Init() {
	transform = { 0 };
	transform.pos = { -360.0f,240.0f };
	transform.scale = { 1.0f,1.0f };
	transform.size = { 480.0f,192.0f };
	tutorialCount = 0;

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

	isInScreeenUI = true;
	tutorialStep = 0;
}

void ContorolTutorialUI::Update() {

	if (isActive) {
		
		if (player->GetPos().x <= 564.0f && player->GetPos().y >= 64.0f * 25.0f) {
			isInScreeenUI = false;
		} else {
			isInScreeenUI = true;
		}
	} else {
		isInScreeenUI = false;
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

	if (tutorialStep >= 100 && tutorialCount < 3) {
		tutorialCount++;
		tutorialStep = 0;
	}

	if (isInScreeenUI) {
		Eas::SimpleEaseIn(&transform.pos.x, -360.0f, 0.3f);
	} else {
		Eas::SimpleEaseIn(&transform.pos.x, -900.0f, 0.2f);
	}
}

void ContorolTutorialUI::Draw() {

	Render::DrawSprite(transform, *camera, WHITE, windowGH);

	if (Novice::GetNumberOfJoysticks() > 0) {

		if (input->GetControl(DASH, Press)) {
			Render::DrawSprite(transform, *camera, WHITE, controllerTutorialPushGH[1]);
		}

		if (input->GetPress(DIK_E) || input->GetControl(ATTACK, Press)) {
			Render::DrawSprite(transform, *camera, WHITE, controllerTutorialPushGH[2]);
		}

		Render::DrawSprite(transform, *camera, WHITE, controllerTutorialGH[tutorialCount % 4]);
		
		if (tutorialCount == 0 ||tutorialCount >= 3) {
			if (Length(input->GetControlDir()) > 0) {
				Transform drawStickTransform = transform;
				drawStickTransform.pos += input->GetControlDir() * 4.0f;

				Render::DrawSprite(drawStickTransform, *camera, 0xd65a31FF, controllerTutorialPushGH[0]);
			} else {
				Render::DrawSprite(transform, *camera, 0xEEEEEEFF, controllerTutorialPushGH[0]);
			}
		} else {
			Render::DrawSprite(transform, *camera, WHITE, controllerTutorialPushGH[0]);
		}

	} else {

		if (Length(input->GetControlDir()) > 0) {
			Render::DrawSprite(transform, *camera, WHITE, keyTutorialPushGH[0]);
		}

		if (input->GetControl(DASH, Press)) {
			Render::DrawSprite(transform, *camera, WHITE, keyTutorialPushGH[1]);
		}

		if (input->GetPress(DIK_E) || input->GetControl(ATTACK, Press)) {
			Render::DrawSprite(transform, *camera, WHITE, keyTutorialPushGH[2]);
		}

		Render::DrawSprite(transform, *camera, WHITE, keyTutorialGH[tutorialCount % 4]);
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
