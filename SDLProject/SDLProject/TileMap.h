#pragma once
#include "Game.h"

class Generator;

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();
	Generator* m_pAStarGenerator;

	void LoadMap(std::string path, int sizeX, int sizeY);


private:

};

