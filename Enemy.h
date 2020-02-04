#pragma once
#include "Object.h"
#include "Player.h"
//#include "Player.h" //h에서? cpp에서?

enum class DIRECTION
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

//상태패턴을 위한 전방선언
class EnemyBasic;
class EnemyIdle;
class EnemyMove;
class EnemyAttack;
class EnemyHit;
class EnemyDead;

//hp, bullet
class Ability;
//class Bullet;

class Enemy : public Object
{
protected:
	Sprite* _sprite;
	PhysicsBody* _physics;
	Player* _player;
	//■■■■■■■ 상태패턴 틀이 되는 EnemyBasic를 Enemy에게 알려줌 ■■■■■■■
	EnemyBasic* state;
	DIRECTION _dir;	//방향
	float _speed;
	Ability* _ability;
	int _angle;
	list<Vector2> _path;

	bool move;
	//타임도 줘야 하나?
	bool _isAtk;

	bool _changePos = true;

public:
	Enemy();
	virtual~Enemy(); //상속
	
	
	int maxFrameX;
	int frameY;
	
	//상태패턴을 만들어서 Enemy에게 알려주기 위한 함수
	void SetState(EnemyBasic* state);
	virtual void Init();
	virtual void Update();	
	virtual void Render();
	virtual void Attack() {};
	virtual void AttackEnd() {};
//get,set함수 만들어야 함
	Ability* GetHP() { return _ability; }
	PhysicsBody* GetPhysics() { return _physics; }
	DIRECTION GetDir() { return _dir; }
	Sprite* GetSprite() { return _sprite; }
	float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }
	float GetSpeed() { return _speed; }
	EnemyBasic* GetState() { return state; }
	Player* GetPlayer() { return _player; }

//A*
	void SetPath(list<Vector2> _path);
	list<Vector2> GetPath() { return _path; }
	void SetMove(bool active) { move = active; }
	bool GetMove() { return move; }
	bool GetAtk() { return _isAtk; }
	void SetAtk(bool active) { _isAtk = active; }
//아이템 떨굴 갯수 만들어야함

};



//■■■■■■■■■■■■■■ 상태 ■■■■■■■■■■■■■■■■
class EnemyBasic
{
protected:
	//상태패턴 내부에서 서로의 상태를 왔다 갔다 하기 위한 것.
	void SetEnemyState(Enemy* _sEnemy, EnemyBasic* _EnemyState)
	{
		_sEnemy->SetState(_EnemyState);
	}
public:
	//basic이라서 다 초기화 해준다.
	virtual void Init(Enemy* _sEnemy) {};
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy) {};

};
//■■■■■■■■■■■■ Idle ■■■■■■■■■■■■■■
class EnemyIdle : public EnemyBasic
{
	//상태를 객체화 해줌
	static EnemyIdle* instance;

public:
	//Idle이 아닌 다른 상태들한테 보내줄 인스턴스
	static EnemyIdle* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//■■■■■■■■■■■■ Move ■■■■■■■■■■■■■
class EnemyMove : public EnemyBasic
{
	static EnemyMove* instance;
	float timer;

public:
	static EnemyMove* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//■■■■■■■■■■■ Attack ■■■■■■■■■■■■
class EnemyAttack : public EnemyBasic
{
	static EnemyAttack* instance;

public:
	static EnemyAttack* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};

//■■■■■■■■■■■■ Hit ■■■■■■■■■■■■■
class EnemyHit : public EnemyBasic
{
	static EnemyHit* instance;

public:
	static EnemyHit* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//■■■■■■■■■■■■ Dead ■■■■■■■■■■■■

class EnemyDead : public EnemyBasic
{
	static EnemyDead* instance;

public:
	static EnemyDead* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};