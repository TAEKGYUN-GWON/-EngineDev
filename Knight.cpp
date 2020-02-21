#include "stdafx.h"
#include "Knight.h"
#include "EnemyState.h"

void Knight::Init(Vector2 pos)
{
	Enemy::Init();
	_name = "Knight";
	_atkDistance = 10.f;
	_distance = 100;
	_FPS = 1.3f;
	_speed = 60.f;
	_atkFrame = 3;
	_angle = 0;
	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"Knight_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Hurt", dir + L"Knight_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"Knight_Move_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"Knight_Death_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"Knight_Attack_5x1.png", 5, 1);

	_sprite->SetPivot(PIVOT::BOTTOM);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(20, 15));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);

	_leftAtk = Object::CreateObject<Object>(this);
	_leftAtk->Init();
	auto t = _leftAtk->GetTrans();
	t->SetScale(20, 15);
	t->SetPos(_trans->GetPos() + Vector2::left * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	auto p = _leftAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->GetBody()->SetFixedRotation(true);
	_leftAtk->SetIsActive(false);

	_rightAtk = Object::CreateObject<Object>(this);
	_rightAtk->Init();
	t = _rightAtk->GetTrans();
	t->SetScale(20, 15);
	t->SetPos(_trans->GetPos() + Vector2::right * (5 + (t->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	p = _rightAtk->AddComponent<PhysicsBody>();
	p->Init(BodyType::DYNAMIC, 1);
	p->GetBody()->SetFixedRotation(true);

	_rightAtk->SetIsActive(false);
	_state->Enter();
	_ability->Init(120, 15);
}
//
//void Knight::Update()
//{
//	Enemy::Update();
//	if (KEYMANAGER->isOnceKeyDown('1'))
//		_distance = 5;
//	if (KEYMANAGER->isOnceKeyDown('2'))
//		_distance = 100;
//}
//
//void Knight::Release()
//{
//	Enemy::Release();
//}

void Knight::Attack()
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

void Knight::AttackExit()
{
	Enemy::AttackExit();
	_leftAtk->SetIsActive(false);
	_rightAtk->SetIsActive(false);
}


void Knight::BasicUpdate()
{
	Enemy::BasicUpdate();
	if (_state->GetStateToString() == "Idle")
		_sprite->SetPosition(_trans->GetPos() + Vector2::down * 13);
	else if (_state->GetStateToString() == "Move")
	{
		if (_dir == E_Dir::RIGHT)
			_sprite->SetPosition(_trans->GetPos() + Vector2::right * 2 + Vector2::down * 8);
		else
			_sprite->SetPosition(_trans->GetPos() + Vector2::left * 2 + Vector2::down * 8);
	}
	else if (_state->GetStateToString() == "Attack")
	{
		if (_dir == E_Dir::RIGHT)
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::right * 5 + Vector2::down * 13);
		else
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::left * 5 + Vector2::down * 13);
	}


	_leftAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::left * (5 + (_leftAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_leftAtk->GetComponent<PhysicsBody>()->SetBodyPosition();

	_rightAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::right * (5 + (_rightAtk->GetTrans()->GetScale().x / 2) + (_trans->GetScale().x / 2)));
	_rightAtk->GetComponent<PhysicsBody>()->SetBodyPosition();

	

}

