#pragma once
#include "SDL.h"
#include "SDL_image.h"
#undef main
#include <iostream>
#include <memory>
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
	void Draw();
	void Clean();

	bool Running() { return m_bIsRunning; }

	static SDL_Renderer* Renderer;

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

