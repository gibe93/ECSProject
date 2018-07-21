#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include "AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *m_pTransform;
	SDL_Texture* m_pTexture;
	SDL_Rect m_oSrcRect, m_oDestRect;

	bool m_bAnimated = false;
	int m_iFrames = 0;
	int m_iSpeed = 100;

public:
	
	std::map<const char*, std::function<bool()>> m_vAnimationTextures;

	SDL_RendererFlip m_oSpiteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string textID)
	{
		SetTex(textID);
	}
	SpriteComponent(std::string textID, int nFrames, int speed)
	{
		SetTex(textID, true);
		m_iFrames = nFrames;
		m_iSpeed = speed;
	}
	~SpriteComponent()
	{
	}

	void SetTex(std::string textID, bool isAnimated = false)
	{
		m_pTexture = Game::assets->GetTexture(textID);
		m_bAnimated = isAnimated;
	}

	void ChangeAnimation(std::string textID, int nFrames, int speed)
	{
		SetTex(textID, true);
		m_iFrames = nFrames;
		m_iSpeed = speed;
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
		if (m_bAnimated)
		{
			m_oSrcRect.x = m_oSrcRect.w * static_cast<int>((SDL_GetTicks() / m_iSpeed % m_iFrames));
		}

		m_oDestRect.x = (int)m_pTransform->m_oPosition.x;
		m_oDestRect.y = (int)m_pTransform->m_oPosition.y;
		m_oDestRect.w = m_pTransform->m_iWidth * m_pTransform->m_iScale;
		m_oDestRect.h = m_pTransform->m_iHeight *  m_pTransform->m_iScale;
	}

	void Draw() override
	{
		TextureManager::Draw(m_pTexture, m_oSrcRect, m_oDestRect, m_oSpiteFlip);
	}
};