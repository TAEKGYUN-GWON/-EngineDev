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

	Ability* _ability;
	shared_ptr<EnemyState> _state;
	E_AtkType _atkType;
	E_Dir _dir;
	float _FPS;
	float _distance;
	float _atkDistance;
	float _speed;
	float _angle;
	float _dirAngle;
	float _hurtAngle;
	int _atkFrame;
	bool _isAtkFrame;
	bool _isHurt;
	bool _isMove;
	float _timer;
	float _maxTimer;
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
	void SetIsHurt(bool active) { _isHurt = active; }
	bool GetIsHurt() { return _isHurt; }

	void SetIsMove(bool active) { _isMove = active; }
	bool GetIsMove() { return _isMove; }

	void AngleDetection();

	float GetTimer() { return _timer; }
	float GetMaxTimer() { return _maxTimer; }
	void SetTimer(float time) { _timer = time; }
	
	void ChangeState(shared_ptr<EnemyState> state);
	
	shared_ptr<EnemyState> GetState() { return _state; }

	string GetStateName();
	
	Ability* GetAbility() { return _ability; }

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
	list<Vector2> GetPath() { return _path; }

	//에너미 매니저
	void SetDistance(float distance) { _distance = distance; }
	void SetAngle(float angle) { _angle = angle; }
	void SetPath(list<Vector2> path);

	void SetHurtAngle(float angle) { _hurtAngle = angle; }
	float GetHurtAngle() { return _hurtAngle; }

	void SetDirAngle(float angle) { _dirAngle = angle; }
	float GetDirAngle() { return _dirAngle; }



	void Move();
};
