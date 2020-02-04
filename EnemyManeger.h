#pragma once
#include "Object.h"
#include "Enemy.h"
#include "SlimeEnemy.h"
#include "GolemEnemy.h"
#include "MintPotEnemy.h"
#include "Boss.h"
#include "Astar.h"
#include "Player.h"
#include "Dungeon.h"
#include "Bullet.h"
#include "BulletScript.h"

class Dungeon;

class EnemyManeger
{
private:
	Enemy* _enemy;
	Player* _player;
	Astar* _astar;
	Boss* _boss;
	Dungeon* _room;
	BulletObjPool* _BobjPool;
	Bullet* _bullet;
	

	vector<Enemy*> _vEnemy;
public:
	EnemyManeger();
	
	

	void Init(Dungeon* room);
	void Update();
	void Release();
	void Render();

	void SetEnemy();
	void Fire();
	//hp
	//여기서 아이템?
};

