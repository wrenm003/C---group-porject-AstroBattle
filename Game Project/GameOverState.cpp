#include "GameOverState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include <iostream>
#include "Game.h"
#include "AnimatedGraphic.h"
#include "PlayState.h"
#include "MainMenuState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new
		PlayState());
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	TheTextureManager::Instance()->draw("winnertext", 245, 70, 149, 28, TheGame::Instance()->getRenderer());
	if (winner == PLAYER)
	{
		TheTextureManager::Instance()->draw("player1text", 237, 100, 166, 32, TheGame::Instance()->getRenderer());
	}
	else
	{
		TheTextureManager::Instance()->draw("player2text", 234, 100, 172, 32, TheGame::Instance()->getRenderer());
	}	
	
}

bool GameOverState::onExit()
{
	std::cout << "exiting GameOverState\n";
	TheGame::Instance()->resetScores();
	return GameState::onExit();
}

bool GameOverState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	//set callbacks for menu items

	setCallbacks(m_callbacks);

	for (int i = 0; i < 2; i++)
	{
		if (TheGame::Instance()->getScores()[0] == 0)
		{
			winner = ENEMY;
		}
		else
		{
			winner = PLAYER;
		}
	}

	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//if of type MEnuButton, assign callback based on id passed from file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}