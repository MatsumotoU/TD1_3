#include "TitleScene.h"
#include "SelectScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"

void TitleScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);
}

void TitleScene::Update() {
	particleManager.Update();
}

void TitleScene::Draw() {
	particleManager.Draw();
}

IScene* TitleScene::GetNextScene() {
	return nullptr;
}
