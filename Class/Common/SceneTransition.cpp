#include "SceneTransition.h"

#include <Novice.h>
#include <math.h>
#include <algorithm>

void SceneTransition::Init() {
	transitionTime = 0;
	transitionType = 0;
	transitionEndTime = 30;

	for (int i = 0; i < 3; ++i) {
		t[i] = 0.0f;
	}

	cnt = 1;

	playSEHandle[0] = -1;
	playSEHandle[1] = -1;

	frameCount = 0;

	isTransition = false;
	isTransitionClosed = false;

	mainCamera.Init();
	particle.Init();
	particle.SetCamera(&mainCamera);

	Vector2* cameraPos;
	cameraPos = mainCamera.GetPosPtr();
	*cameraPos = { 640.0f,360.0f };

	shutterGraphHandle = Novice::LoadTexture("./Resources/Images/shutter.png");

	sEHandle[0] = Novice::LoadAudio("./Resources/Sounds/shutterM.mp3");
	sEHandle[1] = Novice::LoadAudio("./Resources/Sounds/shutterC.mp3");
}

void SceneTransition::Update() {

	if (isTransition) {
		switch (transitionType) {
			case 0:
				if (isTransitionClosed) {
					if (transitionTime <= transitionEndTime) {
						transitionTime++;

						if (transitionTime == 1) {
							if (!Novice::IsPlayingAudio(playSEHandle[0]) || playSEHandle[0] == -1) {
								playSEHandle[0] = Novice::PlayAudio(sEHandle[0], false, 0.7f);
							}
						}

						if (transitionTime >= 29) {
							Novice::SetAudioVolume(playSEHandle[0], 0.0f);
							Novice::StopAudio(playSEHandle[0]);
						}


						for (int i = 0; i < cnt; ++i) {
							t[i] += 1.0f / 30.0f;
							t[i] = std::clamp(t[i], 0.0f, 1.0f);
						}

						if (transitionTime == 28) {
							playSEHandle[1] = Novice::PlayAudio(sEHandle[1], false, 0.7f);
						}

					} else {

						if (isTransition) {
							transitionTime = 0;
							transitionType = 0;
							transitionEndTime = 30;

							for (int i = 0; i < 3; ++i) {
								t[i] = 0.0f;
							}

							cnt = 1;

							isTransition = false;
							isTransitionClosed = false;

							playSEHandle[0] = -1;
							playSEHandle[1] = -1;

							Novice::SetAudioVolume(playSEHandle[0], 0.0f);
							Novice::StopAudio(playSEHandle[0]);
						}
					}

				} else {

					if (transitionTime <= transitionEndTime) {
						transitionTime++;

						for (int i = 0; i < cnt; ++i) {
							t[i] += 1.0f / 25.0f;
							t[i] = std::clamp(t[i], 0.0f, 1.0f);
						}

						if (transitionTime == 1) {
							if (!Novice::IsPlayingAudio(playSEHandle[0]) || playSEHandle[0] == -1) {
								playSEHandle[0] = Novice::PlayAudio(sEHandle[0], false, 0.7f);
							}
						}

						if (transitionTime >= 24) {
							Novice::SetAudioVolume(playSEHandle[0], 0.0f);
							Novice::StopAudio(playSEHandle[0]);
						}

						if (transitionTime == 23) {
							playSEHandle[1] = Novice::PlayAudio(sEHandle[1], false, 0.7f);
						}

					} else {

						if (!isTransitionClosed) {
							isTransitionClosed = true;
							transitionTime = 0;
							transitionEndTime = 30;
							for (int i = 0; i < 3; ++i) {
								t[i] = 0.0f;
							}

							Novice::SetAudioVolume(playSEHandle[0], 0.0f);
							Novice::StopAudio(playSEHandle[0]);
						}
					}
				}

				break;
			case 1:
				if (isTransitionClosed) {
					if (transitionTime <= transitionEndTime) {
						transitionTime++;

						for (int i = 0; i < cnt; ++i) {
							t[i] += 1.0f / static_cast<float>(transitionEndTime);
							t[i] = std::clamp(t[i], 0.0f, 1.0f);
						}

					} else {

						if (isTransition) {
							Init();
						}
					}

				} else {

					if (transitionTime <= transitionEndTime) {
						transitionTime++;

						if (transitionTime % (transitionEndTime / 3) == 0) {
							cnt++;
							cnt = std::clamp(cnt, 0, 3);
						}

						for (int i = 0; i < cnt; ++i) {
							t[i] += 1.0f / static_cast<float>((transitionEndTime / 3));
							t[i] = std::clamp(t[i], 0.0f, 1.0f);
						}

					} else {

						if (!isTransitionClosed) {
							isTransitionClosed = true;
							transitionTime = 0;
							cnt = 1;
							transitionEndTime = 10;
							for (int i = 0; i < 3; ++i) {
								t[i] = 0.0f;
							}
						}
					}
				}

				break;
		}
	}

	particle.Update();
}

void SceneTransition::Draw() {

	if (isTransition) {

		if (isTransitionClosed) {
			switch (transitionType) {
				case 0:
					Novice::DrawSprite(0, static_cast<int>(Eas::EaseOut(t[0], 2.0f, 0.0f, -720.0f)), shutterGraphHandle, 1.0f, 1.0f, 0.0f, 0xffffffff);
					break;
				case 1:
					Novice::DrawBox(static_cast<int>(Eas::EaseInOutQuart(t[0], 0.0f, 1280.0f)), 0, static_cast<int>(Eas::EaseInOutQuart(t[1], 1280.0f, 0.0f)), 720, 0.0f, Pal::kGRAY, kFillModeSolid);
					break;
			}

		} else {
			switch (transitionType) {
				case 0:
					Novice::DrawSprite(0, static_cast<int>(Eas::EaseIn(t[0], 3.0f, -720.0f, 0.0f)), shutterGraphHandle, 1.0f, 1.0f, 0.0f, 0xffffffff);
					break;

				case 1:
					Novice::DrawBox(0, 0, static_cast<int>(Eas::EaseInOutQuart(t[0], 0.0f, 1280.0f)), 720, 0.0f, Pal::kWHITE, kFillModeSolid);
					Novice::DrawBox(0, 0, static_cast<int>(Eas::EaseInOutQuart(t[1], 0.0f, 1280.0f)), 720, 0.0f, Pal::kORANGE, kFillModeSolid);
					Novice::DrawBox(0, 0, static_cast<int>(Eas::EaseInOutQuart(t[2], 0.0f, 1280.0f)), 720, 0.0f, Pal::kGRAY, kFillModeSolid);
					break;
			}
		}
	}

	particle.Draw();

#if _DEBUG
	//Novice::ScreenPrintf(0, 20, "SceneTransition = isT:%d isTC%d", isTransition, isTransitionClosed);
	//Novice::ScreenPrintf(0, 64, "SceneTransition = count:%d", frameCount);
#endif
}

void SceneTransition::SetIsTransition(int setIsTransition) {
	isTransition = setIsTransition;
}

int SceneTransition::GetIsTransition() {
	return isTransition;
}

int SceneTransition::GetIsTransitionClosed() {
	return isTransitionClosed;
}
