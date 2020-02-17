#include "stdafx.h"
#include "Enemy.h"
#include "EnemyState.h"
void Enemy::Init()
{
	Object::Init();

	_tag = "Enemy";
	_state = new EnemyIdle(this);
	_distance = _atkDistance = _speed = _angle = _isAtkFrame = 0;
	AddComponent<Sprite>();
}

void Enemy::Update()
{
	Object::Update();

	_state->Stay();

}

void Enemy::Release()
{
	if (_state) delete _state;
	Object::Release();
}

void Enemy::ChangeState(EnemyState* state)
{
	if (_state)
	{
		_state->Exit();
		delete _state;
	}
	_state = state;
	_state->Enter();
}

string Enemy::GetStateName()
{
	return _state->GetStateToString();
}

void Enemy::SetPath(list<Vector2> path)
{
	_path.clear();
	_path = path;
}

void Enemy::SetImg(string stateName)
{
	auto s = GetComponent<Sprite>();
	s->SetImgName(_name + stateName);
}
