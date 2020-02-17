#pragma once
#include "Object.h"
#include "Ability.h"
class EnemyState;

typedef enum class EnemyAttackType
{
	CLOSE,
	DISTANT

} E_AtkType;

class Enemy :	public Object
{
protected:

	Ability* _ability;
	EnemyState* _state;
	E_AtkType _atkType;
	float _distance;
	float _atkDistance;
	float _speed;
	float _angle;
	bool _isAtkFrame;
	list<Vector2> _path;

public:

	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Attack() {};

	void ChangeState(EnemyState* state);
	
	EnemyState* GetState() { return _state; }

	string GetStateName();
	
	Ability* GetAbility() { return _ability; }

	E_AtkType GetAtkType() { return _atkType; }
	void SetAtkType(E_AtkType atkType) { _atkType = atkType; }


	void SetDistance(float distance) { _distance = distance; }
	float GetDistance() { return _distance; }
	float GetAtkDistance() { return _atkDistance; }
	
	float GetSpeed() { return _speed; }

	void SetAngle(float angle) { _angle = angle; }
	float GetAngle() { return _angle; }
	list<Vector2>* GetPath() { return &_path; }
	void SetPath(list<Vector2> path);
	
	void SetImg(string stateName);
	void OffAtkFrame() { _isAtkFrame = false; }
	bool GetAtkFrame() { return _isAtkFrame; }

};
