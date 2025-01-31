#include "InputManager.h"

//==============================
// キー取得更新処理
//==============================
void InputManager::Update() {

	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	// 各キーの押されている長さ
	for (int i = 0; i < 256; i++) {
		if (GetTriger(i)) {
			keysPushTime[i]++;
		} else {
			keysPushTime[i] = 0;
		}
	}

	controllerManager.Update();
}

//==============================
// 特定のキーが押されていない状態取得
//==============================
int InputManager::GetNone(int key) {

	// 特定のキーが押されていないなら真を返す
	if (keys[key]) {

		return false;

	} else {

		return true;
	}
}

//==============================
// 特定のキーが押された状態取得
//==============================
int InputManager::GetTriger(int key) {

	// 特定のキーが押されたなら真を返す
	if (keys[key] && !preKeys[key]) {

		return true;

	} else {
		return false;
	}

}

//==============================
// 特定のキーが押されている状態取得
//==============================
int InputManager::GetPress(int key) {

	// 特定のキーが押されているなら真を返す
	if (keys[key]) {

		return true;

	} else {

		return false;

	}

}

//==============================
// 特定のキーから離れた状態取得
//==============================
int InputManager::GetRelease(int key) {

	// 特定のキー離れたなら真を返す
	if (!keys[key] && preKeys[key]) {

		return true;

	} else {

		return false;

	}

}

//==============================
// 特定のキー同時押し状態取得
//==============================
int InputManager::GetPressSimultaneous(int key1, int key2) {

	// 特定のキーを同時押しで真を返す
	if (keys[key1] && keys[key2]) {

		return true;

	} else {

		return false;

	}
}

int InputManager::GetControl(ControlKey control, KeyState keyState) {

	int x;
	int y;
	Novice::GetAnalogInputLeft(0, &x, &y);

	switch (keyState)
	{
	case Triger:

			switch (control)
			{
			case RIGHT:
				
				if (keys[DIK_RIGHT] && !preKeys[DIK_RIGHT] ||
					keys[DIK_D] && !preKeys[DIK_D] ||
					x > 0 || Novice::IsTriggerButton(0, kPadButton3)) {

					return true;
				}

				break;

			case LEFT:

				if (keys[DIK_LEFT] && !preKeys[DIK_LEFT] ||
					keys[DIK_A] && !preKeys[DIK_A]||
					x < 0 || Novice::IsTriggerButton(0, kPadButton2)) {

					return true;
				}

				break;

			case UP:

				if (keys[DIK_UP] && !preKeys[DIK_UP] ||
					keys[DIK_W] && !preKeys[DIK_W]||
					y < 0 || Novice::IsTriggerButton(0, kPadButton0)) {

					return true;
				}

				break;

			case DOWN:

				if (keys[DIK_DOWN] && !preKeys[DIK_DOWN] ||
					keys[DIK_S] && !preKeys[DIK_S]||
					y > 0 || Novice::IsTriggerButton(0, kPadButton1)) {

					return true;
				}

				break;

			case ENTER:

				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] ||
					keys[DIK_RETURN] && !preKeys[DIK_RETURN] ||
					keys[DIK_Z] && !preKeys[DIK_Z] || 
					Novice::IsTriggerButton(0, kPadButton10)) {

					return true;
				}

				break;

			case BACK:

				if (keys[DIK_BACKSPACE] && !preKeys[DIK_BACKSPACE] ||
					keys[DIK_X] && !preKeys[DIK_X]
					|| Novice::IsTriggerButton(0, kPadButton11)) {

					return true ;
				}

				break;

			case DASH:

				if (keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT] ||
					keys[DIK_RSHIFT] && !preKeys[DIK_RSHIFT]
					|| Novice::IsTriggerButton(0, kPadButton11)) {

					return true  ;
				}

				break;

			case INVENTRY:

				if (keys[DIK_TAB] && !preKeys[DIK_TAB] ||
					keys[DIK_I] && !preKeys[DIK_I]
					|| Novice::IsTriggerButton(0, kPadButton4)) {

					return true;
				}

				break;

			case JUMP:

				if (keys[DIK_W] && !preKeys[DIK_W] ||
					keys[DIK_SPACE] && !preKeys[DIK_SPACE]
					|| Novice::IsTriggerButton(0, kPadButton10)) {

					return true;
				}

				break;

			case ATTACK:

				if (keys[DIK_Z] && !preKeys[DIK_Z] ||
					keys[DIK_RETURN] && !preKeys[DIK_RETURN]
					|| Novice::IsTriggerButton(0, kPadButton9)) {

					return true ;
				}

				break;

			default:
				break;
			}

		break;

	case Press:

			switch (control)
			{
			case RIGHT:

				if (keys[DIK_RIGHT] || keys[DIK_D] || 
					x > 0 || Novice::IsPressButton(0, kPadButton3)) {

					return true;
				}

				break;

			case LEFT:

				if (keys[DIK_LEFT] || keys[DIK_A] ||
					x < 0 || Novice::IsPressButton(0, kPadButton2)) {

					return true;
				}

				break;

			case UP:

				if (keys[DIK_UP] || keys[DIK_W] ||
					y < 0 || Novice::IsPressButton(0, kPadButton0)) {

					return true;
				}

				break;

			case DOWN:

				if (keys[DIK_DOWN] || keys[DIK_S]||
					y > 0 || Novice::IsPressButton(0, kPadButton1)) {

					return true;
				}

				break;

			case ENTER:

				if (keys[DIK_SPACE] || keys[DIK_RETURN] || keys[DIK_Z]||
					Novice::IsPressButton(0, kPadButton10)) {

					return true;
				}

				break;

			case BACK:

				if (keys[DIK_BACKSPACE] || keys[DIK_X] ||
					Novice::IsPressButton(0, kPadButton11)) {

					return true;
				}

				break;

			case DASH:

				if (keys[DIK_LSHIFT] || keys[DIK_RSHIFT] ||
					Novice::IsPressButton(0, kPadButton11)) {

					return true;
				}

				break;

			case JUMP:

				if (keys[DIK_W] || keys[DIK_SPACE] ||
					Novice::IsPressButton(0, kPadButton10)) {

					return true;
				}

				break;

			case ATTACK:

				if (keys[DIK_Z] && !preKeys[DIK_Z] || keys[DIK_RETURN] ||
					Novice::IsPressButton(0, kPadButton9)) {

					return true;
				}

				break;

				break;
			default:
				break;
			}

		break;

	case Release:

		switch (control)
		{
		case RIGHT:

			if (!keys[DIK_RIGHT] && preKeys[DIK_RIGHT] ||
				!keys[DIK_D] && preKeys[DIK_D]) {

				return true;
			}

			break;

		case LEFT:

			if (!keys[DIK_LEFT] && preKeys[DIK_LEFT] ||
				!keys[DIK_A] && preKeys[DIK_A]) {

				return true;
			}

			break;

		case UP:

			if (!keys[DIK_UP] && preKeys[DIK_UP] ||
				!keys[DIK_W] && preKeys[DIK_W]) {

				return true;
			}

			break;

		case DOWN:

			if (!keys[DIK_DOWN] && preKeys[DIK_DOWN] ||
				!keys[DIK_S] && preKeys[DIK_S]) {

				return true;
			}

			break;

		case ENTER:

			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE] ||
				!keys[DIK_RETURN] && preKeys[DIK_RETURN] ||
				!keys[DIK_Z] && preKeys[DIK_Z]) {

				return true;
			}

			break;

		case BACK:

			if (!keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] ||
				!keys[DIK_X] && preKeys[DIK_X]) {

				return true;
			}

			break;

		case JUMP:

			if (!keys[DIK_W] && preKeys[DIK_W] || 
				!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {

				return true;
			}

			break;

		case ATTACK:

			if (!keys[DIK_Z] && preKeys[DIK_Z] || 
				!keys[DIK_RETURN] && preKeys[DIK_RETURN]) {

				return true;
			}

			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
	return 0;
}

Vector2 InputManager::GetControlDir() {
	Vector2 result = { 0 };

	int x;
	int y;
	Novice::GetAnalogInputLeft(0, &x, &y);
	Vector2 controlerDir = { static_cast<float>(x),static_cast<float>(-y) };
	
	if (GetControl(RIGHT, Press)) {
		result.x += 1.0f;
	}

	if (GetControl(LEFT, Press)) {
		result.x -= 1.0f;
	}

	if (GetControl(UP, Press)) {
		result.y += 1.0f;
	}

	if (GetControl(DOWN, Press)) {
		result.y -= 1.0f;
	}

	if (Length(controlerDir) >= Length(result)) {
		result = controlerDir;
	}

	return Normalize(result);
}

int InputManager::GetPressFrame(int key) {
	return keysPushTime[key];
}

int InputManager::GetNotPressAnyKeys() {
	for (int i = 0; i < 256; i++) {
		if (keysPushTime[i] > 0) {
			return false;
		}
	}
	return true;
}

ControllerManager* InputManager::GetControllerManager() {
	return &controllerManager;
}
