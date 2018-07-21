#include "CollisionManager.h"
#include "ColliderComponent.h"

bool CollisionManager::AABB(const SDL_Rect & recA, const SDL_Rect & recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
		return true;

	return false;
}

bool CollisionManager::AABB(const ColliderComponent & colA, const ColliderComponent & colB)
{
	if (CollisionManager::AABB(colA.m_oCollider, colB.m_oCollider))
	{
		std::cout << colA.m_sTag << " hitted " << colB.m_sTag << std::endl;
		return true;
	}
	return false;
}
