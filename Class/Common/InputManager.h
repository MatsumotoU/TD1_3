#pragma once
#include <Novice.h>
#include "Class/Common/MyMath.h"
#include "ControllerManager.h"

enum ControlKey {
	RIGHT,
	LEFT,
	UP,
	DOWN,
	ENTER,
	BACK,
	DASH,
	INVENTRY,
	JUMP,
	ATTACK
};

enum KeyState {
	Triger,
	Press,
	Release,
};

class InputManager {
public:

	//	シングルトン
	static InputManager* GetInstance() {
		static InputManager instance;
		return &instance;
	}

	// キー取得更新処理
	void Update();

	int GetNone(int key);
	int GetTriger(int key);
	int GetPress(int key);
	int GetRelease(int key);
	int GetPressSimultaneous(int key1, int key2);

	/// <summary>
	/// 汎用キーまとめ変数
	/// </summary>
	/// <param name="control">操作の種類</param>
	/// <param name="keyState">判定方法</param>
	/// <returns>押されている ＝ true</returns>
	int GetControl(ControlKey control, KeyState keyState);

	/// <summary>
	/// 入力方向取得
	/// </summary>
	/// <returns>入力方向0~1を返す</returns>
	Vector2 GetControlDir();

	/// <summary>
	/// 任意のキーが押されているフレーム取得
	/// </summary>
	/// <param name="key">任意のキー</param>
	/// <returns>連続して押されている長さ(フレーム)</returns>
	int GetPressFrame(int key);

	/// <summary>
	/// どこも押されていないかどうかを取得
	/// </summary>
	/// <returns>押されていないならtrueを返す</returns>
	int GetNotPressAnyKeys();

	ControllerManager* GetControllerManager();

private:
	// キー入力の長さを取得する
	int keysPushTime[256] = { 0 };

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	ControllerManager controllerManager;

	// コンストラクタをプライベートに
	InputManager() = default;
	~InputManager() = default;

	// * おまじない * //
	// コピーコンストラクタを削除
	InputManager(const InputManager&) = delete;
	// コピー代入演算子を削除
	InputManager& operator=(const InputManager&) = delete;
};

