#include "PauseState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	SDL_ShowCursor(1);
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);
	setCallbacks(m_callbacks);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	TheInputHandler::Instance()->reset();
	SDL_ShowCursor(0);

	std::cout << "exiting PauseState\n";

	return GameState::onExit();
}
void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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