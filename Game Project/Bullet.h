#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Bullet :
	public SDLGameObject
{
public:
	Bullet();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
};

class BulletCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Bullet();
	}
};