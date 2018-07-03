#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	virtual ~GameObject();

	void Update();
	void Draw();

private:

	int m_iXpos;
	int m_iYpos;

	SDL_Texture* m_pTextureObj;
	SDL_Rect m_oSrcRect;
	SDL_Rect m_oDestRect;

};

