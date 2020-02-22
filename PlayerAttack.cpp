#include "stdafx.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "PlayerIdle.h"

void PlayerAttack::Enter()
{
	_state = "Attack";

	_obj->GetSprite()->SetImgName("Hero_Pistol_Superhit");
	_obj->GetSprite()->SetFPS(2.0f);
	_obj->GetSprite()->Start();
}

void PlayerAttack::Update()
{
	if (_obj->GetSprite()->IsFrameEnd())
	{
		_obj->ChangeState(make_shared<PlayerIdle>(_obj));
	}
}

void PlayerAttack::Exit()
{
}
