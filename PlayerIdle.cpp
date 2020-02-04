#include "stdafx.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerRoll.h"
#include "PlayerAttack.h"
#include "SwordAttack.h"
#include "BowAttack.h"
#include "Ability.h"
#include "PlayerDead.h"

void PlayerIdle::Enter()
{
	_state = "Idle";

	_obj->GetSprite()->SetImgName("will_dungeon");
	_obj->GetSprite()->SetMaxFrameX(10);
	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetIsLoop(true);

	switch (_obj->GetDirection())
	{
	case Dir::Left : case Dir::Left_Up : case Dir::Left_Down :
		_obj->GetSprite()->SetFrameY(9);
		break;
	case Dir::Right : case Dir::Right_Up : case Dir::Right_Down :
		_obj->GetSprite()->SetFrameY(8);
		break;
	case Dir::Up : _obj->GetSprite()->SetFrameY(10); break;
	case Dir::Down: _obj->GetSprite()->SetFrameY(11); break;
	}
	_obj->GetSprite()->SetFPS(1.0f);
	_obj->GetPhysics()->GetBody()->SetLinearVelocity(Vector2::b2Zero);
}

void PlayerIdle::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_obj->ChangeState(new PlayerMove(_obj));
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_obj->ChangeState(new PlayerMove(_obj));
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_obj->ChangeState(new PlayerMove(_obj));
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_obj->ChangeState(new PlayerMove(_obj));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_obj->ChangeState(new PlayerRoll(_obj));
	}

	if (SCENEMANAGER->GetNowScene()->GetName() != "Shop" && 
		!_obj->GetIsInteraction() && KEYMANAGER->isOnceKeyDown('J'))
	{
		if(_obj->GetAttackType() == AttackType::Sword)
			_obj->ChangeState(new SwordAttack(_obj));
		else if (_obj->GetAttackType() == AttackType::Bow)
			_obj->ChangeState(new BowAttack(_obj));
	}

	if (_obj->GetAbility()->IsDead()) _obj->ChangeState(new PlayerDead(_obj));
}

void PlayerIdle::Exit()
{
}
