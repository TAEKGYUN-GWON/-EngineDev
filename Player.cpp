#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerScript.h"
void Player::Init(Vector2 pos)
{
	Object::Init();
	AddComponent<PlayerScript>();
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(15, 10));
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 3,3);
	_physics->GetBody()->SetFixedRotation(true);
	_name = "Player";
	_tag = "Player";
	_speed = 100.f;
	_atkFrame = 3;
	_atkAngle = 0;
	_FPS = 2.f;
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetFPS(_FPS);
	_sprite->SetScale(Vector2(1.3, 1.3));
	_sprite->SetDepth(2);
	wstring dir = L"Resource/Wizard/Player/";
	_ability = make_shared<Ability>();
	_ability->Init(100, 15);
	_state = make_shared<PlayerIdle>(this);

	_skills.push_back(new P_Skill("WindBoomerang", 0.2f));
	_skills.push_back(new P_Skill("FireBall", 1.6f));
	_skills.push_back(new P_Skill("ChaosCircle", 7));

	_curSkill = FindSkill("WindBoomerang");

	//_isCollisionToWall = true;
	GRAPHICMANAGER->AddFrameImage(_name + "SideIdle", dir + L"PlayerSideIdle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "UpIdle", dir + L"PlayerUpIdle.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "DownIdle", dir + L"PlayerDownIdle.png", 1, 1);

	GRAPHICMANAGER->AddFrameImage(_name + "SideHurt", dir + L"PlayerSideHert.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "UpHurt", dir + L"PlayerUpHert.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "DownHurt", dir + L"PlayerDownHert.png", 1, 1);

	GRAPHICMANAGER->AddFrameImage(_name + "SideMove", dir + L"PlayerSideMove_10x1.png", 10, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "UpMove", dir + L"PlayerUpMove_10x1.png", 10, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "DownMove", dir + L"PlayerDownMove_10x1.png", 10, 1);

	GRAPHICMANAGER->AddFrameImage(_name + "SideAttack", dir + L"PlayerAtkSide_8x1.png", 8, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "UpAttack", dir + L"PlayerAtkUp_11x1.png", 11, 1);
	GRAPHICMANAGER->AddFrameImage(_name + "DownAttack", dir + L"PlayerAtkDown_9x1.png", 9, 1);

	GRAPHICMANAGER->AddFrameImage(_name + "Death", dir + L"Death_11x1.png", 11, 1);

	_state->Enter();
}

void Player::Update()
{
	if (_isDead) return;
	Object::Update();
	BasicUpdate();
}

void Player::Render()
{
	Object::Render();
	char buffer[256];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(buffer, "%d CoolDown : %f", i + 1, _skills[i]->curTime);
		GRAPHICMANAGER->Text(Vector2(WINSIZE / 2) + Vector2(0, i * 100), buffer, 20, 100, 20, ColorF::WhiteSmoke);
	}
}

void Player::Release()
{
	Object::Release();
}

void Player::ChangeState(shared_ptr<PlayerState> state)
{
	_state->Exit();
	_state.swap(state);
	_state->Enter();
}

string Player::GetStateName()
{
	return _state->GetStateToString();
}

string Player::GetDirectionToString()
{
	switch (_dir)
	{
	case Player_Direction::LEFT:
	case Player_Direction::RIGHT:
	{
		return "Side";
	}
	break;
	case Player_Direction::UP:
	{
		return "Up";
	}
	break;
	case Player_Direction::DOWN:
	{
		return "Down";
	}
	break;
	}
}

void Player::Move()
{
	_trans->Move(Vector2(cosf(_moveAngle), -sinf(_moveAngle)) * _speed * TIMEMANAGER->getElapsedTime());
	_physics->SetBodyPosition();
}

void Player::BasicUpdate()
{

	//if (!_isBattle) CAMERA->SetPosition(_trans->GetPos());
	AtkAngleDetection();
	_ability->Update();
	_state->Stay();
	_sprite->SetPosition(_trans->GetPos() + Vector2::up * 12);
	FlipDetection();
	WindUpCoolDown();
	ChangeCurrentSkill();
}

void Player::WindUpCoolDown()
{
	for (auto s : _skills)
	{
		if (s->curTime < s->cooldownTime) s->curTime += TIMEMANAGER->getElapsedTime();
		if (s->curTime > s->cooldownTime)s->curTime = s->cooldownTime;
	}


}

void Player::FlipDetection()
{
	switch (_dir)
	{
	case Player_Direction::LEFT:
		_sprite->SetFlipX(true);
		break;
	case Player_Direction::RIGHT:
		_sprite->SetFlipX(false);
		break;
	}

}

void Player::AtkAngleDetection()
{
	_atkAngle = Vector2::GetAngle(_trans->GetPos(), MOUSEPOINTER->GetMouseWorldPosition());
}

void Player::SetPlayerImg(string stateName)
{
	if (stateName != "Death")
		switch (_dir)
		{
		case Player_Direction::LEFT : 
		case Player_Direction::RIGHT:
		{
			_sprite->SetImgName(_name + "Side"+ stateName);
		}
		break;
		case Player_Direction::UP:
		{
			_sprite->SetImgName(_name + "Up" + stateName);
		}
		break;
		case Player_Direction::DOWN:
		{
			_sprite->SetImgName(_name + "Down" + stateName);
		}
		break;
		}
	else
		_sprite->SetImgName("PlayerDeath");
	_sprite->SetFPS(_FPS);
}

P_Skill* Player::FindSkill(string name)
{
	for (auto s : _skills)
		if (s->name == name) return s;
	return nullptr;
}

void Player::ChangeCurrentSkill()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if(_curSkill->name == "WindBoomerang") _curSkill = FindSkill("FireBall");
		else if (_curSkill->name == "FireBall") _curSkill = FindSkill("ChaosCircle");
		else if (_curSkill->name == "ChaosCircle") _curSkill = FindSkill("WindBoomerang");

	}
}
