#include "ScoreUIManager.h"

ScoreUIManager::ScoreUIManager() {
	scoreGH[0] = Novice::LoadTexture("./Resources/Images/num32x32.png");
	scoreGH[1] = Novice::LoadTexture("./Resources/Images/num32x33.png");
	scoreGH[2] = Novice::LoadTexture("./Resources/Images/num32x34.png");
	scoreGH[3] = Novice::LoadTexture("./Resources/Images/num32x35.png");
	scoreGH[4] = Novice::LoadTexture("./Resources/Images/num32x36.png");
	scoreGH[5] = Novice::LoadTexture("./Resources/Images/num32x37.png");
	scoreGH[6] = Novice::LoadTexture("./Resources/Images/num32x38.png");
	scoreGH[7] = Novice::LoadTexture("./Resources/Images/num32x39.png");
	scoreGH[8] = Novice::LoadTexture("./Resources/Images/num32x40.png");
	scoreGH[9] = Novice::LoadTexture("./Resources/Images/num32x41.png");

	plusGH = Novice::LoadTexture("./Resources/Images/plus.png");

	for (int i = 0; i < gameScoreArraySize; i++) {
		gameScores[i].SetGH(scoreGH);
		gameScores[i].SetPlusGH(&plusGH);
	}
}

void ScoreUIManager::Init() {
	
	for (int i = 0; i < gameScoreArraySize; i++) {
		gameScores[i].Init();
	}
}

void ScoreUIManager::Update() {
	for (int i = 0; i < gameScoreArraySize; i++) {
		if (gameScores[i].GetIsActive()) {
			gameScores[i].Update();
		}
	}
}

void ScoreUIManager::Draw() {
	for (int i = 0; i < gameScoreArraySize; i++) {
		if (gameScores[i].GetIsActive()) {
			gameScores[i].Draw();
		}
	}
}

void ScoreUIManager::SetCamera(Camera* set) {
	for (int i = 0; i < gameScoreArraySize; i++) {
		gameScores[i].SetCamera(set);
	}
}

void ScoreUIManager::SpawnScore(Vector2 pos, int score) {
	for (int i = 0; i < gameScoreArraySize; i++) {
		if (!gameScores[i].GetIsActive()) {
			gameScores[i].Init();
			gameScores[i].SetPos(pos);
			gameScores[i].SetScore(score);
			gameScores[i].SetGroundPos(pos);
			gameScores[i].GetPhysics()->AddForce({ Random(-5.0f,5.0f),Random(10.0f,20.0f) }, IMPACT);
			gameScores[i].SetIsActive(true);
			return;
		}
	}
}
