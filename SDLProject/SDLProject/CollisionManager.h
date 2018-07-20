#pragma once
#include <SDL.h>

class CollisionManager
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};