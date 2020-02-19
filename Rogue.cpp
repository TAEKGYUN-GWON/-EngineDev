#include "stdafx.h"
#include "Rogue.h"
#include "EnemyState.h"

void Rogue::Init(Vector2 pos)
{
	Enemy::Init();
	_name = "Rogue";
	_atkDistance = 5.f;
	_distance = 100;
	_FPS = 1.3f;
	_speed = 80.f;
	_atkFrame = 0;
	_angle = PI;

	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"Rogue_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"RogueRunRight0_6x1.png", 6, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"RogueDead0_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"RogueAttack0_3x1.png", 3, 1);

	_sprite->SetPivot(PIVOT::BOTTOM);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(20, 10));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);

	_leftAtk = Object::CreateObject<Object>(this);
	_leftAtk->Init();
	auto t = _leftAtk->GetTrans();
	t->SetScale(10, 15);
	t->SetPos(_trans->GetPos() + Vector2::left * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	auto p = _leftAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->GetBody()->SetFixedRotation(true);
	_leftAtk->SetIsActive(false);

	_rightAtk = Object::CreateObject<Object>(this);
	_rightAtk->Init();
	t = _rightAtk->GetTrans();
	t->SetScale(10, 15);
	t->SetPos(_trans->GetPos() + Vector2::right * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	p = _rightAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->GetBody()->SetFixedRotation(true);

	_rightAtk->SetIsActive(false);
	_state->Enter();


}
void Rogue::Update()
{
	Enemy::Update();
	if (_state->GetStateToString() == "Attack")
	{
		_FPS = 0.7f;
		_sprite->SetFPS(_FPS);
	}
	else
	{
		_FPS = 1.3;
		_sprite->SetFPS(_FPS);
	}
	if (KEYMANAGER->isOnceKeyDown('1'))
		_distance = 5;
	if (KEYMANAGER->isOnceKeyDown('2'))
		_distance = 100;
}
void Rogue::Attack()
{
	switch (_dir)
	{
	case EnemyDirection::LEFT:
		_leftAtk->SetIsActive(true);
		break;
	case EnemyDirection::RIGHT:
		_rightAtk->SetIsActive(true);
		break;
	default:
		break;
	}
}

void Rogue::AttackExit()
{
	Enemy::AttackExit();
	_leftAtk->SetIsActive(false);
	_rightAtk->SetIsActive(false);
}

void Rogue::BasicUpdate()
{
	Enemy::BasicUpdate();
	//if (_state->GetStateToString() == "Idle")
	_sprite->SetPosition(_trans->GetPos() + Vector2::down * 13);

	_leftAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::left * (5 + (_leftAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_leftAtk->GetComponent<PhysicsBody>()->SetBodyPosition();

	_rightAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::right * (5 + (_rightAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_rightAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
}
