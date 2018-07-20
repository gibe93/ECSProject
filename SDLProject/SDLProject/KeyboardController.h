#pragma once
#include "Game.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* m_pTransform;

	void Init() override
	{
		m_pTransform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				m_pTransform->m_oVelocity.y = -1;
				break;
			case SDLK_s:
				m_pTransform->m_oVelocity.y = 1;
				break;
			case SDLK_a:
				m_pTransform->m_oVelocity.x = -1;
				break;
			case SDLK_d:
				m_pTransform->m_oVelocity.x = 1;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				m_pTransform->m_oVelocity.y = 0;
				break;
			case SDLK_s:
				m_pTransform->m_oVelocity.y = 0;
				break;
			case SDLK_a:
				m_pTransform->m_oVelocity.x = 0;
				break;
			case SDLK_d:
				m_pTransform->m_oVelocity.x = 0;
				break;
			default:
				break;
			}
		}
	}
};