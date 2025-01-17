#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"
#include "Class/Common/InputManager.h"

class Player;

class PlayerHpUI:public GameObject
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);
	void SetPlayer(Player* set);

private:
	
	int drawHpCount;
	Camera* camera;
	Player* player;

	int hpGH;
};

