#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerIdle.h"

void PlayerMove::Enter()
{
	_state = "Move";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.5f);

	_speed = 300.0f;
}

void PlayerMove::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_obj->GetCursorWhere() == CursorWhere::Left)
		{
			if(_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run_Back");
		}
		else if (_obj->GetCursorWhere() == CursorWhere::Right)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run_Back") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
		}
		_angle = PI2;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
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
		_angle = PI;
	}

	_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(_angle), -sinf(_angle)) * _speed * TIMEMANAGER->getElapsedTime());
	_obj->GetPhysicsBody()->SetBodyPosition();

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))// &&
		//!KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//_obj->ChangeState(new PlayerIdle(_obj));
		_obj->ChangeState(make_shared<PlayerIdle>(_obj));
	}
}

void PlayerMove::Exit()
{
}
