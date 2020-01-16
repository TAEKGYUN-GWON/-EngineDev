#pragma once
#include "Scene.h"
#include "Player.h"
#include"Astar.h"
#include "Enemy1.h"
class StartScene : public Scene
{
private:
	Player* _player;
	Player*_player2;
	Enemy1* _enemy1;
	vector<Enemy1*> vEnemy;
	Astar* _ast;
	float time;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

