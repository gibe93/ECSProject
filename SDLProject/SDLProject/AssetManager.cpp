#include "AssetManager.h"


AssetManager::AssetManager(Manager * man)
{
	m_pManager = man;
}

AssetManager::~AssetManager()
{
}

void AssetManager::AddTexture(std::string id, const char * path)
{
	m_vTextures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture * AssetManager::GetTexture(std::string id)
{
	return m_vTextures[id];
}
