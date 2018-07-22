#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "Vector2D.h"

bool CollisionManager::AABB(const SDL_Rect & recA, const SDL_Rect & recB)
{
	bool One = recA.x + recA.w >= recB.x;
	bool Two = recB.x + recB.w >= recA.x;
	bool Three = recA.y + recA.h >= recB.y;
	bool Four = recB.y + recB.h >= recA.y;

	return One && Two && Three && Four;
}

bool CollisionManager::AABB(const ColliderComponent & colA, const ColliderComponent & colB)
{
	return CollisionManager::AABB(colA.m_oCollider, colB.m_oCollider);
}

bool CollisionManager::AABBdir(const SDL_Rect& recA, const SDL_Rect& recB, bool& isRight, bool& isLeft, bool& isTop, bool& isBottom)
{
	bool One = recA.x + recA.w >= recB.x;
	bool Two = recB.x + recB.w >= recA.x;
	bool Three = recA.y + recA.h >= recB.y;
	bool Four = recB.y + recB.h >= recA.y;

	Vector2D recAPos = Vector2D((float)(recA.x + recA.w / 2), (float)(recA.y + recA.h));
	Vector2D recBPos = Vector2D((float)(recB.x + recB.w / 2), (float)(recB.y + recB.h));

	Vector2D dist = (recAPos - recBPos).Abs();

	isRight = recA.x > recB.x + (recB.w * 0.5) && dist.x > dist.y;
	isBottom = recA.y > recB.y + (recB.h * 0.5) && dist.y > dist.x;
	isLeft = recA.x < recB.x + (recB.w * 0.5) && dist.x > dist.y;
	isTop = recA.y < recB.y + (recB.h * 0.5) && dist.y > dist.x;


	return One && Two && Three && Four;
}

bool CollisionManager::AABBdir(const ColliderComponent& colA, const ColliderComponent& colB, bool& isRight, bool& isLeft, bool& isTop, bool& isBottom)
{
	if (colA.m_sTag == colB.m_sTag) return false;

	return CollisionManager::AABBdir(colA.m_oCollider, colB.m_oCollider, isRight, isLeft, isTop, isBottom);
}
