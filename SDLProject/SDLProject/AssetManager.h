#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	Manager* m_pManager;
	std::map<std::string, SDL_Texture*> m_vTextures;
};

