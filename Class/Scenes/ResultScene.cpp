#include "ResultScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameStageScene.h"

void ResultScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;
}

void ResultScene::Update() {
}

void ResultScene::Draw() {
}

IScene* ResultScene::GetNextScene() {
	return nullptr;
}
