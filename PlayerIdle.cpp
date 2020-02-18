#include "stdafx.h"
#include "PlayerIdle.h"
#include "Player.h"
#include "PlayerMove.h"

void PlayerIdle::Enter()
{
	_state = "Idle";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Idle");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.0f);
}

void PlayerIdle::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//_obj->ChangeState(new PlayerMove(_obj));
		_obj->ChangeState(make_shared<PlayerMove>(_obj));
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_obj->ChangeState(make_shared<PlayerMove>(_obj));
	}
}

void PlayerIdle::Exit()
{
}
