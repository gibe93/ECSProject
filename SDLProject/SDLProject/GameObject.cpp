#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char * textureSheet, int x, int y)
{
	m_pTextureObj = TextureManager::LoadTexture(textureSheet);

	m_iXpos = x;
	m_iYpos = y;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	
	m_oSrcRect.h = 32;
	m_oSrcRect.w = 32;
	m_oSrcRect.x = 0;
	m_oSrcRect.y = 0;

	m_oDestRect.x = m_iXpos;
	m_oDestRect.y = m_iYpos;
	m_oDestRect.w = m_oSrcRect.w;
	m_oDestRect.h = m_oSrcRect.h;
	
}

void GameObject::Draw()
{
	SDL_RenderCopy(Game::Renderer, m_pTextureObj, &m_oSrcRect, &m_oDestRect);
}
