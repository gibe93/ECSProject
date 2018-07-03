#pragma once
#include "Game.h"

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

	void LoadMap(int arr[20][20]);
	void DrawMap();

private:
	SDL_Rect m_oSrc;
	SDL_Rect m_oDest;

	SDL_Texture* m_pTypeZero;
	SDL_Texture* m_pTypeOne;
	SDL_Texture* m_pTypeTwo;

	int m_oMap[20][20];
};

