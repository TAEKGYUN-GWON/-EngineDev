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

	_legs->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 5.0f));
	_body->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));
	_arms->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));

	// 2020.02.10 TODO: 마우스 좌표 따라 팔의 각도도 달라져야하는데 그거 잡아야함
	// 맵툴도 빨리 봐야하는데..
	_arms->GetTrans()->SetRotateToRadian(_arms->GetTrans()->GetRotateRadian() + 0.01f);

	//_sprite->SetPosition(_trans->GetPos());
}

void Player::Render()
{
	Object::Render();

}
