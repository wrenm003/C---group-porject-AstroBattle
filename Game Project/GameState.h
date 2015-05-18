#pragma once

#include <string>
#include <vector>
#include "Game.h"
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit()
	{
		for (int i = 0; i < m_textureIDList.size(); i++)
		{
			TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
		}
		return true;
	}

	virtual std::string getStateID() const = 0;
	std::vector<std::string> m_textureIDList;
};

