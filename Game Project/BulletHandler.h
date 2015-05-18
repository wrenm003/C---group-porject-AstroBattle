#pragma once
#include "Vector2D.h"
#include "Bullet.h"
#include "SDLGameObject.h"
#include <vector>
class BulletHandler
{
public:
	
	static BulletHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new BulletHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}
	void add(Vector2D pos, int dir,int who);
	int getNum(){ return bulletPos.size(); }
	void update();
	void remove(int num);
	void removeAll()
	{
		bulletPos.clear();
		bulletDir.clear();
		bulletOwner.clear();
	}
	std::vector<int> get(int num);
	Vector2D getPos(int num);


private:
	Vector2D bulletSpeed = Vector2D(4, 0);
	BulletHandler(){}
	static BulletHandler* s_pInstance;
	std::vector< Vector2D > bulletPos;
	std::vector< int > bulletDir;
	std::vector< int > bulletOwner;
};

typedef BulletHandler TheBulletHandler;