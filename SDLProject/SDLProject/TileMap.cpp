#include "TileMap.h"
#include "TextureManager.h"

int testMap[20][20] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

};

TileMap::TileMap()
{
	m_pTypeZero = TextureManager::LoadTexture("assets/dirt.png");
	m_pTypeOne = TextureManager::LoadTexture("assets/grass.png");
	m_pTypeTwo = TextureManager::LoadTexture("assets/water.png");

	LoadMap(testMap);

	m_oSrc.x = m_oDest.x = 0;
	m_oSrc.y = m_oDest.y = 0;
	m_oSrc.h = m_oDest.h = 32;
	m_oSrc.w = m_oDest.w = 32;

	
}


TileMap::~TileMap()
{
}

void TileMap::LoadMap(int arr[20][20])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 20; column++)
		{
			m_oMap[row][column] = arr[row][column];
		}
	}
}

void TileMap::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 20; column++)
		{
			type = m_oMap[row][column];

			m_oDest.x = column * 32;
			m_oDest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(m_pTypeZero, m_oSrc, m_oDest);
				break;
			case 1:
				TextureManager::Draw(m_pTypeOne, m_oSrc, m_oDest);
				break;
			case 2:
				TextureManager::Draw(m_pTypeTwo, m_oSrc, m_oDest);
				break;
			default:
				break;
			}
		}
	}
}
