#pragma once
#include "Object.h"

enum class OnwerType
{
	Player,
	Enemy
};

class SkillObject :	public Object
{
protected:

	PhysicsBody* _physics;
	Object* _onwer;
	Sprite* _sprite;
	OnwerType _type;
	float _atk;
	float _speed;
	float _timer;
	float _maxTimer;
	float _moveAngle;
public:
	virtual void Init();
	virtual void Update();
	virtual void Move() {};
};

