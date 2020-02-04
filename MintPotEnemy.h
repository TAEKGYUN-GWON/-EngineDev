#pragma once
#include "Enemy.h"

class MintPotEnemy : public Enemy
{
protected:
	float _fireCount;

public:
	MintPotEnemy();
	~MintPotEnemy();

	void Init(Vector2 pos);
	void Update();
	void Attack();
	void AttackEnd();
	void IsFire();
};

