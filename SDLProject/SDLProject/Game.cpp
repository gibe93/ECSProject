#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Components.h"

SDL_Renderer* Game::Renderer = nullptr;
Game* Game::m_pGameInstance = nullptr;
TileMap* Map;


Manager manager;
auto& Player(manager.AddEntity());

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
		
		Player.AddComponent<PositionComponent>();
		Player.AddComponent<SpriteComponent>("assets/hero.png");
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
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
	manager.Update();
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
