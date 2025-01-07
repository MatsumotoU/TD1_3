#pragma once
#include "Class/Common/InputManager.h"
#include "Class/Common/SceneTransition.h"

#include "IScene.h"

class SceneManager {
public:
	// 初期化と更新と描画
	void Init();
	void Update();
	void Draw();

private:
	int frameCount;
	int gameStage;

	// キー入力受付クラス呼び出し
	InputManager* input = InputManager::GetInstance();

	// シーン管理ポインタ
	IScene* scene;

	SceneTransition sceneTransition;

	int backGroundGraphHandle;

};

