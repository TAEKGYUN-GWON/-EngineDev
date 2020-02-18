#include "stdafx.h"
#include "Enemy.h"
#include "EnemyState.h"
void Enemy::Init()
{
	Object::Init();

	_tag = "Enemy";
	_state = make_shared<EnemyIdle>(this);
	_distance = _atkDistance = _speed = _angle = _isAtkFrame = _FPS = 0;
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
}

void Enemy::Update()
{
	Object::Update();
	BasicUpdate();
	AngleDetection();
	_state->Stay();

}

void Enemy::Release()
{
	Object::Release();
}



void Enemy::AngleDetection()
{
	if ((_angle > PI / 2 && _angle <= PI) || (_angle >= -PI && _angle < -PI / 2)) _dir = E_Dir::LEFT;
	else _dir = E_Dir::RIGHT;

	if (_dir == E_Dir::LEFT) _sprite->SetFlipX(true);
	else _sprite->SetFlipX(false);
}

void Enemy::ChangeState(shared_ptr<EnemyState> state)
{

	_state->Exit();
	_state.swap(state);
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

	_sprite->SetImgName(_name + stateName);
	
}
