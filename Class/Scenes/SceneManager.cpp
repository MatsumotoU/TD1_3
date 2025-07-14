#include "SceneManager.h"

// 各シーン読み込み
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"

//==============================
// 初期化処理
//==============================
void SceneManager::Init() {

	// シーン読み込み
	scene = new TitleScene();
	//scene = new SelectScene();
	//scene = new GameStageScene();
	//scene = new ResultScene();

	scene->SetSceneObj(&sceneObject);
	scene->Init();
	sceneTransition.Init();

	frameCount = 0;
	gameStage = 0;
}

//==============================
// 更新処理
//==============================
void SceneManager::Update() {
	// 
	frameCount++;

	// シーン遷移処理をしているなら更新ストップ
	if (!sceneTransition.GetIsTransition()) {

		// シーン更新処理
		scene->Update();
	}

	if (scene->GetIsTransition()) {

		// シーン遷移演出スタート
		if (!sceneTransition.GetIsTransition()) {
			sceneTransition.SetIsTransition(true);
		}

		// シーンが完全に閉じているか
		if (sceneTransition.GetIsTransitionClosed()) {

			// ゲームシーン共有
			gameStage = scene->GetGameStage();

			// シーン遷移処理
			IScene* temp = scene->GetNextScene();

			// 返り値が別のシーンだったら
			if (temp) {

				// メモリ解放
				delete scene;

				// 現在のシーンを次のシーンへ
				scene = temp;

				scene->SetSceneObj(&sceneObject);

				// 現在のシーンの初期化処理
				scene->Init();

				// ゲームステージ引き継ぎ
				scene->SetGameStage(gameStage);

				scene->Update();
			} else {
				assert(temp != nullptr && "シーン遷移に失敗しました。次のシーンがnullptrです。");
			}
		}
	}

	// シーン遷移演出処理
	if (sceneTransition.GetIsTransition()) {

		sceneTransition.Update();

	}

#if _DEBUG // * デバッグ遷移 * //
	// Iキーが押されたら
	if (input->GetTriger(DIK_I)) {

		// シーン遷移処理
		IScene* temp = scene->GetNextScene();
		assert(temp != nullptr && "シーン遷移に失敗しました。次のシーンがnullptrです。");

		// 返り値が別のシーンだったら
		if (temp) {

			// メモリ解放
			delete scene;

			// 現在のシーンを次のシーンへ
			scene = temp;

			// 現在のシーンの初期化処理
			scene->Init();
		}

		scene->SetSceneObj(&sceneObject);
	}

	// Iキーが押されたら
	if (input->GetTriger(DIK_R)) {

		scene->Init();
	}
#endif

}

//==============================
// 描画処理
//==============================
void SceneManager::Draw() {

	// シーン描画処理
	scene->Draw();

	// シーン遷移演出
	sceneTransition.Draw();

	// * Debug * //
	// シーン番号
	//Novice::ScreenPrintf(0, 0, "Scene");
}
