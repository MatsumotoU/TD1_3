#include "SelectScene.h"
#include "TitleScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"

void SelectScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	mainCamera.Init();

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	// 
	star[0][0];
	stageIcon[0];
}

void SelectScene::Update() {

	particleManager.Update();
}

void SelectScene::Draw() {

	particleManager.Draw();
}

IScene* SelectScene::GetNextScene() {
	return nullptr;
}
