#include "SceneObject.h"

SceneObject::SceneObject() {
	 score = 0;
	 isNotDeathClear = false;

	 for (int i = 0; i < 3; i++) {
		 for (int j = 0; j < 3; j++) {
			 shouldClearedMission[i][j] = false;
		 }
	 }
}
