#include "ControllerManager.h"
#include "MyMath.h"

ControllerManager::ControllerManager() {

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	controllerVibrationSpeedX = 0;
	controllerVibrationSpeedY = 0;

	vibrationFrame = 0;
}

void ControllerManager::Init() {
	controllerVibrationSpeedX = 0;
	controllerVibrationSpeedY = 0;
}

void ControllerManager::Update() {

	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			// バイブレーション
			if (vibrationFrame > 0) {
				ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
				vibration.wLeftMotorSpeed = static_cast<WORD>(Clamp(controllerVibrationSpeedX, 0, 65535)); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(Clamp(controllerVibrationSpeedY, 0, 65535)); // use any value between 0-65535 here
				XInputSetState(i, &vibration);
			} else {
				vibration.wLeftMotorSpeed = 0;
				vibration.wRightMotorSpeed = 0;
				XInputSetState(i, &vibration);
			}
		}
	}

	if (vibrationFrame > 0) {
		vibrationFrame--;
	}
}

void ControllerManager::VibrationController(int lSpeed, int rSpeed, int setVibrationFrame) {
	controllerVibrationSpeedX = lSpeed;
	controllerVibrationSpeedY = rSpeed;
	vibrationFrame = setVibrationFrame;
}
