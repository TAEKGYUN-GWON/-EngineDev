#pragma once
#include "Object.h"

class EnemyState;

class Enemy : public Object
{
protected:
	Sprite* _sprite;
	PhysicsBody* _physics;
	Ability* _ability;

	shared_ptr<EnemyState> _state;

public:
	Enemy() {}
	virtual ~Enemy() {}

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual Sprite* GetSprite() { return _sprite; }
	virtual PhysicsBody* GetPhysics() { return _physics; }
	virtual Ability* GetAbility() { return _ability; }

	virtual void ChangeState(shared_ptr<EnemyState> state);

	virtual shared_ptr<EnemyState> GetState() { return _state; }
};

