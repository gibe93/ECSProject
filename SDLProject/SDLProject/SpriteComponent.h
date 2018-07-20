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
	~SpriteComponent()
	{
		SDL_DestroyTexture(m_pTexture);
	}

	void SetTex(const char* path)
	{
		m_pTexture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		m_pTransform = &entity->GetComponent<TransformComponent>();


		m_oSrcRect.x = m_oSrcRect.y = 0;
		m_oSrcRect.w = m_pTransform->m_iWidth;
		m_oSrcRect.h = m_pTransform->m_iHeight;
	}

	void Update() override
	{
		m_oDestRect.x = (int)m_pTransform->m_oPosition.x;
		m_oDestRect.y = (int)m_pTransform->m_oPosition.y;
		m_oDestRect.w = m_pTransform->m_iWidth * m_pTransform->m_iScale;
		m_oDestRect.h = m_pTransform->m_iHeight *  m_pTransform->m_iScale;
	}

	void Draw() override
	{
		TextureManager::Draw(m_pTexture, m_oSrcRect, m_oDestRect);
	}
};