#include "Game.h"
#include <SDL_image.h>
#include <iostream>
#include "MainMenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "TextManager.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	//init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL init success\n";
		//if succeeded, create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if the window creation succeeded, create window
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl could not init
	}
	std::cout << "init success\n";
	m_bRunning = true;
	m_gameWidth = width;
	m_gameHeight = height;
	
	m_pGameStateMachine = new GameStateMachine();
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("Bullet", new BulletCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	m_pGameStateMachine->changeState(new MainMenuState());
	TheTextureManager::Instance()->load("assets/back.jpg", "background", TheGame::Instance()->getRenderer());
	scores.push_back(9);
	scores.push_back(9);
	return true;
}
void Game::update()
{
	m_pGameStateMachine->update();
	
}
void Game::render()
{

	//clear window to black
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();
	//show window
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}
Game::Game()
{

}