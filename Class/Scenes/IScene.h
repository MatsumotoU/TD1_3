#pragma once
#include<Novice.h>
#include "Class/Common/InputManager.h"
#include "Class/Common/Render.h"

// 各ゲームシーンの基底クラス
class IScene{
public:

	// コンストラクタとデストラクタ定義
	IScene() = default;
	virtual ~IScene() = default;

	// 初期化と更新と描画
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ゲームシーン取得用
	virtual IScene* GetNextScene() = 0;

	// シーン遷移しようとしてるか取得用
	virtual int GetIsTransition() = 0;

	virtual int GetGameStage() = 0;
	virtual void SetGameStage(int setGameStage) = 0;
	virtual int GetIsContinue() = 0;

protected:

	int frameCount;
	int isTransition;
	int gameStage;
	Camera mainCamera;

	// キー入力受付クラス呼び出し
	InputManager* input = InputManager::GetInstance();
};

