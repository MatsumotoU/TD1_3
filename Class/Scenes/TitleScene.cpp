#include "TitleScene.h"
#include "SelectScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"

void TitleScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;
}

void TitleScene::Update() {
}

void TitleScene::Draw() {
}

IScene* TitleScene::GetNextScene() {
	return nullptr;
}
