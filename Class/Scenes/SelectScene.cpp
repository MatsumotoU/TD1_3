#include "SelectScene.h"
#include "TitleScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"

void SelectScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;
}

void SelectScene::Update() {
}

void SelectScene::Draw() {
}

IScene* SelectScene::GetNextScene() {
	return nullptr;
}
