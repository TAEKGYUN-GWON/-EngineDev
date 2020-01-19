#pragma once
#include "Scene.h"
#include "Player.h"
#include "Astar.h"
#include "Maptool.h"
#include "Enemy1.h"

class StartScene : public Scene
{
private:
	Player* _player;
	Player*_player2;
	Astar* _ast;
	Maptool* _maptool;
	Enemy1* _enemy1;
	vector<Enemy1*> vEnemy;
	float time;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

