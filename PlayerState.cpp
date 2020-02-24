#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"
#include "FireBall.h"
#include "ChaosCircle.h"
#include "WindBoomerang.h"
//Idle
void PlayerIdle::Enter()
{
	_name = "Idle";
	_player->SetPlayerImg(_name);

}

void PlayerIdle::Stay()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player->SetDirection(P_DIR::UP);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player->SetDirection(P_DIR::LEFT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player->SetDirection(P_DIR::DOWN);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player->SetDirection(P_DIR::RIGHT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_player->GetCurrentSkill()->curTime >= _player->GetCurrentSkill()->cooldownTime)
			_player->ChangeState(make_shared<PlayerAttack>(_player));
		return;
	}

}

void PlayerIdle::Exit()
{
}

//Move
void PlayerMove::Enter()
{
	_name = "Move";
	_player->SetFPS(2.f);
	_player->SetPlayerImg(_name);
}

void PlayerMove::Stay()
{

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_player->GetDirection() != P_DIR::RIGHT)
		{
			_player->SetDirection(P_DIR::RIGHT);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('W')) _player->SetMoveAngle(PI / 4);

		else if (KEYMANAGER->isStayKeyDown('S')) _player->SetMoveAngle(-PI / 4);

		else _player->SetMoveAngle(0);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_player->GetDirection() != P_DIR::LEFT)
		{
			_player->SetDirection(P_DIR::LEFT);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('W'))  _player->SetMoveAngle((PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('S')) _player->SetMoveAngle(-(PI * 3) / 4);

		else _player->SetMoveAngle(PI);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('W'))
	{

		if (_player->GetDirection() != P_DIR::UP)
		{
			_player->SetDirection(P_DIR::UP);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('A')) _player->SetMoveAngle((PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('D')) _player->SetMoveAngle(PI / 4);

		else _player->SetMoveAngle(PI / 2);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_player->GetDirection() != P_DIR::DOWN)
		{
			_player->SetDirection(P_DIR::DOWN);
			_player->SetPlayerImg(_name);
		}

		if (KEYMANAGER->isStayKeyDown('A')) _player->SetMoveAngle(-(PI * 3) / 4);

		else if (KEYMANAGER->isStayKeyDown('D')) _player->SetMoveAngle(-PI / 4);

		else _player->SetMoveAngle(-PI / 2);

		//if (!_player->GetIsCollToWall()) _player->Move();
	}

	else
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}

	_player->GetTrans()->Move(Vector2(cosf(_player->GetMoveAngle()), -sinf(_player->GetMoveAngle())) * _player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	_player->GetPhysics()->SetBodyPosition();
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if(_player->GetCurrentSkill()->curTime >= _player->GetCurrentSkill()->cooldownTime)
			_player->ChangeState(make_shared<PlayerAttack>(_player));
		return;
	}

}

void PlayerMove::Exit()
{
}

//Attack;
void PlayerAttack::Enter()
{
	_name = "Attack";
	_player->SetFPS(2.f);

	float angle = _player->GetAtkAngle();

	if (angle >= 45 * DegToRad && angle < 135 * DegToRad) _player->SetDirection(P_DIR::UP);

	else if (angle <= -45 * DegToRad && angle > -135 * DegToRad) _player->SetDirection(P_DIR::DOWN);

	else if (angle >= 135 * DegToRad && angle < 180 * DegToRad) _player->SetDirection(P_DIR::LEFT);
	else if (angle <= -135 * DegToRad && angle > -180 * DegToRad) _player->SetDirection(P_DIR::LEFT);


	else if (angle <= 0 * DegToRad && angle > -45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	else if (angle >= 0 * DegToRad && angle < 45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	isAttack = false;
	_player->SetPlayerImg(_name);
}

void PlayerAttack::Stay()
{
	if (_player->GetSprite()->GetCurrentFrameX() == _player->GetAtkFrame())
	{
		if (_player->GetCurrentSkill()->name == "WindBoomerang")
		{
			if (!isAttack)
			{
				WindBoomerang* chaos = Object::CreateObject<WindBoomerang>(_player);
				_player->GetCurrentSkill()->curTime = 0;
				chaos->Init(_player);
				isAttack = true;
			}
		}
		else if (_player->GetCurrentSkill()->name == "FireBall")
		{
			if (!isAttack)
			{
				FireBall* chaos = Object::CreateObject<FireBall>(_player);
				_player->GetCurrentSkill()->curTime = 0;
				chaos->Init(_player);
				isAttack = true;
			}
		}
		else if (_player->GetCurrentSkill()->name == "ChaosCircle")
		{

			ChaosCircle* chaos = Object::CreateObject<ChaosCircle>(_player);
			_player->GetCurrentSkill()->curTime = 0;
			chaos->Init(_player);
		}
		

	}
	if (_player->GetSprite()->GetCurrentFrameX() == _player->GetSprite()->GetMaxFrameX()) _player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerAttack::Exit()
{
}

//Hurt
void PlayerHurt::Enter()
{
	_name = "Hurt";

	float angle = _player->GetHurtAngle();

	if (angle >= 45 * DegToRad && angle < 135 * DegToRad) _player->SetDirection(P_DIR::UP);

	else if (angle <= -45 * DegToRad && angle > -135 * DegToRad) _player->SetDirection(P_DIR::DOWN);

	else if (angle >= 135 * DegToRad && angle < 180 * DegToRad) _player->SetDirection(P_DIR::LEFT);
	else if (angle <= -135 * DegToRad && angle > -180 * DegToRad) _player->SetDirection(P_DIR::LEFT);


	else if (angle <= 0 * DegToRad && angle > -45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);
	else if (angle >= 0 * DegToRad && angle < 45 * DegToRad) _player->SetDirection(P_DIR::RIGHT);

	_player->SetPlayerImg(_name);
	_timer = 0;
	_maxTimer = 0.5f;
}

void PlayerHurt::Stay()
{
	_timer += TIMEMANAGER->getElapsedTime();

	if (_timer >= _maxTimer)
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
	}
}

void PlayerHurt::Exit()
{
}

//Death
void PlayerDeath::Enter()
{
	_name = "Death";
	_player->SetFPS(1.5f);
	_player->SetPlayerImg(_name);
}

void PlayerDeath::Stay()
{
}

void PlayerDeath::Exit()
{
}
