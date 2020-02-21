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
	cout << _obj->GetSprite()->GetCurrentFrameX() << endl;

	//if (_obj->GetSprite()->IsFrameEnd())
	if (_obj->GetSprite()->GetCurrentFrameX() >= _obj->GetSprite()->GetMaxFrameX())
	{
		_obj->ChangeState(make_shared<PlayerIdle>(_obj));
	}
}

void PlayerAttack::Exit()
{
}
