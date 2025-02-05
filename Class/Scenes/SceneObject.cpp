#include "SceneObject.h"

SceneObject::SceneObject() {
	 score = 0;
	 isNotDeathClear = false;
	 gameStage = 0;

	 for (int i = 0; i < 3; i++) {
		 for (int j = 0; j < 3; j++) {
			 shouldClearedMission[i][j] = false;
		 }
	 }

	 for (int i = 0; i < 3; i++) {
		 stageHighScore[i] = 0;
	 }
	 
	 scoreData.clear();
	 scoreData = SJN::LoadJsonData(highScoreFp);
	 scoreData.emplace("stage1", 0);
	 scoreData.emplace("stage2", 0);
	 scoreData.emplace("stage3", 0);

	 stageHighScore[0] = static_cast<int>(scoreData["stage1"]);
	 stageHighScore[1] = static_cast<int>(scoreData["stage2"]);
	 stageHighScore[2] = static_cast<int>(scoreData["stage3"]);

	 targetScore[0] = 40000;
	 targetScore[1] = 40000;
	 targetScore[2] = 120000;
}

void SceneObject::SaveScore() {

	scoreData["stage1"] = stageHighScore[0];
	scoreData["stage2"] = stageHighScore[1];
	scoreData["stage3"] = stageHighScore[2];
	SJN::SaveJsonData("Score", scoreData);
}
