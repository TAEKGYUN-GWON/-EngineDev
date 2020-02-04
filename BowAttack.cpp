#include "stdafx.h"
#include "BowAttack.h"
#include "PlayerIdle.h"

void BowAttack::Enter()
{
	_state = "Attack";

	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetFPS(2.8f);
	_obj->GetSprite()->SetIsLoop(false);
	
	int arrowSpd = 350;

	switch (_obj->GetDirection())
	{
	case Dir::Left: case Dir::Left_Up: case Dir::Left_Down: 
		_obj->GetSprite()->SetFrameY(3); 
		_obj->GetBulletPool()->GetPoolObject()->GetSprite()->SetImgName("arrow_up");
		_obj->GetBulletPool()->GetPoolObject()->Fire(_obj->GetTrans()->GetPos() + Vector2(-5, -15), PI, arrowSpd);
		break;
	case Dir::Right: case Dir::Right_Up: case Dir::Right_Down: 
		_obj->GetSprite()->SetFrameY(2); 
		_obj->GetBulletPool()->GetPoolObject()->GetSprite()->SetImgName("arrow_up");
		_obj->GetBulletPool()->GetPoolObject()->Fire(_obj->GetTrans()->GetPos() + Vector2(5, -15), PI2, arrowSpd);
		break;
	case Dir::Up: 
		_obj->GetSprite()->SetFrameY(0); 
		_obj->GetBulletPool()->GetPoolObject()->GetSprite()->SetImgName("arrow_down");
		_obj->GetBulletPool()->GetPoolObject()->Fire(_obj->GetTrans()->GetPos() + Vector2(0, -20), PI / 2, arrowSpd);
		break;
	case Dir::Down: 
		_obj->GetSprite()->SetFrameY(1); 
		_obj->GetBulletPool()->GetPoolObject()->GetSprite()->SetImgName("arrow_down");
		_obj->GetBulletPool()->GetPoolObject()->Fire(_obj->GetTrans()->GetPos() + Vector2(0, 20), 3 * PI / 2, arrowSpd);
		break;
	}
	_obj->GetBulletPool()->InssertActiveObject();

	_obj->GetSprite()->SetImgName("will_bow");
	_obj->GetSprite()->SetMaxFrameX(9);

	_obj->GetSprite()->SetPosition(_obj->GetTrans()->GetPos() + Vector2(0, -14));
	
	_timer = _count = 0;
	_delay = 0.29f;
}

void BowAttack::Update()
{
	if (_obj->GetSprite()->GetCurrentFrameX() == _obj->GetSprite()->GetMaxFrameX())
	{
		_timer += TIMEMANAGER->getElapsedTime();
	
		if (_timer >= _delay)
		{
			_timer -= _delay;
			_obj->ChangeState(new PlayerIdle(_obj));
		}
	}
}

void BowAttack::Exit()
{
}
