#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject() : GameObject()
{

}
void SDLGameObject::load(const LoaderParams* pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames = pParams->getNumFrames();
	
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() == 0)
	{
		isStationary = true;
	}
	if (m_velocity.getX() > 0)
	{
		isStationary = false;
		goingLeft = false;
		goingRight = true;
		wasLeft = false;
		wasRight = true;
	}

	else if (m_velocity.getX()<0)
	{
		isStationary = false;
		goingRight = false;
		goingLeft = true;
		wasRight = false;
		wasLeft = true;
	}
	if (isStationary)
	{
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (wasRight)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if (wasLeft)
		{
			flip = SDL_FLIP_NONE;
		}
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), flip);
	}
	else if (goingRight)
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	
	else if (goingLeft)
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
}

void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}
void SDLGameObject::clean()
{

}

