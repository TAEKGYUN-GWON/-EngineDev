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
	_atkFrame = 4;
	//_angle = PI;
	wstring dir = L"Resource/Wizard/Enemy/";
	GRAPHICMANAGER->AddFrameImage(_name + "Idle", dir + L"Knight_Idle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Move", dir + L"Knight_Move_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"Knight_Death_7x1.png", 7, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "Attack", dir + L"3Knight_Attack_5x1.png", 5, 1);
	_sprite->SetImgName(_name + "Idle");
	_sprite->SetPivot(PIVOT::BOTTOM);
	_state->Enter();
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(20, 15));
	_sprite->SetPosition(_trans->GetPos());
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1, 1);
}

void Knight::Update()
{
	Enemy::Update();
	if (KEYMANAGER->isOnceKeyDown('F'))
		_distance = 10;
	if (KEYMANAGER->isOnceKeyDown('G'))
		_distance = 100;
}

void Knight::Release()
{
	Enemy::Release();
}

void Knight::Attack()
{
}

void Knight::BasicUpdate()
{
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
		if (_sprite->GetCurrentFrameX() == _atkFrame)
			_isAtkFrame = true;
		if (_dir == E_Dir::RIGHT)
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::right * 5 + Vector2::down * 13);
		else
			_sprite->SetPosition(_trans->GetPos() + Vector2::up * 5 + Vector2::left * 5 + Vector2::down * 13);
	}


}
