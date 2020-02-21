#include "stdafx.h"
#include "PlayerIdle.h"
#include "Player.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"

void PlayerIdle::Enter()
{
	_state = "Idle";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Idle");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.0f);
}

void PlayerIdle::Update()
{
	if (KEYMANAGER->isStayKeyDown('D') or KEYMANAGER->isStayKeyDown('A'))
	{
		_obj->ChangeState(make_shared<PlayerMove>(_obj));
		return;
	}

	if (_obj->GetIsLadderCollider())
	{
		if (KEYMANAGER->isStayKeyDown('W') or KEYMANAGER->isStayKeyDown('S'))
		{
			_obj->ChangeState(make_shared<PlayerMove>(_obj));
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_obj->ChangeState(make_shared<PlayerAttack>(_obj));
	}
}

void PlayerIdle::Exit()
{
}
