#pragma once

#include <SDL.h>
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>
#include "GameStateMachine.h"
enum players
{
	PLAYER = 4,
	ENEMY = 8
};
class GameStateMachine;
class Game
{
public:
	//Return the instance
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	~Game(){}

	//Initialise SDL
	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);

	//render objects
	void render();
	//update game state
	void update();
	//handle collisions / input etc
	void handleEvents();
	//clean up
	void clean();
	//quit (sets m_bRunning to false)
	void quit() { m_bRunning = false; }

	//function to access private running variable
	bool running(){
		return m_bRunning;
	}
	int getGameWidth() const
	{
		return m_gameWidth;
	}
	int getGameHeight() const
	{
		return m_gameHeight;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }

	void changeScore(int who)
	{
		switch (who)
		{
		case PLAYER:
			scores[0]--;
			break;
		case ENEMY:
			scores[1]--;
			break;
		}
	}

	void resetScores()
	{
		scores[0] = 9;
		scores[1] = 9;
	}

	std::vector< int > getScores()
	{
		return scores;
	}

private:
	Game();
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	int m_currentFrame;
	int m_gameWidth;
	int m_gameHeight;
	std::vector< int > scores;

	GameStateMachine* m_pGameStateMachine;
};
typedef Game TheGame;