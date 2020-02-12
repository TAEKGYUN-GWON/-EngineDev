#include "stdafx.h"
#include "Player.h"

void Player::Init()
{
	Object::Init();

	GRAPHICMANAGER->AddFrameImage("Hero_Dead", L"Resource/Player/Hero_Dead.png", 10, 1);
	GRAPHICMANAGER->AddFrameImage("Hero_Idle", L"Resource/Player/Hero_Idle.png", 5, 1);
	GRAPHICMANAGER->AddFrameImage("Hero_Idle_d", L"Resource/Player/Hero_Idle_d.png", 4, 1);
	GRAPHICMANAGER->AddFrameImage("Legs_Idle", L"Resource/Player/Legs_Idle.png", 5, 1);
	GRAPHICMANAGER->AddFrameImage("Hero_pistol_arm", L"Resource/Player/Hero_pistol_arm.png", 5, 1);
	
	// test image
	GRAPHICMANAGER->AddFrameImage("Hero_Mlee_Pistol_7", L"Resource/Player/Hero Mlee Pistol_7.png", 1, 1);

	_trans->SetPos(WINSIZEX / 2, 300);

	//_sprite = AddComponent<Sprite>();
	////_sprite->Init(true, true);
	//_sprite->Init(true);
	//_sprite->SetImgName("Hero_Mlee_Pistol_7");
	//_sprite->Stop();
	//
	//_trans->SetScale(_sprite->GetFrameWidth() * _sprite->GetScale().x, _sprite->GetFrameHeight() * _sprite->GetScale().y);
	_trans->SetScale(64, 64);

	_legs = Object::CreateObject<Object>(this);
	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 5.0f));

	Sprite* s = _legs->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Legs_Idle");
	//s->Stop();
	_legs->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());


	_body = Object::CreateObject<Object>(this);
	_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 2.0f));

	s = _body->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Hero_Idle_d");
	_body->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());


	_arms = Object::CreateObject<Object>(this);
	_arms->GetTrans()->SetPos(_trans->GetPos());
	
	s = _arms->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Hero_pistol_arm");
	_arms->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());
}

void Player::Update()
{
	Object::Update();

	_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 2.0f));
	_body->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));

	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 5.0f));
	_legs->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 5.0f));

	_arms->GetTrans()->SetPos(_trans->GetPos());
	_arms->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));


	if (MOUSEPOINTER->GetMouseWorldPosition().x < _trans->GetPos().x)
	{
		_body->GetComponent<Sprite>()->SetFlipX(true);
		_legs->GetComponent<Sprite>()->SetFlipX(true);
		_arms->GetComponent<Sprite>()->SetFlipX(true);
		_arms->GetTrans()->SetRotateToRadian(-Vector2::GetAngle(MOUSEPOINTER->GetMouseWorldPosition(), _trans->GetPos()));
	}
	else
	{
		_body->GetComponent<Sprite>()->SetFlipX(false);
		_legs->GetComponent<Sprite>()->SetFlipX(false);
		_arms->GetComponent<Sprite>()->SetFlipX(false);
		_arms->GetTrans()->SetRotateToRadian(-Vector2::GetAngle(_trans->GetPos(), MOUSEPOINTER->GetMouseWorldPosition()));
	}

	//_sprite->SetPosition(_trans->GetPos());
}

void Player::Render()
{
	Object::Render();

}
