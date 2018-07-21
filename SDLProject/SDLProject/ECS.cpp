#include "ECS.h"

void Entity::AddGroup(Group mGroup)
{
	m_oGroupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}
