#include "stdafx.h"
#include "EnemyState.h"

//idle
void EnemyIdle::Enter()
{
	_name = "Idle";
	_timer = 0;
	_maxTimer = RND->getFromFloatTo(2, 4);
	_enemy->SetImg(_name);


}

void EnemyIdle::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
	{
		_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
		return;
	}

	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyMove>(_enemy));
		return;
	}
	_enemy->GetPhysics()->SetBodyPosition();
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
	_enemy->SetImg(_name);
}

void EnemyMove::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
		return;
	}

	if (_enemy->GetDistance() <= _enemy->GetAtkDistance())
	{
		_enemy->ChangeState(make_shared <EnemyAttack>(_enemy));
		return;
	}

	if (_path->size())
	{
		_enemy->GetTrans()->SetRotateToRadian(Vector2::GetAngle(_enemy->GetTrans()->GetPos(), *(*_path).begin()));

		Vector2 direction = *(*_path).begin() - _enemy->GetTrans()->GetPos();
		direction = direction.Nomalized();
		_enemy->GetTrans()->Move(direction * _enemy->GetSpeed() * TIMEMANAGER->getElapsedTime());
		_enemy->GetPhysics()->SetBodyPosition();
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
	_enemy->SetImg(_name);
}

void EnemyAttack::Stay()
{
	if (_enemy->GetAtkFrame())
	{
		_enemy->Attack();

		if (_enemy->GetSprite()->GetCurrentFrameX() >= _enemy->GetSprite()->GetMaxFrameX())
		{
			_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
			return;
		}
	}
}

void EnemyAttack::Exit()
{
	_enemy->AttackExit();
}


//hurt
void EnemyHurt::Enter()
{
	_timer = 0;
	_maxTimer = 1.f;
	_name = "Hurt";
	_enemy->SetImg(_name);
}

void EnemyHurt::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();
	
	if (_timer >= _maxTimer)
	{
		_enemy->ChangeState(make_shared <EnemyIdle>(_enemy));
		return;
	}

}

void EnemyHurt::Exit()
{

}



//death
void EnemyDeath::Enter()
{
	_timer = 0;
	_maxTimer = 1.5f;
	_name = "Death";
	_enemy->SetImg(_name);
}

void EnemyDeath::Stay()
{

	if (_enemy->GetComponent<Sprite>()->GetCurrentFrameX() >= _enemy->GetComponent<Sprite>()->GetMaxFrameX())
		_timer += TIMEMANAGER->getElapsedTime();
	

	if(_timer>=_maxTimer)
		_enemy->SetIsActive(false);
}

void EnemyDeath::Exit()
{
}
