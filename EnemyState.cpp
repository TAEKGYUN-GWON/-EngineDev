#include "stdafx.h"
#include "EnemyState.h"
#include "Player.h"
#include "EnemyNormal.h"

// Idle
void EnemyIdle::Enter()
{
	_state = "Idle";
	_enemy->GetSprite()->SetImgName(_enemy->GetName() + "_Idle");
	_enemy->GetSprite()->SetIsLoop(true);
	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Player");
	_timer = 0.0f;
}

void EnemyIdle::Update()
{
	_distance = fabs(Vector2::Distance(_enemy->GetTrans()->GetPos(), _player->GetTrans()->GetPos()));

	if (_distance <= TILE_WIDTH * 6)
	{
		_timer += 1.f * TIMEMANAGER->getElapsedTime();
		if (_timer >= 0.5f)
		{
			_enemy->ChangeState(make_shared<EnemyMove>(_enemy));
			return;
		}
	}
}

void EnemyIdle::Exit()
{
}

// Move
void EnemyMove::Enter()
{
	_state = "Move";
	
	_enemy->GetSprite()->SetImgName(_enemy->GetName() + "_Walk");
	_enemy->GetSprite()->SetIsLoop(true);

	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Player");
}

void EnemyMove::Update()
{
	_v2Dis = (_enemy->GetTrans()->GetPos() - _player->GetTrans()->GetPos());

	if (_v2Dis.x <= -1.f) _enemy->SetDirection(E_Dir::Right);
	else if (_v2Dis.x >= 1.f) _enemy->SetDirection(E_Dir::Left);
	else _enemy->SetDirection(E_Dir::None);

	if (fabs(_v2Dis.x) <= TILE_WIDTH)
	{
		_enemy->ChangeState(make_shared<EnemyAttack>(_enemy));
		return;
	}

	if (fabs(_v2Dis.x) >= TILE_WIDTH * 7)
	{
		_enemy->ChangeState(make_shared<EnemyIdle>(_enemy));
		return;
	}

	_enemy->GetPhysics()->ApplyForce(Vector2::b2Down);
	_enemy->GetTrans()->SetPos(_enemy->GetTrans()->GetPos() + Vector2(_enemy->GetDirection(), 0.0f) *
	_enemy->GetAbility()->GetSpeed() * TIMEMANAGER->getElapsedTime());
	
	_enemy->GetPhysics()->SetBodyPosition();

}

void EnemyMove::Exit()
{
}

// Attack
void EnemyAttack::Enter()
{
	_state = "Attack";
	_enemy->GetSprite()->SetImgName(_enemy->GetName() + "_Attack");
	_enemy->GetSprite()->SetIsLoop(false);

	_timer = 0.0f;
}

void EnemyAttack::Update()
{
	if (_enemy->GetSprite()->IsFrameEnd())
	{
		_timer += 1.0f * TIMEMANAGER->getElapsedTime();
		if (_timer > 0.25f)
		{
			_enemy->ChangeState(make_shared<EnemyIdle>(_enemy));
			return;
		}
	}
}

void EnemyAttack::Exit()
{
}

// Damege
void EnemyDamage::Enter()
{
	_state = "Damege";
	_enemy->GetSprite()->SetImgName(_enemy->GetName() + "_Damage");
	_enemy->GetSprite()->SetIsLoop(false);

	_enemy->GetPhysics()->ApplyForce(Vector2::b2Right * 1000 * TIMEMANAGER->getElapsedTime());

	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Player");
	_enemy->GetAbility()->DamageHP(_player->GetAbility()->GetAttackPoint());

	_timer = 0.0f;
}

void EnemyDamage::Update()
{
	//_enemy->GetPhysics()->ApplyForce(Vector2::b2Right * 100.f * TIMEMANAGER->getElapsedTime());
	//_enemy->GetPhysics()->GetBody()->SetLinearVelocity(Vector2::b2Right * 70.f * TIMEMANAGER->getElapsedTime());

	if (_enemy->GetSprite()->IsFrameEnd())
	{
		_timer += 1.0f * TIMEMANAGER->getElapsedTime();
		if (_timer > 0.25f)
		{
			if (_enemy->GetAbility()->IsDead())
			{
				_enemy->ChangeState(make_shared<EnemyDead>(_enemy));
				return;
			}

			_enemy->ChangeState(make_shared<EnemyIdle>(_enemy));
			return;
		}
	}
}

void EnemyDamage::Exit()
{
}

// Dead
void EnemyDead::Enter()
{
	_state = "Dead";

	_enemy->GetSprite()->SetImgName(_enemy->GetName() + "_Dead");
	_enemy->GetSprite()->SetIsLoop(false);

	_timer = 0.0f;
}

void EnemyDead::Update()
{
	if (_enemy->GetSprite()->IsFrameEnd())
	{
		_timer += 1.0f * TIMEMANAGER->getElapsedTime();
		if (_timer > 0.45f)
		{
			_enemy->SetIsActive(false);
		}
	}
}

void EnemyDead::Exit()
{
}
