#pragma once
#include "Game.h"

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

	static void LoadMap(std::string path, int sizeX, int sizeY);


private:

};

