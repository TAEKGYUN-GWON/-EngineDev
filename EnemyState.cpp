#include "stdafx.h"
#include "EnemyState.h"
#include "Enemy.h"

// [ Enemy Idle ]
void EnemyIdle::Enter()
{
	_state = "Idle";
}

void EnemyIdle::Update()
{
}

void EnemyIdle::Exit()
{
}

// [ Enemy Move ]
void EnemyMove::Enter()
{
	_state = "Move";
}

void EnemyMove::Update()
{
}

void EnemyMove::Exit()
{
}

// [ Enemy Attack ]
void EnemyAttack::Enter()
{
	_state = "Attack";
}

void EnemyAttack::Update()
{
}

void EnemyAttack::Exit()
{
}

// [ Enemy Dead ]
void EnemyDead::Enter()
{
	_state = "Dead";
}

void EnemyDead::Update()
{
}

void EnemyDead::Exit()
{
}
