#include "BulletHandler.h"
#include "Game.h"

BulletHandler* BulletHandler::s_pInstance = 0;
Vector2D BulletHandler::getPos(int num)
{
	return bulletPos.at(num);
}
void BulletHandler::add(Vector2D pos, int dir, int who)
{
	bulletPos.push_back(pos);
	bulletDir.push_back(dir);
	bulletOwner.push_back(who);
}

std::vector< int > BulletHandler::get(int num)
{
	std::vector<int> temp;
	temp.push_back(bulletPos.at(num).m_x);
	temp.push_back(bulletPos.at(num).m_y);
	temp.push_back(bulletDir.at(num));
	temp.push_back(bulletOwner.at(num));
	return temp;
}

void BulletHandler::update()
{
	for (int i = 0; i < bulletPos.size(); i++)
	{
		switch (bulletDir.at(i))
		{
		case MRIGHT:
			bulletPos.at(i) += bulletSpeed;
			break;
		case MLEFT:
			bulletPos.at(i) -= bulletSpeed;
		}
		
		if (bulletPos.at(i).m_x > 640 || bulletPos.at(i).m_x < -14)
		{
			remove(i);
		}
	}
}
void BulletHandler::remove(int num)
{
	bulletPos.erase(bulletPos.begin() + num);
	bulletDir.erase(bulletDir.begin() + num);
	bulletOwner.erase(bulletOwner.begin() + num);
}