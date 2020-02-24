#include "stdafx.h"
#include "EnemyNormal.h"
#include "EnemyState.h"

void EnemyNormal::Init()
{
	Enemy::Init();

	_name = "BigZombie";

	GRAPHICMANAGER->AddImage("BigZombie_Idle", L"Resource/Enemy/Normal/BigZombie_Idle.png", 4, 1);
	GRAPHICMANAGER->AddImage("BigZombie_Walk", L"Resource/Enemy/Normal/BigZombie_Walk.png", 5, 1);
	GRAPHICMANAGER->AddImage("BigZombie_Attack", L"Resource/Enemy/Normal/BigZombie_Attack.png", 5, 1);
	GRAPHICMANAGER->AddImage("BigZombie_Damage", L"Resource/Enemy/Normal/BigZombie_Damage.png", 3, 1);
	GRAPHICMANAGER->AddImage("BigZombie_Dead", L"Resource/Enemy/Normal/BigZombie_Dead.png", 8, 1);
	GRAPHICMANAGER->AddImage("BigZombie_Dead_Headshot", L"Resource/Enemy/Normal/BigZombie_Dead_Headshot.png", 8, 1);

	_trans->SetPos(WINSIZEX / 2 - 300, 325);
	_trans->SetScale(24, 30);

	_sprite->Init(true, true);
	_sprite->SetDepth(7);
	_sprite->SetImgName("BigZombie_Idle");
	_sprite->SetPosition(_trans->GetPos() + Vector2(0.0f, -3.f));
	_sprite->SetShowRect(true);

	_ability = make_shared<Ability>(40, 40, 10, 85.f);

	_dir = E_Dir::Right;

	_physics->Init(BodyType::DYNAMIC, 1.0f);
	_physics->GetBody()->SetFixedRotation(true);

	b2Filter b;
	b.categoryBits = CATEGORY_ENEMY;
	b.maskBits = MASK_ENEMY;
	_physics->GetBody()->GetFixtureList()->SetFilterData(b);

	_state = make_shared<EnemyIdle>(this);
	_state->Enter();
}

void EnemyNormal::Release()
{
	Enemy::Release();
}

void EnemyNormal::Update()
{
	Enemy::Update();

	_state->Update();

	_sprite->SetPosition(_trans->GetPos() + Vector2(0.0f, -3.f));
	_trans->SetPos(_physics->GetBodyPosition());
}

void EnemyNormal::Render()
{
	Enemy::Render();

	//char buffer[128];
	//sprintf_s(buffer, "%s", _state->GetState().c_str());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 200, 20, ColorF::Azure);
	//
	//sprintf_s(buffer, "%d", _dir);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 240), buffer, 20, 200, 20, ColorF::Azure);
}
