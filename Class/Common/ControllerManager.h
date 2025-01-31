#pragma once
#include <Novice.h>
#include <Xinput.h>

class ControllerManager
{
public:

	ControllerManager();

	void Init();
	void Update();
	
	/// <summary>
	/// controllerを振動させます
	/// </summary>
	/// <param name="lSpeed">左のモーターの速度</param>
	/// <param name="rSpeed">右のモーターの速度</param>
	/// <param name="setVibrationFrame">バイブレーション時間</param>
	void VibrationController(int lSpeed, int rSpeed, int setVibrationFrame);

private:

	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;

	int vibrationFrame;

	int controllerVibrationSpeedX;
	int controllerVibrationSpeedY;

};

