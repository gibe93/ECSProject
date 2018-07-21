#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* m_pTransform;
	SpriteComponent* m_pSprite;
	SDL_Rect m_oTileRect;
	int m_iTileID;
	std::string type;

	TileComponent() {};

	TileComponent(int x, int y, int w, int h, int id)
	{
		m_oTileRect.x = x;
		m_oTileRect.y = y;
		m_oTileRect.w = w;
		m_oTileRect.h = h;
		m_iTileID = id;

		switch (m_iTileID)
		{
		case 0:
			type = "Dirt";
			break;
		case 1:
			type = "Water";
			break;
		case 2:
			type = "Grass";
			break;
		default:
			break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>((float)m_oTileRect.x, (float)m_oTileRect.y, m_oTileRect.w, m_oTileRect.h, 1, 0);
		m_pTransform = &entity->GetComponent<TransformComponent>();
		entity->AddComponent<SpriteComponent>(type);
		m_pSprite = &entity->GetComponent<SpriteComponent>();
	}
};


