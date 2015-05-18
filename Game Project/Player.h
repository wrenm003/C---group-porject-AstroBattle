#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
class TileLayer;
enum move_dirs
{
	MLEFT = -1,
	MRIGHT = 1,
	MJUMP = 0,
	PBULLET = 4,
	EBULLET = 8
};
class Player :
	public SDLGameObject
{
public:
	Player();
	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	Vector2D getVelocity() { return m_velocity; }
	virtual void collision(){ std::cout << "collision!"; }

private:
	void handleInput();
	void handleAnimation();
	Vector2D target;
	void move(int dir);
	void shoot();
	bool standing = true;
	bool jumping = false;
	bool falling = false;
	bool shooting = true;
	Uint32 shootStart = 0;
	int jStart = -5;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};