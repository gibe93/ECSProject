#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Components.h"
#include "Vector2D.h"
#include "CollisionManager.h"

Manager manager;
SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::m_vColliders;
Game* Game::m_pGameInstance = nullptr;

auto& Player(manager.AddEntity());

enum GroupLabels: std::size_t
{
	GroupMap,
	GroupPlayers,
	GroupEnemies,
	GroupColliders
};

Game::Game() :
	m_bIsRunning(false),
	m_iUpdateCounter(0)
{

}


Game::~Game()
{

}

void Game::Init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Initialized!" << endl;
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			cout << "SDL Window has been created!" << endl;
		}

		Game::Renderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if (Game::Renderer != nullptr)
		{
			SDL_SetRenderDrawColor(Game::Renderer, 255, 255, 255, 255);
			cout << "SDL Renderer has been created" << endl;
		}

		m_bIsRunning = true;
		
		TileMap::LoadMap("assets/map.txt", 16, 16);

		Player.AddComponent<TransformComponent>(3);
		Player.AddComponent<SpriteComponent>("assets/hero.png");
		Player.AddComponent<KeyboardController>();
		Player.AddComponent<ColliderComponent>("player");
		Player.AddGroup(GroupPlayers);
	}
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_bIsRunning = false;
		break;
	default:
		break;

	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	for (auto cc : m_vColliders)
	{
		CollisionManager::AABB(Player.GetComponent<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.GetGroup(GroupMap));
auto& players(manager.GetGroup(GroupPlayers));
auto& enemies(manager.GetGroup(GroupEnemies));
auto& colliders(manager.GetGroup(GroupColliders));

void Game::Draw()
{
	SDL_RenderClear(Renderer);
	for(auto& t : tiles)
	{
		t->Draw();
	}
	for (auto& p : players)
	{
		p->Draw();
	}	for (auto& e : enemies)
	{
		e->Draw();
	}	
	for (auto& c : colliders)
	{
		c->Draw();
	}
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	cout << "Game has been cleaned and closed" << endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(x, y, 32, 32, id);
	tile.AddGroup(GroupMap);
}
