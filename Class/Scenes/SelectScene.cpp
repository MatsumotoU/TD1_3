#define _USE_MATH_DEFINES
#include "SelectScene.h"
#include "TitleScene.h"
#include "GameStageScene.h"
#include "ResultScene.h"
#include "math.h"

#include "Class/Common/Render.h"
#include "Class/Common/MyEasing.h"

void SelectScene::Init() {
	frameCount = 0;
	isTransition = false;
	gameStage = 0;

	mainCamera.Init();

	particleManager.Init();
	particleManager.SetCamera(&mainCamera);

	// ミッションの星の変数
	for (int i = 0; i < starTotalCount; ++i) {
		star[i] = {
			{ 320.0f + i * 320.0f, 560.0f }, // 位置
			{ 256.0f, 256.0f }, // 大きさ
			{ 1.0f, -1.0f }, // 比率
			0.0f // 角度
		};

		isStarMoving[i] = false;
		starT[i] = 0.0f;
	}

	// ステージアイコンの変数
	for (int i = 0; i < stageTotalCount; ++i) {
		stageIcon[i] = {
			{ 640.0f + i * 640.0f, 256.0f },
			{ 256.0f, 256.0f },
			{ 1.0f, 1.0f },
			0.0f
		};

		stageIconT[i] = 0.0f;
	}

	// ミッションをクリアしたか
	for (int i = 0; i < stageTotalCount; ++i) {
		for (int j = 0; j < starTotalCount; ++j) {
			shouldClearedMission[i][j] = true;
		}
	}

	// 左右キーを押したときステージアイコンなどが動く時間
	movingFrameCount = 20.0f;

	shouldPressedRight = false;
	shouldPressedLeft = false;

	cameraPos = mainCamera.GetPosPtr();
	*cameraPos = { 640.0f,360.0f };

	starGraphHandle = Novice::LoadTexture("./Resources/Images/missionStar.png");


}

void SelectScene::Update() {

	if (input->GetControl(RIGHT, Press)) {
		if (!shouldPressedRight) {
			if (!shouldPressedLeft) {
				if (gameStage < stageTotalCount - 1) {
					gameStage++;
					shouldPressedRight = true;
					for (int i = 0; i < starTotalCount; ++i) {
						starT[i] = 0.0f;
						isStarMoving[i] = true;
					}

					for (int i = 0; i < stageTotalCount; ++i) {
						stageIconT[i] = 0.0f;
					}
				}
			}
		}
	}

	if (input->GetControl(LEFT, Press)) {
		if (!shouldPressedRight) {
			if (!shouldPressedLeft) {
				if (gameStage > 0) {
					gameStage--;
					shouldPressedLeft = true;
					for (int i = 0; i < starTotalCount; ++i) {
						starT[i] = 0.0f;
						isStarMoving[i] = true;
					}

					for (int i = 0; i < stageTotalCount; ++i) {
						stageIconT[i] = 0.0f;
					}
				}
			}
		}
	}

	// 決定キーを押してシーンを遷移させる
	if (input->GetControl(ENTER, Triger)) {
		// ステージに遷移する
		nextScene = new GameStageScene();
		isTransition = true;
	}

	//================================================================
	// ステージアイコンの更新処理
	//================================================================

	// ステージアイコンの移動
	if (shouldPressedRight) {
		for (int i = 0; i < stageTotalCount; ++i) {
			// tに値を加算
			if (stageIconT[i] < 1.0f) {
				stageIconT[i] += 1.0f / movingFrameCount;
			}

			if (stageIconT[i] >= 1.0f) {
				stageIconT[i] = 1.0f;
				shouldPressedRight = false;
			}

			stageIcon[i].pos.x =
				Eas::EaseInOutQuart(
					stageIconT[i],
					(640.0f * stageTotalCount - (gameStage + 1.0f) * 640.0f) + (i * 640.0f),
					(640.0f * stageTotalCount - (gameStage + 2.0f) * 640.0f) + (i * 640.0f)
				);
		}
	}

	if (shouldPressedLeft) {
		for (int i = 0; i < stageTotalCount; ++i) {
			// tに値を加算
			if (stageIconT[i] < 1.0f) {
				stageIconT[i] += 1.0f / movingFrameCount;
			}

			if (stageIconT[i] >= 1.0f) {
				stageIconT[i] = 1.0f;
				shouldPressedLeft = false;
			}

			stageIcon[i].pos.x =
				Eas::EaseInOutQuart(
					stageIconT[i],
					(640.0f * stageTotalCount - (gameStage + 3.0f) * 640.0f) + (i * 640.0f),
					(640.0f * stageTotalCount - (gameStage + 2.0f) * 640.0f) + (i * 640.0f)
				);
		}
	}

	//================================================================
	// 星の更新処理
	//================================================================

	for (int i = 0; i < stageTotalCount; ++i) {
		for (int j = 0; j < starTotalCount; ++j) {
			// ミッションをクリアしているか
			if (shouldClearedMission[i][j]) {
				// 星の縮小の処理
				if (isStarMoving[j]) {

					// tに値を加算
					if (starT[j] < 1.0f) {
						starT[j] += 1.0f / 20.0f;
					}

					if (starT[j] >= 1.0f) {
						starT[j] = 1.0f;

						if (isStarMoving[j]) {
							isStarMoving[j] = false;
						}
					}

					star[j].scale.x = Eas::EaseInOutQuart(starT[j], 10.0f, 1.0f);
					star[j].scale.y = Eas::EaseInOutQuart(starT[j], 10.0f, 1.0f);
				}
			}
		}
	}

	particleManager.Update();
}

void SelectScene::Draw() {
	for (int i = 0; i < stageTotalCount; ++i) {
		Render::DrawSprite(stageIcon[i], mainCamera, 0xff0000ff, 0);
	}

	for (int i = 0; i < starTotalCount; ++i) {
		Render::DrawSprite(star[i], mainCamera, 0xffffffff, starGraphHandle);
	}

	particleManager.Draw();
}

IScene* SelectScene::GetNextScene() {
	return nullptr;
}
