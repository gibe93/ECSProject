#include "Game.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "TileMap.h"
#include "Components.h"
#include "Vector2D.h"

TileMap* Map;
Manager manager;
SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::event;
Game* Game::m_pGameInstance = nullptr;

auto& Player(manager.AddEntity());
auto& Wall(manager.AddEntity());

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
		Map = new TileMap();

		Player.AddComponent<TransformComponent>(3);
		Player.AddComponent<SpriteComponent>("assets/hero.png");
		Player.AddComponent<KeyboardController>();
		Player.AddComponent<ColliderComponent>("player");

		Wall.AddComponent<TransformComponent>(200.0f, 200.0f, 300, 20, 1);
		Wall.AddComponent<SpriteComponent>("assets/grass.png");
		Wall.AddComponent<ColliderComponent>("wall");
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
	if (CollisionManager::AABB(Player.GetComponent<ColliderComponent>().m_oCollider,
		                       Wall.GetComponent<ColliderComponent>().m_oCollider))
	{
		cout << "wall hit" << endl;
	}
}

void Game::Draw()
{
	SDL_RenderClear(Renderer);
	Map->DrawMap();
	manager.Draw();
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	cout << "Game has been cleaned and closed" << endl;
}
