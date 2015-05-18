#pragma once
#include "GameState.h"
#include <vector>
#include "GameObject.h"
class Level;
class GameObject;

class PlayState :
	public GameState
{
	friend class Player;
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	static bool checkCollision(Player* p1, Vector2D bullet);
	static bool checkCollision(Enemy* p1, Vector2D bullet);

	virtual std::string getStateID() const { return s_playID; }

protected:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	Level *pLevel;
};

