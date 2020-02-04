#include "stdafx.h"
#include "SwordAttack.h"
#include "PlayerIdle.h"
#include "PlayerAttackScript.h"

void SwordAttack::Enter()
{
	_state = "Attack";

	_obj->GetSprite()->SetFrameX(0);
	_obj->GetSprite()->SetFPS(2.8f);
	_obj->GetSprite()->SetIsLoop(false);

	switch (_obj->GetDirection())
	{
	case Dir::Left: case Dir::Left_Up: case Dir::Left_Down: _obj->GetSprite()->SetFrameY(3); break;
	case Dir::Right: case Dir::Right_Up: case Dir::Right_Down: _obj->GetSprite()->SetFrameY(2); break;
	case Dir::Up: _obj->GetSprite()->SetFrameY(0); break;
	case Dir::Down: _obj->GetSprite()->SetFrameY(1); break;
	}

	_obj->GetSprite()->SetImgName("will_sword");
	_obj->GetSprite()->SetMaxFrameX(6);

	int d = (int)_obj->GetDirection();
	int width = 100;
	int height = 60;

	_atkArea = Object::CreateObject<Object>(_obj);
	_atkArea->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf(d * 45 * Deg2Rad), -sinf(d * 45 * Deg2Rad)) * 20);
	_atkArea->GetTrans()->SetScale(width, height);
	_atkArea->AddComponent<PlayerAttackScript>();

	switch (d)
	{
	case (int)Dir::Down: case (int)Dir::Up: case (int)Dir::Left: case (int)Dir::Right:
		_atkArea->GetTrans()->SetScale(height, width);
		break;
	}

	_atkArea->AddComponent<PhysicsBody>();

	PhysicsBody* p = _atkArea->GetComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1.f);

	b2Vec2 atk;
	if (d == (int)Dir::Down) atk = b2Vec2(p->GetBody()->GetPosition() + b2Vec2(cosf(d * 45 * Deg2Rad), -sinf(d * 45 * Deg2Rad)) * 0.0005f);
	else if (d == (int)Dir::Left_Up || d == (int)Dir::Up) atk = b2Vec2(p->GetBody()->GetPosition() + b2Vec2(cosf(d * 45 * Deg2Rad), -sinf(d * 45 * Deg2Rad)) * 0.3f);
	else atk = b2Vec2(p->GetBody()->GetPosition() + b2Vec2(cosf(d * 45 * Deg2Rad), -sinf(d * 45 * Deg2Rad)) * 0.15f);

	p->GetBody()->SetTransform(atk, d * 45 * Deg2Rad);
	p->GetBody()->SetFixedRotation(true);
	p->SetSensor(true);


	_obj->GetSprite()->SetPosition(_obj->GetTrans()->GetPos() + Vector2(0, -14));

	_timer = _count = 0;
	_delay = 0.3f;
}

void SwordAttack::Update()
{
	if (_obj->GetSprite()->GetCurrentFrameX() == _obj->GetSprite()->GetMaxFrameX())
	{
		_timer += TIMEMANAGER->getElapsedTime();

		if (_timer >= _delay)
		{
			_timer -= _delay;
			_obj->ChangeState(new PlayerIdle(_obj));
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				if (_count == 0)
				{
					_timer = 0;
					_count++;
					_obj->GetSprite()->SetMaxFrameX(11);
					_obj->GetSprite()->Resume();
				}
				else if (_count == 1)
				{
					_timer = 0;
					_delay = 0.4f;
					_count++;
					_obj->GetSprite()->SetMaxFrameX(6);
					_obj->GetSprite()->SetFrameX(1);
					_obj->GetSprite()->Resume();
				}
			}
		}
	}
}

void SwordAttack::Exit()
{
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_obj->GetChildren()[0]->GetComponent<PhysicsBody>()->GetBody());
	_obj->GetChildren()[0]->Release();
}
