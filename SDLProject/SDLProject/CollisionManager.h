#pragma once
#include <SDL.h>
class ColliderComponent;

class CollisionManager
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABBdir(const SDL_Rect& recA, const SDL_Rect& recB, bool& isRight, bool& isLeft, bool& isTop,  bool& isBottom);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABBdir(const ColliderComponent& colA, const ColliderComponent& colB, bool& isRight, bool& isLeft, bool& isTop, bool& isBottom);
};
