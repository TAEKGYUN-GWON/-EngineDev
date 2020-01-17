#pragma once
#include "Scene.h"
#include "Player.h"
#include "Astar.h"
#include "Maptool.h"

class StartScene : public Scene
{
private:
	Player* _player;
	Player*_player2;
	Astar* _ast;
	Maptool* _maptool;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

