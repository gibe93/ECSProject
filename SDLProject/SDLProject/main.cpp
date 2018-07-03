#include "Game.h"

Game* GameInstance = nullptr;

int main(int argc, const char *args[])
{
	const int FPS = 60;
	const int Fdelay = 1000 / FPS;

	Uint32 FStart;
	int FTime;

	const int windowSizeX = 640;
	const int windowSizeY = 640;
	GameInstance = Game::GetGameInstance();
	GameInstance->Init("SDLProject", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, false);

	while (GameInstance->Running())
	{
		FStart = SDL_GetTicks();

		GameInstance->HandleEvents();
		GameInstance->Update();
		GameInstance->Draw();

		FTime = SDL_GetTicks() - FStart;
		if(Fdelay > FTime)
		{
			SDL_Delay(Fdelay - FTime);
		}
	}

	GameInstance->Clean();
	delete GameInstance;

	return 0;
}