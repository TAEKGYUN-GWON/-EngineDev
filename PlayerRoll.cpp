#include "stdafx.h"
#include "PlayerRoll.h"
#include "PlayerIdle.h"

void PlayerRoll::Enter()
{
	_state = "Roll";

	_obj->GetSprite()->SetMaxFrameX(8);
	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetFPS(2.5f);
	_obj->GetPhysics()->SetSensor(true);

	_rollSpeed = 10.0f;
	//if (_obj->GetDirection() == Dir::Left)
	//{
	//	_obj->GetSprite()->SetFrameY(5);
	//	_obj->GetPhysics()->ApplyForce(Vector2::b2Left * _rollSpeed);
	//}
	//else if (_obj->GetDirection() == Dir::Left_Up)
	//{
	//	_obj->GetSprite()->SetFrameY(5);
	//	_obj->GetPhysics()->ApplyForce((Vector2::b2Left + Vector2::b2Up) * _rollSpeed);
	//}
	//else if (_obj->GetDirection() == Dir::Right)
	//{
	//	_obj->GetSprite()->SetFrameY(4);
	//	_obj->GetPhysics()->ApplyForce(Vector2::b2Right * _rollSpeed);
	//}
	
	_friction = -0.3f;
}

void PlayerRoll::Update()
{
	//_obj->GetTrans()->SetPos(_obj->GetPhysics()->GetBodyPosition());

	if (_obj->GetDirection() == Dir::Left)
	{
		_obj->GetSprite()->SetFrameY(5);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(PI), -sinf(0.0f)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Left_Up)
	{
		_obj->GetSprite()->SetFrameY(5);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(2.53f), -sinf(2.53f)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Left_Down)
	{
		_obj->GetSprite()->SetFrameY(5);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(5 * PI / 4), -sinf(5 * PI / 4)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Right)
	{
		_obj->GetSprite()->SetFrameY(4);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(PI2), -sinf(0.0f)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Right_Up)
	{
		_obj->GetSprite()->SetFrameY(4);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(PI / 4), -sinf(PI / 4)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Right_Down)
	{
		_obj->GetSprite()->SetFrameY(4);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(7 * PI / 4), -sinf(7 * PI / 4)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Up)
	{
		_obj->GetSprite()->SetFrameY(6);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(PI / 2), -sinf(PI / 2)) * _rollSpeed);
	}
	else if (_obj->GetDirection() == Dir::Down)
	{
		_obj->GetSprite()->SetFrameY(7);
		_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(3 * PI / 2), -sinf(3 * PI / 2)) * _rollSpeed);
	}
	
	_rollSpeed += _friction;
	_obj->GetPhysics()->SetBodyPosition();
	
	if (_obj->GetSprite()->GetCurrentFrameX() >= _obj->GetSprite()->GetMaxFrameX())
	{
		_obj->GetPhysics()->SetSensor(false);
		_obj->ChangeState(new PlayerIdle(_obj));
	}
}

void PlayerRoll::Exit()
{
}
