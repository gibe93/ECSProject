#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *m_pTransform;
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
		m_pTransform = &entity->GetComponent<TransformComponent>();


		m_oSrcRect.x = m_oSrcRect.y = 0;
		m_oSrcRect.w = m_oSrcRect.h = 32;
		m_oDestRect.w = m_oDestRect.h = 64;
	}

	void Update() override
	{
		m_oDestRect.x = (int)m_pTransform->m_oPosition.x;
		m_oDestRect.y = (int)m_pTransform->m_oPosition.y;
	}

	void Draw() override
	{
		TextureManager::Draw(m_pTexture, m_oSrcRect, m_oDestRect);
	}
};