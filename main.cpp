#include <Novice.h>
#include "Class/Common/InputManager.h"
#include "Class/Scenes/SceneManager.h"

const char kWindowTitle[] = "1309_きりすてメンゴ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 変数宣言
	// キー入力受付クラス呼び出し
	InputManager* input = InputManager::GetInstance();

	// シーンごとの処理用
	SceneManager sceneManager;
	sceneManager.Init();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		///
		/// ↓更新処理ここから
		///

		// キー入力更新処理
		input->Update();

		// シーン処理
		sceneManager.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// シーン描画
		sceneManager.Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (input->GetTriger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
