#pragma once
#include "Object.h"
#include "Ability.h"
#include "Player.h"
#include"BossState.h"
#include "Astar.h"
#include "Enemy.h"

class BossState;
class BossHand;

//보스 공격 패턴
enum class PHASE
{
	ROCK,
	HAND,
	SLIME
};

class Boss : public Object
{
protected:
	Sprite* _sprite;
	PhysicsBody* _physics;

	PHASE _phase;
	Ability* _ability;
	BossState* _Bstate;
	Player* _player;
	BossHand* _hand;
	list<Vector2> _path;

	vector<Object*> _rocks;

	vector<Enemy*> _enemys;
	Astar* _aStar;

	int _angle;
	float _speed; //굳이 있어야 하나?

public:
	Boss();
	~Boss();


	int maxFrameX;
	int frameY;
	//float GetAtkArea() { return 200; }
	void Init(Vector2 pos, vector<Tile*> tiles);
	void Update();
	void Render();
	void Release();

	vector<Object*> GetRocks() { return _rocks; }
	BossHand* GetHand() { return _hand; }
	void Attack();
	//void AttackEnd();
	vector<Enemy*>* GetEnemys() { return &_enemys; }
	Ability* GetHP() { return _ability; }
	PhysicsBody* GetPhysics() { return _physics; }
	Sprite* GetSprite() { return _sprite; }
	Player* GetPlayer() { return _player; }
	PHASE GetPhase() { return _phase; }
	BossState* GetState() { return _Bstate; }
	void SetState(BossState* state);
	//void SetHand(BossHand* hand);
	
};