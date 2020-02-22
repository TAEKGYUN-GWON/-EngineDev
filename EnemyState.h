#pragma once

class Enemy;

class EnemyState abstract
{
protected:
	Enemy* _enemy;
	string _state;

public:
	EnemyState() {}
	EnemyState(Enemy* obj) : _enemy(obj) {}

	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}

	string GetState() { return _state; }
};

// Enemy Idle
class EnemyIdle : public EnemyState
{
private:

public:
	EnemyIdle(Enemy* obj) : EnemyState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

// Enemy Move
class EnemyMove : public EnemyState
{
private:

public:
	EnemyMove(Enemy* obj) : EnemyState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

// Enemy Attack
class EnemyAttack : public EnemyState
{
private:

public:
	EnemyAttack(Enemy* obj) : EnemyState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

// Enemy Dead
class EnemyDead : public EnemyState
{
private:

public:
	EnemyDead(Enemy* obj) : EnemyState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};