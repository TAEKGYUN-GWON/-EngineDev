#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManeger.h"
#include "Dungeon.h"
#include "DungeonMgr.h"
#include "UiManager.h"

class DungeonScene : public Scene
{
private:
	Player* _player;
	Enemy* _enemy;	//나중에 enemymaneger로 바꿔줘야 할걸...?
	Dungeon* test;
	DungeonMgr* _dMgr;
	UiManager* UI;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

