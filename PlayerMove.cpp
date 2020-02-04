#include "stdafx.h"
#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerRoll.h"
#include "SwordAttack.h"
#include "BowAttack.h"

void PlayerMove::Enter()
{
	_state = "Move";

	_obj->GetSprite()->SetMaxFrameX(8);
	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetFPS(2.0f);
}

void PlayerMove::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_obj->GetSprite()->SetFrameY(0);
			_obj->SetDirection(Dir::Right_Up);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_obj->GetSprite()->SetFrameY(1);
			_obj->SetDirection(Dir::Right_Down);
		}
		else
		{
			_obj->GetSprite()->SetFrameY(2);
			_obj->SetDirection(Dir::Right);
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_obj->GetSprite()->SetFrameY(0);
			_obj->SetDirection(Dir::Left_Up);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_obj->GetSprite()->SetFrameY(1);
			_obj->SetDirection(Dir::Left_Down);
		}
		else
		{
			_obj->GetSprite()->SetFrameY(3);
			_obj->SetDirection(Dir::Left);
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_obj->GetSprite()->SetFrameY(0);
		_obj->SetDirection(Dir::Up);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_obj->GetSprite()->SetFrameY(1);
		_obj->SetDirection(Dir::Down);
	}

	// Roll
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _obj->ChangeState(new PlayerRoll(_obj));

	// Attack
	if (SCENEMANAGER->GetNowScene()->GetName() != "Shop" && 
		!_obj->GetIsInteraction() && KEYMANAGER->isOnceKeyDown('J'))
	{
		if (_obj->GetAttackType() == AttackType::Sword)
			_obj->ChangeState(new SwordAttack(_obj));
		else if (_obj->GetAttackType() == AttackType::Bow)
			_obj->ChangeState(new BowAttack(_obj));
	}

	// 방향키를 누르지 않았을 때
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_obj->ChangeState(new PlayerIdle(_obj));
	}

	_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf((int)_obj->GetDirection() * 45 * Deg2Rad), -sinf((int)_obj->GetDirection() * 45 * Deg2Rad)) * _obj->GetSpeed() * TIMEMANAGER->getElapsedTime());
	_obj->GetPhysics()->SetBodyPosition();
	
}

void PlayerMove::Exit()
{
	_obj->GetPhysics()->SetBodyPosition();
	_obj->GetSprite()->SetPosition(_obj->GetTrans()->GetPos() + Vector2(0, -14));
}
