#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"
#include "Class/Common/InputManager.h"

class Player;

class ContorolTutorialUI : GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);
	void SetPlayer(Player* set);

private:

	int isInScreeenUI;
	int tutorialCount;

	int windowGH;
	int keyTutorialGH[4];
	int keyTutorialPushGH[3];
	int controllerTutorialGH[4];
	int controllerTutorialPushGH[3];
	int tutorialStep;

	Camera* camera;
	Player* player;

	InputManager* input = InputManager::GetInstance();

};

