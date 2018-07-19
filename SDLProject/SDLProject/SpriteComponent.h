#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	PositionComponent *m_pPosition;
	SDL_Texture* m_pTexture;
	SDL_Rect m_oSrcRect, m_oDestRect;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTex(path);
	}

	void SetTex(const char* path)
	{
		m_pTexture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		m_pPosition = &entity->GetComponent<PositionComponent>();


		m_oSrcRect.x = m_oSrcRect.y = 0;
		m_oSrcRect.w = m_oSrcRect.h = 32;
		m_oDestRect.w = m_oDestRect.h = 64;
	}

	void Update() override
	{
		m_oDestRect.x = m_pPosition->X();
		m_oDestRect.y = m_pPosition->Y();
	}

	void Draw() override
	{
		TextureManager::Draw(m_pTexture, m_oSrcRect, m_oDestRect);
	}
};