#include "stdafx.h"
#include "Enemy.h"
#include "EnemyState.h"

void Enemy::Init()
{
	Object::Init();
}

void Enemy::Release()
{
	Object::Release();
}

void Enemy::Update()
{
	Object::Update();
}

void Enemy::Render()
{
	Object::Render();
}

void Enemy::ChangeState(shared_ptr<EnemyState> state)
{
	_state->Exit();
	_state.swap(state);
	_state->Enter();
}
