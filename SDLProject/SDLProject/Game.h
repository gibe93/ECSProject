#pragma once
#include "SDL.h"
#include "SDL_image.h"
#undef main
#include <iostream>
#include <memory>
#include <vector>

class AssetManager;
class ColliderComponent;
class Entity;
class Generator;
class TileComponent;
using namespace std;

class Game
{
public:
	~Game();
	static Game* GetGameInstance()
	{
		if (m_pGameInstance == nullptr)
			m_pGameInstance = new Game();
		return m_pGameInstance;
	};

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();

	void CheckEntityCollisions(Entity* e);

	void Draw();
	void Clean();

	bool Running() { return m_bIsRunning; }

	static void AddTile(int id, int x, int y, Generator* g);
	static SDL_Renderer* Renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> m_vColliders;
	static AssetManager* assets;

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	
protected:
	static Game* m_pGameInstance;
	
private:
	Game();

	int m_iUpdateCounter;
	bool m_bIsRunning;
	SDL_Window* m_pWindow;

};

