#pragma once
#include "Object.h"
#include "Ability.h"
class EnemyState;

typedef enum class EnemyAttackType
{
	CLOSE,
	DISTANT

} E_AtkType;

typedef enum class EnemyDirection
{
	LEFT,
	RIGHT

}E_Dir;

class Enemy :	public Object
{
protected:

	shared_ptr<Ability> _ability;
	shared_ptr<EnemyState> _state;
	E_AtkType _atkType;
	E_Dir _dir;
	float _FPS;
	float _distance;
	float _atkDistance;
	float _speed;
	float _angle;
	int _atkFrame;
	bool _isAtkFrame;
	list<Vector2> _path;

	Sprite* _sprite;
	PhysicsBody* _physics;

public:

	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Attack() {};
	virtual void AttackExit() { OffAtkFrame(); }
	
	virtual void BasicUpdate();

	void AngleDetection();

	void ChangeState(shared_ptr<EnemyState> state);
	
	shared_ptr<EnemyState> GetState() { return _state; }

	string GetStateName();
	
	shared_ptr<Ability> GetAbility() { return _ability; }

	E_AtkType GetAtkType() { return _atkType; }
	void SetAtkType(E_AtkType atkType) { _atkType = atkType; }

	void SetImg(string stateName);
	void OffAtkFrame() { _isAtkFrame = false; }
	bool GetAtkFrame() { return _isAtkFrame; }
	Sprite* GetSprite() { return _sprite; }
	PhysicsBody* GetPhysics() { return _physics; }
	E_Dir GetDir() { return _dir; }

	float GetDistance() { return _distance; }
	float GetAtkDistance() { return _atkDistance; }
	float GetSpeed() { return _speed; }
	float GetAngle() { return _angle; }
	list<Vector2>* GetPath() { return &_path; }

	//에너미 매니저
	void SetDistance(float distance) { _distance = distance; }
	void SetAngle(float angle) { _angle = angle; }
	void SetPath(list<Vector2> path);

	
	
};
