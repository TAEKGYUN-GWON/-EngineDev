#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerIdle.h"

void Player::Init()
{
	Object::Init();

	GRAPHICMANAGER->AddImage("Hero_Dead", L"Resource/Player/Hero_Dead.png", 10, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle", L"Resource/Player/Hero_Idle.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle_d", L"Resource/Player/Hero_Idle_d.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle_u", L"Resource/Player/Hero_Idle_u.png", 5, 1);
	GRAPHICMANAGER->AddImage("Legs_Idle", L"Resource/Player/Legs_Idle.png", 5, 1);
	GRAPHICMANAGER->AddImage("Legs_Run", L"Resource/Player/Legs_Run.png", 8, 1);
	GRAPHICMANAGER->AddImage("Legs_Run_Back", L"Resource/Player/Legs_Run_Back.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_pistol_arm", L"Resource/Player/Hero_pistol_arm.png", 5, 1);
	
	// test image
	GRAPHICMANAGER->AddImage("Hero_Mlee_Pistol_7", L"Resource/Player/Hero Mlee Pistol_7.png", 1, 1);

	_trans->SetPos(WINSIZEX / 2 - 200, 300);

	//_sprite = AddComponent<Sprite>();
	////_sprite->Init(true, true);
	//_sprite->Init(true);
	//_sprite->SetImgName("Hero_Mlee_Pistol_7");
	//_sprite->Stop();
	//
	//_trans->SetScale(_sprite->GetFrameWidth() * _sprite->GetScale().x, _sprite->GetFrameHeight() * _sprite->GetScale().y);
	_trans->SetScale(24, 42);

	_legs = Object::CreateObject<Object>(this);
	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 5.0f));

	Sprite* s = _legs->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Legs_Idle");
	//s->SetFPS(1.5f);
	_legs->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());


	_body = Object::CreateObject<Object>(this);
	_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 2.0f));

	s = _body->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Hero_Idle_u");
	_body->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());


	_arms = Object::CreateObject<Object>(this);
	_arms->GetTrans()->SetPos(_trans->GetPos());
	
	s = _arms->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Hero_pistol_arm");
	_arms->GetTrans()->SetScale(s->GetFrameWidth(), s->GetFrameHeight());

	_cw = CursorWhere::None;

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f, 0.3f);
	_physics->GetBody()->SetFixedRotation(true);

	_state = make_shared<PlayerIdle>(this);
	_state->Enter();
}

void Player::Update()
{
	Object::Update();

	_state->Update();

	/*_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 2.0f));
	_body->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));

	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 5.0f));
	_legs->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 5.0f));

	_arms->GetTrans()->SetPos(_trans->GetPos());
	_arms->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 2.0f));*/

	_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, -2.0f));
	_body->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, -2.0f));

	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 1.0f));
	_legs->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 1.0f));

	_arms->GetTrans()->SetPos(_trans->GetPos());
	_arms->GetComponent<Sprite>()->SetPosition(_trans->GetPos());

	DirectionSprite();

	//_sprite->SetPosition(_trans->GetPos());
}

void Player::Render()
{
	Object::Render();

	//wchar_t buffer[128];
	//swprintf(buffer, 128, L"%f", _armsAngle);
	////swprintf(buffer, 128, L"%f", _arms->GetTrans()->GetRotateDegree());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 200, 20, ColorF::White);
	//
	//swprintf(buffer, 128, L"arm : %f", _arms->GetTrans()->GetRotateRadian());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 130), buffer, 20, 200, 20, ColorF::White);
}

void Player::ChangeState(shared_ptr<PlayerState> state)
{
	_state->Exit();
	_state.swap(state);
	_state->Enter();
}

void Player::DirectionSprite()
{
	if (MOUSEPOINTER->GetMouseWorldPosition().x < _trans->GetPos().x)
	{
		_cw = CursorWhere::Left;

		_armsAngle = -Vector2::GetAngle(MOUSEPOINTER->GetMouseWorldPosition(), _trans->GetPos());
		_body->GetComponent<Sprite>()->SetFlipX(true);
		_legs->GetComponent<Sprite>()->SetFlipX(true);
		_arms->GetComponent<Sprite>()->SetFlipX(true);

		if (_armsAngle < -0.6f) _arms->GetTrans()->SetRotateToRadian(-0.6f);
		else if (_armsAngle > 0.5f) _arms->GetTrans()->SetRotateToRadian(0.5f);

		if (_armsAngle >= -0.6f and _armsAngle <= 0.5f)
		{
			_arms->GetTrans()->SetRotateToRadian(_armsAngle);

			if (_armsAngle < -0.25f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle_d") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle_d");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
			else if (_armsAngle < 0.25f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
			else if (_armsAngle < 0.6f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle_u") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle_u");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
		}
	}
	else
	{
		_cw = CursorWhere::Right;

		_armsAngle = -Vector2::GetAngle(_trans->GetPos(), MOUSEPOINTER->GetMouseWorldPosition());
		_body->GetComponent<Sprite>()->SetFlipX(false);
		_legs->GetComponent<Sprite>()->SetFlipX(false);
		_arms->GetComponent<Sprite>()->SetFlipX(false);

		if (_armsAngle < -0.5f) _arms->GetTrans()->SetRotateToRadian(-0.5f);
		else if (_armsAngle > 0.6f) _arms->GetTrans()->SetRotateToRadian(0.6f);

		if (_armsAngle >= -0.5f and _armsAngle <= 0.6f)
		{
			_arms->GetTrans()->SetRotateToRadian(_armsAngle);

			if (_armsAngle < -0.25f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle_u") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle_u");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
			else if (_armsAngle < 0.25f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
			else if (_armsAngle < 0.6f)
			{
				if (_body->GetComponent<Sprite>()->GetImgKey().compare("Hero_Idle_d") != 0)
				{
					_body->GetComponent<Sprite>()->SetImgName("Hero_Idle_d");
					_arms->GetComponent<Sprite>()->Start();
				}
			}
		}
	}
}