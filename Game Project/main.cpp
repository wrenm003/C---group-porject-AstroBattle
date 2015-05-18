#include "Game.h"
#define SDL_main main

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
Game* g_game = 0;

int main(int argc, char *argv[])
{
	Uint32 frameStart, frameTime;
	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init("Astro Battle", 100, 100, 640, 480, false))
	{
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "game closing...\n";
	TheGame::Instance()->clean();

	return 0;
}