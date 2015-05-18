#pragma once

#include "GameState.h"
#include <vector>
class GameState;
class GameStateMachine
{
	friend class Player;
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();

protected:
	
	std::vector<GameState*> m_gameStates;

};

