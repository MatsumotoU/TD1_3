#pragma once
#include "Class/Common/MyFileIO.h"
#include "Class/Common/Camera.h"

const int kMapSizeX = 32;
const int kMapSizeY = 32;
const Vector2 kMapChipSize = { 64.0f,64.0f };
const float kMapChipNum = 10;

class Player;

class Mapchip
{
public:

	void SetIsTransition(int* set);

	int GetIsHit(Vector2 pos);
	int GetMapNum(Vector2 pos);

	void LoadMap(std::string setFilePath);
	void SetMap(int setMap[kMapSizeY][kMapSizeX]);
	void Draw(Camera* camera);
	void Update();

private:

	int* isTransition;
	int* isCrear;
	int frameCount;
	int map[kMapSizeY][kMapSizeX];

	MyFileIO file;
};

