#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect m_oCollider;
	std::string m_sTag;

	TransformComponent* m_pTransform;

	ColliderComponent(const std::string& tag)
	{
		m_sTag = tag;
	}

	void Init() override
	{
		if(!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		m_pTransform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		m_oCollider.x = static_cast<int>(m_pTransform->m_oPosition.x);
		m_oCollider.y = static_cast<int>(m_pTransform->m_oPosition.y);
		m_oCollider.w = m_pTransform->m_iWidth * m_pTransform->m_iScale;
		m_oCollider.h = m_pTransform->m_iHeight * m_pTransform->m_iScale;
	}
};