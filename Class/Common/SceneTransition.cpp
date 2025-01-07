#include "SceneTransition.h"

#include <Novice.h>
#include <math.h>

void SceneTransition::Init() {
	transitionTime = 0;

	isTransition = false;
	isTransitionClosed = false;
}

void SceneTransition::Update() {

	if (isTransition) {

		if (isTransitionClosed) {
			if (transitionTime >= 0) {

				transitionTime--;

			} else {

				if (isTransition) {
					isTransitionClosed = false;
					isTransition = false;
				}
			}

		} else {

			if (transitionTime <= 40) {
				transitionTime++;
			} else {

				if (!isTransitionClosed) {
					isTransitionClosed = true;
				}
			}
		}
	}
}

void SceneTransition::Draw() {

	if (isTransition) {

		if (isTransitionClosed) {

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 8.0f)), 1280, 360, 0.0f, 0x2d2d4f23, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 8.0f)), 1280, 360, 0.0f, 0x2d2d4f23, kFillModeSolid);

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 4.0f)), 1280, 360, 0.0f, 0x2d2d4fAF, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 4.0f)), 1280, 360, 0.0f, 0x2d2d4fAF, kFillModeSolid);

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 2.0f)), 1280, 360, 0.0f, 0x2d2d4fFF, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 2.0f)), 1280, 360, 0.0f, 0x2d2d4fFF, kFillModeSolid);

		} else {

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 8.0f)), 1280, 360, 0.0f, 0x2d2d4f23, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 8.0f)), 1280, 360, 0.0f, 0x2d2d4f23, kFillModeSolid);

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 4.0f)), 1280, 360, 0.0f, 0x2d2d4fAF, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 4.0f)), 1280, 360, 0.0f, 0x2d2d4fAF, kFillModeSolid);

			Novice::DrawBox(0, static_cast<int>(-360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 2.0f)), 1280, 360, 0.0f, 0x2d2d4fFF, kFillModeSolid);
			Novice::DrawBox(0, static_cast<int>(360.0f + 360.0f * powf(1.0f - static_cast<float>(transitionTime) / 30.0f, 2.0f)), 1280, 360, 0.0f, 0x2d2d4fFF, kFillModeSolid);
		}
	}

#if _DEBUG
	//Novice::ScreenPrintf(0, 20, "SceneTransition = isT:%d isTC%d", isTransition, isTransitionClosed);
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
