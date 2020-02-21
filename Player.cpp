#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerIdle.h"
#include "PlayerCollider.h"
#include "LadderScript.h"

void Player::Init()
{
	Object::Init();
	_name = "Player";
	GRAPHICMANAGER->AddImage("Hero_Dead", L"Resource/Player/Hero_Dead.png", 10, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle", L"Resource/Player/Hero_Idle.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle_d", L"Resource/Player/Hero_Idle_d.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_Idle_u", L"Resource/Player/Hero_Idle_u.png", 5, 1);
	GRAPHICMANAGER->AddImage("Legs_Idle", L"Resource/Player/Legs_Idle.png", 5, 1);
	GRAPHICMANAGER->AddImage("Legs_Run", L"Resource/Player/Legs_Run.png", 8, 1);
	GRAPHICMANAGER->AddImage("Legs_Run_Back", L"Resource/Player/Legs_Run_Back.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_pistol_arm", L"Resource/Player/Hero_pistol_arm.png", 5, 1);
	GRAPHICMANAGER->AddImage("Hero_Pistol_Superhit", L"Resource/Player/Hero_Pistol_Superhit.png", 5, 1);
	GRAPHICMANAGER->AddImage("None", L"Resource/Terrain/None/None.png");

	// test image
	GRAPHICMANAGER->AddImage("Hero_Mlee_Pistol_7", L"Resource/Player/Hero Mlee Pistol_7.png", 1, 1);

	_trans->SetPos(WINSIZEX / 2 - 500, 325);

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true);
	//_sprite->Init();
	_sprite->SetShowRect(true);
	_sprite->SetDepth(7);
	//_sprite->SetImgName("Hero_Pistol_Superhit");
	_sprite->SetImgName("None");

	_trans->SetScale(24, 42);

	_legs = Object::CreateObject<Object>(this);
	_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 5.0f));

	Sprite* s = _legs->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("Legs_Idle");
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
	_physics->Init(BodyType::DYNAMIC, 3.0f, 3.0f);
	_physics->GetBody()->SetFixedRotation(true);


	_judgingFloor = Object::CreateObject<Object>(this);
	_judgingFloor->GetTrans()->SetScale(1, 1);
	_judgingFloor->GetTrans()->SetPos(_trans->GetPosToPivot(TF_PIVOT::BOTTOM) + Vector2::up * _judgingFloor->GetTrans()->GetScale().y / 2 - Vector2(0, 5));
	_judgingFloor->AddComponent<LadderScript>();

	_floorPhysics = _judgingFloor->AddComponent<PhysicsBody>();
	_floorPhysics->Init(BodyType::DYNAMIC, 1.0f, 1.0f);
	_floorPhysics->GetBody()->SetFixedRotation(true);
	_floorPhysics->SetSensor(true);

	_state = make_shared<PlayerIdle>(this);
	_state->Enter();

	_isLadderCol = false;

	AddComponent<PlayerCollider>();
}

void Player::Update()
{
	Object::Update();

	_judgingFloor->GetTrans()->SetPos(_trans->GetPosToPivot(TF_PIVOT::BOTTOM) + Vector2::up * _judgingFloor->GetTrans()->GetScale().y / 2 - Vector2(0, 5));
	_judgingFloor->GetComponent<PhysicsBody>()->SetBodyPosition();

	_state->Update();

	_trans->SetPos(_physics->GetBodyPosition());

	if (_state->GetState().compare("Attack") == 0)
	{
		_body->SetIsActive(false);
		_legs->SetIsActive(false);
		_arms->SetIsActive(false);

		if (_sprite->GetFlipX()) _sprite->SetPosition(_trans->GetPos() + Vector2(-6.0f, 1.0f));
		else _sprite->SetPosition(_trans->GetPos() + Vector2(6.0f, 1.0f));
	}
	else
	{
		if (_body->GetIsActive() == false)
		{
			_body->SetIsActive(true);
			_legs->SetIsActive(true);
			_arms->SetIsActive(true);
			_sprite->SetImgName("None");
		}

		_body->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, -2.0f));
		_body->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, -2.0f));

		_legs->GetTrans()->SetPos(_trans->GetPos() + Vector2(0, 1.0f));
		_legs->GetComponent<Sprite>()->SetPosition(_trans->GetPos() + Vector2(0, 1.0f));

		_arms->GetTrans()->SetPos(_trans->GetPos());
		_arms->GetComponent<Sprite>()->SetPosition(_trans->GetPos());

		DirectionSprite();
	}

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

	char buffer[128];
	sprintf_s(buffer, "%s", _state->GetState().c_str());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 200, 20, ColorF::Azure);

	sprintf_s(buffer, "%d", _isLadderCol);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 240), buffer, 20, 200, 20, ColorF::Azure);

	sprintf_s(buffer, "index : %d", ((int)MOUSEPOINTER->GetMouseWorldPosition().x / TILE_WIDTH) + TILE_NUM_X * ((int)MOUSEPOINTER->GetMouseWorldPosition().y / TILE_HEIGHT));
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 180), buffer, 20, 200, 20, ColorF::Azure);
	//
	//sprintf_s(buffer, "x : %f \ny : %f", _judgingFloor->GetTrans()->GetPos().x, _judgingFloor->GetTrans()->GetPos().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 120), buffer, 20, 200, 20, ColorF::Azure);
	//
	//sprintf_s(buffer, "x : %f \ny : %f", _trans->GetPos().x, _trans->GetPos().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 70), buffer, 20, 200, 20, ColorF::Aqua);
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

		_sprite->SetFlipX(true);

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

		_sprite->SetFlipX(false);

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