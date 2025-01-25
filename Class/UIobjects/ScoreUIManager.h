#pragma once
#include "GameScore.h"

const int gameScoreArraySize = 128;

class ScoreUIManager
{
public:

	ScoreUIManager();

	void Init();
	void Update();
	void Draw();

	void SetCamera(Camera* set);

	void SpawnScore(Vector2 pos, int score);

private:

	int plusGH;
	int scoreGH[10];
	GameScore gameScores[gameScoreArraySize];

};

