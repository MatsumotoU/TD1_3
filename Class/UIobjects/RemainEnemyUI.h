#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"
#include "Class/Common/InputManager.h"

class EnemyManager;

class RemainEnemyUI:public GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetEnemyManager(EnemyManager* set);

private:

	EnemyManager* enemyManager;

};

