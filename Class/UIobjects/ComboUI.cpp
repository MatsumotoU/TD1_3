#include "ComboUI.h"
#include "Class/Common/MyEasing.h"
#include "Class/Scenes/GameStageScene.h"

ComboUI::ComboUI() {
	camera = nullptr;
	combo = nullptr;
	remainFrame = nullptr;
	maxRemainFrame = static_cast<float>(GMScene::maxComboRemainFrame);
}

void ComboUI::Init() {
	isActive = false;
	transform = { 0.0f,-480.0f };
	transform.scale = { 1.0f,1.0f };
	transform.size = { 800.0f,64.0f };
	transform.angle = 0.0f;
	comboCount.Init();
	comboCount.SetPos(transform.pos);
	comboCount.SetSize({ 128.0f,128.0f });

	comboRamainFrameTransform = transform;
	crossTransform = transform;

	comboNumGH[0] = Novice::LoadTexture("./Resources/Images/Number1.png");
	comboNumGH[1] = Novice::LoadTexture("./Resources/Images/Number2.png");
	comboNumGH[2] = Novice::LoadTexture("./Resources/Images/Number3.png");
	comboNumGH[3] = Novice::LoadTexture("./Resources/Images/Number4.png");
	comboNumGH[4] = Novice::LoadTexture("./Resources/Images/Number5.png");
	comboNumGH[5] = Novice::LoadTexture("./Resources/Images/Number6.png");
	comboNumGH[6] = Novice::LoadTexture("./Resources/Images/Number7.png");
	comboNumGH[7] = Novice::LoadTexture("./Resources/Images/Number8.png");
	comboNumGH[8] = Novice::LoadTexture("./Resources/Images/Number9.png");
	comboNumGH[9] = Novice::LoadTexture("./Resources/Images/Number10.png");

	crossGH = Novice::LoadTexture("./Resources/Images/X64x64.png");
}

void ComboUI::Update() {

	if (*remainFrame > 0) {
		isActive = true;
	} else {
		isActive = false;
	}

	comboCount.SetPos(transform.pos);
	comboCount.SetScale(transform.scale);
	comboCount.SetTargetNum(*combo);
	comboCount.Update();

	comboRamainFrameTransform = transform;
	comboRamainFrameTransform.size = { 800.0f * (static_cast<float>(*remainFrame) / maxRemainFrame),64.0f };

	crossTransform = transform;
	crossTransform.size = { 64.0f,64.0f };
	crossTransform.pos.x -= (64.0f * static_cast<float>(comboCount.GetDigit()));

	if (isActive) {
		Eas::SimpleEaseIn(&transform.pos.y, -280.0f, 0.1f);
	} else {
		Eas::SimpleEaseIn(&transform.pos.y, -480.0f, 0.1f);
	}
}

void ComboUI::Draw() {
	Render::DrawBox(comboRamainFrameTransform, *camera, 0xFFFFFF23, kFillModeSolid);
	Render::DrawBox(transform, *camera, 0xFFFFFF23, kFillModeWireFrame);
	Render::DrawSprite(crossTransform, *camera, WHITE, crossGH);
	comboCount.Draw(camera, comboNumGH);
}

void ComboUI::SetCamera(Camera* set) {
	camera = set;
}

void ComboUI::SetCombo(int* setCombo, int* setRemainFrame) {
	combo = setCombo;
	remainFrame = setRemainFrame;
}
