#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Render.h"

#include <string>

class Bullet:public GameObject
{
public:

	Bullet();

	void Init()override;
	void Update()override;
	void Draw()override;

	void Move();
	void Destroy();
	
	void SetIsShot(int set);
	void SetCamera(Camera* set);
	void SetGH(int set);
	void SetTag(std::string set);
	void SetAliveFrame(int set);

	int GetIsShot();
	std::string GetTag();

private:

	int aliveFrame;
	int isShot;
	std::string tag;
	Camera* camera;
	unsigned int color;
	int bulletGH;
};

