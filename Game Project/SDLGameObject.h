#pragma once
#include "GameObject.h"
#include "LoaderParams.h"
#include <SDL.h>
#include "Vector2D.h"
#include "InputHandler.h"
#include "SoundManager.h"
class SDLGameObject :
	public GameObject
{
public:
	SDLGameObject();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	int playerScore = 0;
	int enemyScore = 0;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int m_numFramesOrig;
	int m_numFrames;
	bool goingRight;
	bool goingLeft;
	bool isStationary;
	bool wasRight = false;
	bool wasLeft = true;

	std::string m_textureID;
};

