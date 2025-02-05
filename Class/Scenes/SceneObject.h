#pragma once
#include "Class/Common/SimpleJson.h"

class SceneObject
{
public:

	SceneObject();

	void SaveScore();

	int score;
	int isNotDeathClear;
	int shouldClearedMission[3][3];
	int gameStage;

	int stageHighScore[3];

	int targetScore[3];

private:

	SJN::json scoreData;
	std::string highScoreFp = "Resources/GlobalVariables/Score.json";

};

