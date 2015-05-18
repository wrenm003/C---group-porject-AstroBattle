#include "Bullet.h"
#include "Game.h"
using namespace std;

Bullet::Bullet() : SDLGameObject()
{
}

void Bullet::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.setX(5);
}

void Bullet::draw()
{
	SDLGameObject::draw();
	cout << "bullet drawn" << endl;
}

void Bullet::update()
{
	m_currentFrame = 0;
	cout << m_position.getX() << endl;
	SDLGameObject::update();
	if (m_position.m_x>TheGame::Instance()->getGameWidth() || m_position.m_x<0-m_width)
	{
		clean();
	}
}
void Bullet::clean()
{
	SDLGameObject::clean();
}