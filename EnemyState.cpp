#include "stdafx.h"
#include "EnemyState.h"

//idle
void EnemyIdle::Enter()
{
	_name = "Idle";
	_timer = 0;
	_maxTimer = RND->getFromFloatTo(2, 4);
}

void EnemyIdle::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
		_enemy->ChangeState(new EnemyAttack(_enemy));

	if (_timer >= _maxTimer)
		_enemy->ChangeState(new EnemyMove(_enemy));
}

void EnemyIdle::Exit()
{
}


//move
void EnemyMove::Enter()
{
	_name = "Move";
	_path = _enemy->GetPath();
	_timer = 0;
	_maxTimer = RND->getFromFloatTo(2, 4);
}

void EnemyMove::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
		_enemy->ChangeState(new EnemyIdle(_enemy));

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
		_enemy->ChangeState(new EnemyAttack(_enemy));

	if (_path->size())
	{
		Vector2 direction = *(*_path).begin() - _enemy->GetTrans()->GetPos();
		direction = direction.Nomalized();
		_enemy->GetTrans()->Move(direction * _enemy->GetSpeed() * TIMEMANAGER->getElapsedTime());
		
		int distance = Vector2::Distance(*(*_path).begin(), _enemy->GetTrans()->GetPos());
		
		if (distance <= 10)
			_path->pop_front();
	}
}

void EnemyMove::Exit()
{
	
}


//attack
void EnemyAttack::Enter()
{
	_name = "Attack";
	_type = _enemy->GetAtkType();
}

void EnemyAttack::Stay()
{
	if (_enemy->GetAtkFrame())
	{
		_enemy->Attack();

		_enemy->ChangeState(new EnemyIdle(_enemy));
	}
}

void EnemyAttack::Exit()
{
	_enemy->OffAtkFrame();
}


//hurt
void EnemyHurt::Enter()
{
}

void EnemyHurt::Stay()
{
}

void EnemyHurt::Exit()
{
}



//death
void EnemyDeath::Enter()
{
	_name = "Death";
}

void EnemyDeath::Stay()
{
	if (_enemy->GetComponent<Sprite>()->GetCurrentFrameX() >= _enemy->GetComponent<Sprite>()->GetMaxFrameX())
		_enemy->SetIsActive(false);
}

void EnemyDeath::Exit()
{
}
