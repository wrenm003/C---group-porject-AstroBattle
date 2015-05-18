#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "BulletHandler.h"

void Level::render()
{
	TheTextureManager::Instance()->draw("background", 0, 0, 640, 480, TheGame::Instance()->getRenderer());
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
	for (int j = 0; j < TheBulletHandler::Instance()->getNum(); j++)
	{
		std::string temp = TheBulletHandler::Instance()->get(j).at(3) == PBULLET?"pbullet":"bullet";
		switch (TheBulletHandler::Instance()->get(j).at(2))
		{
		case MRIGHT:
			TheTextureManager::Instance()->draw(temp, TheBulletHandler::Instance()->get(j).at(0), TheBulletHandler::Instance()->get(j).at(1), 27, 14, TheGame::Instance()->getRenderer());
			break;
		case MLEFT:
			TheTextureManager::Instance()->draw(temp, TheBulletHandler::Instance()->get(j).at(0), TheBulletHandler::Instance()->get(j).at(1), 27, 14, TheGame::Instance()->getRenderer(),SDL_FLIP_HORIZONTAL);
			break;
		}
		
	}
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
	TheBulletHandler::Instance()->update();
}