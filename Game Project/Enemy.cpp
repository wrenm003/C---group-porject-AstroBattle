#include "Enemy.h"
#include "CollisionManager.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "GameStateMachine.h"
#include "BulletHandler.h"
using namespace std;

Enemy::Enemy() : SDLGameObject(), target(0, 0)
{

}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	if (jStart > -5)
	{
		if (Enemy::getPosition().getY() < (jStart - 80)){
			jumping = false;
			falling = true;
			jStart = -5;
		}
	}
	if (!jumping) m_velocity.setY(2);
	m_velocity.setX(0);


	handleInput();
	if (SDL_GetTicks() - shootStart > 0 && SDL_GetTicks() - shootStart < 100 && shooting)
	{
		m_currentRow = 2;
		m_currentFrame = 0;
	}
	else if (SDL_GetTicks() - shootStart > 100 && shooting)
	{
		shootStart = 0;
		shooting = false;
	}
	else if (standing)
	{
		m_currentRow = 1;
		m_currentFrame = 1;
	}
	else
	{
		m_currentRow = 1;
		m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	}


	SDLGameObject::update();
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
	if (Enemy::getPosition().getX() + Enemy::getWidth() > 640)
	{
		right = true;
	}

	if (Enemy::getPosition().getX() < 0)
	{
		left = true;
	}
	if (Enemy::getPosition().getY() + Enemy::getHeight() >480)
	{
		bottom = true;
		falling = false;
	}
	if (Enemy::getPosition().getY() < 0)
	{
		top = true;
	}

	if (left || right || top || bottom)
	{
		if (left)
		{
			Enemy::m_position.setX(0);
		}
		if (right)
		{
			Enemy::m_position.setX(640 - Enemy::getWidth());
		}
		if (bottom)
		{
			Enemy::m_position.setY(480 - Enemy::getHeight());
		}
		if (top)
		{
			Enemy::m_position.setY(0);
		}
	}
	for (int i = 0; i < TheBulletHandler::Instance()->getNum(); i++)
	{
		if (PlayState::checkCollision(this, TheBulletHandler::Instance()->getPos(i)))
		{
			if (TheBulletHandler::Instance()->get(i).at(3) != EBULLET)
			{
				TheGame::Instance()->changeScore(ENEMY);
				TheSoundManager::Instance()->playSound("explosion", 0);
				//cout << "Enemy collided with Bullet #" << i << endl;
				std::cout << "Player: " << TheGame::Instance()->getScores().at(0) << " Enemy: " << TheGame::Instance()->getScores().at(1) << std::endl;
				TheBulletHandler::Instance()->remove(i);
			}
		}
	}
}
void Enemy::clean()
{
}

void Enemy::handleAnimation()
{

}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		standing = false;
	}
	else
	{
		standing = true;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		move(MRIGHT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		move(MLEFT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		move(MJUMP);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_KP_ENTER))
	{
		shoot();
	}
}

void Enemy::move(int dir)
{
	switch (dir){
	case MRIGHT:
		m_velocity.setX(2);
		break;
	case MLEFT:
		m_velocity.setX(-2);
		break;
	case MJUMP:
		if (jumping || falling) break;
		jumping = true;
		jStart = Enemy::getPosition().getY();
		m_velocity.setY(-4);
		break;
	}
}

void Enemy::shoot()
{
	if (shooting) return;
	TheSoundManager::Instance()->playSound("laser", 0);
	shooting = true;
	if (wasRight)TheBulletHandler::Instance()->add(Vector2D(m_position.m_x + 51, m_position.m_y + 7), MRIGHT,EBULLET);
	else if (wasLeft)TheBulletHandler::Instance()->add(Vector2D(m_position.m_x - 14, m_position.m_y + 7), MLEFT,EBULLET);
	shootStart = SDL_GetTicks();
}