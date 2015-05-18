#include "Player.h"
#include "CollisionManager.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "GameStateMachine.h"
#include "BulletHandler.h"
using namespace std;

Player::Player() : SDLGameObject(), target(0,0)
{
	wasRight = true;
	wasLeft = false;
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	if (jStart > -5)
	{
		if (Player::getPosition().getY() < (jStart - 80)){
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
	if (Player::getPosition().getX() + Player::getWidth() > 640)
	{
		right = true;
	}

	if(Player::getPosition().getX() < 0)
	{
		left = true;
	}
	if (Player::getPosition().getY() + Player::getHeight() >480)
	{
		bottom = true;
		falling = false;
	}
	if (Player::getPosition().getY() < 0)
	{
		top = true;
	}
	
	if (left || right || top || bottom)
	{
		if (left)
		{
			Player::m_position.setX(0);
		}
		if (right)
		{
			Player::m_position.setX(640-Player::getWidth());
		}
		if (bottom)
		{
			Player::m_position.setY(480-Player::getHeight());
		}
		if (top)
		{
			Player::m_position.setY(0);
		}
	}
	for (int i = 0; i < TheBulletHandler::Instance()->getNum(); i++)
	{
		if (PlayState::checkCollision(this, TheBulletHandler::Instance()->getPos(i)))
		{
			if (TheBulletHandler::Instance()->get(i).at(3) != PBULLET)
			{
				TheGame::Instance()->changeScore(PLAYER);
				TheSoundManager::Instance()->playSound("explosion", 0);
				//cout << "Player collided with Bullet #" << i << endl;
				std::cout << "Player: " << TheGame::Instance()->getScores().at(0) << " Enemy: " << TheGame::Instance()->getScores().at(1) << std::endl;
				TheBulletHandler::Instance()->remove(i);
			}
		}
	}
}
void Player::clean()
{
}

void Player::handleAnimation()
{

}

void Player::handleInput()
{	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		standing = false;
	}
	else
	{
		standing = true;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		move(MRIGHT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		move(MLEFT);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		move(MJUMP);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		shoot();
	}
}

void Player::move(int dir)
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
		jStart = Player::getPosition().getY();
		m_velocity.setY(-4);
		break;
	}
}

void Player::shoot()
{
	if (shooting) return;
	TheSoundManager::Instance()->playSound("laser", 0);
	shooting = true;
	if (wasRight)TheBulletHandler::Instance()->add(Vector2D(m_position.m_x+51, m_position.m_y+7), MRIGHT,PBULLET);
	else if (wasLeft)TheBulletHandler::Instance()->add(Vector2D(m_position.m_x-14, m_position.m_y+7), MLEFT,PBULLET);
	shootStart = SDL_GetTicks();
	
}