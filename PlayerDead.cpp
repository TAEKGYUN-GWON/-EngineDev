#include "stdafx.h"
#include "PlayerDead.h"

void PlayerDead::Enter()
{
	_state = "Dead";

	_obj->GetSprite()->SetMaxFrameX(10);
	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetFrameY(12);
	_obj->GetSprite()->SetFPS(1.2f);
	_obj->GetSprite()->SetIsLoop(false);
}

void PlayerDead::Update()
{
}

void PlayerDead::Exit()
{
}
