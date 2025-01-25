#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"
#include "Class/Common/InputManager.h"

class Player;
class EnemyManager;

class ContorolTutorialUI :public GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);
	void SetPlayer(Player* set);
	void SetIsInScreen(int set);
	void SetEnemyManager(EnemyManager* set);

private:

	int frameCount;

	Transform hintTransform;
	float alpha;

	int isHideUI;
	int isInScreeenUI;
	int tutorialCount;

	int hintGH[2];
	int windowGH;
	int keyTutorialGH[4];
	int keyTutorialPushGH[3];
	int controllerTutorialGH[4];
	int controllerTutorialPushGH[3];
	int tutorialStep;

	Camera* camera;
	Player* player;
	EnemyManager* enemyManager;

	InputManager* input = InputManager::GetInstance();

};

