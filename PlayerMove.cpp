#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerIdle.h"
//#include "PlayerAttack.h"
#include "HandAttack.h"
#include "UndergroundScene.h"
#include "PlayerDead.h"

void PlayerMove::Enter()
{
	_state = "Move";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.5f);
	_obj->GetPhysicsBody()->GetBody()->SetGravityScale(1);
	_obj->GetAbility()->SetSpeed(SPEED);
}

void PlayerMove::Update()
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_obj->GetCursorWhere() == CursorWhere::Left)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run_Back");
		}
		else if (_obj->GetCursorWhere() == CursorWhere::Right)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run_Back") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
		}

		_obj->SetDirection(Dir::Right);
		_obj->GetPhysicsBody()->ApplyForce(Vector2::b2Down);
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_obj->GetCursorWhere() == CursorWhere::Left)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run_Back") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
		}
		else if (_obj->GetCursorWhere() == CursorWhere::Right)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run_Back");
		}

		_obj->SetDirection(Dir::Left);
		_obj->GetPhysicsBody()->ApplyForce(Vector2::b2Down);
	}

	_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf((int)_obj->GetDirection() * Deg2Rad), -sinf((int)_obj->GetDirection() * Deg2Rad)) * 
		_obj->GetAbility()->GetSpeed() * TIMEMANAGER->getElapsedTime());
	_obj->GetPhysicsBody()->SetBodyPosition();

	if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D'))
	{
		_obj->ChangeState(make_shared<PlayerIdle>(_obj));
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_obj->SetAttackType(AtkType::Hand);
		_obj->ChangeState(make_shared<HandAttack>(_obj));
		return;
	}

	if (_obj->GetAbility()->IsDead())
	{
		_obj->ChangeState(make_shared<PlayerDead>(_obj));
		return;
	}
}

void PlayerMove::Exit()
{
}
