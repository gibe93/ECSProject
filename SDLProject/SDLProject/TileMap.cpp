#include "TileMap.h"
#include "Game.h"
#include <fstream>
#include "AStar.h"


TileMap::TileMap()
{	
	m_pAStarGenerator = new Generator();
	m_pAStarGenerator->setHeuristic(Heuristic::manhattan);
	m_pAStarGenerator->setDiagonalMovement(false);
}


TileMap::~TileMap()
{
}

void TileMap::LoadMap(std::string path, int sizeX, int sizeY)
{
	m_pAStarGenerator->setWorldSize({ sizeX, sizeY });
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for(int y=0; y<sizeY;y++)
	{
		for (int x=0;x<sizeX;x++)
		{
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 32, y * 32, m_pAStarGenerator);
			mapFile.ignore();
		}
	}

	mapFile.close();
}


