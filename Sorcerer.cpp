#include "stdafx.h"
#include "Sorcerer.h"
#include "EnemyState.h"

void Sorcerer::Init(Vector2 pos)
{
	Enemy::Init();

	_name = "Sorcerer";
	_atkDistance =60.f;
	_distance = 100;
	_FPS = 1.3f;
	_speed = 30.f;
	_atkFrame = 4;
	_angle = 0;
	_isFire = false;
	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"SummonerIdleDown.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Hurt", dir + L"SummonerHurt.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"SummonerRunRight0_3x1.png", 3, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"SummonerDead0_6x1.png", 6, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"SummonerCast0_6x1.png", 6, 1);

	_sprite->SetPivot(PIVOT::BOTTOM);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(20, 10));
	_sprite->SetPosition(_trans->GetPos());
	_physics->Init(BodyType::DYNAMIC, 1, 1);

	_state->Enter();
	_ability->Init(80, 20);
}

void Sorcerer::Update()
{
	Enemy::Update();
	if (KEYMANAGER->isOnceKeyDown('1'))
		_distance = 5;
	if (KEYMANAGER->isOnceKeyDown('2'))
		_distance = 100;
}


void Sorcerer::Attack()
{
	if (_atkFrame == _sprite->GetCurrentFrameX())
		_isFire = true;
	else
		_isFire = false;
}

void Sorcerer::AttackExit()
{
	Enemy::AttackExit();
	_isFire = false;
}

void Sorcerer::BasicUpdate()
{
	Enemy::BasicUpdate();
	_sprite->SetPosition(_trans->GetPos() + Vector2::down * 10);
}
