#include "stdafx.h"
#include "EnemyNormal.h"
#include "EnemyState.h"

void EnemyNormal::Init()
{
	GRAPHICMANAGER->AddImage("BigZombie_Idle", L"Resource/Enemy/BigZombie_Idle.png", 4, 1);

	_trans->SetPos(WINSIZEX / 2 - 300, 325);
	_trans->SetScale(24, 30);

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("BigZombie_Idle");

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f);
	_physics->GetBody()->SetFixedRotation(true);

	_ability = new Ability(40, 40, 10);

	//_state = make_shared<EnemyIdle>(this);
	//_state->Enter();
}

void EnemyNormal::Release()
{
}

void EnemyNormal::Update()
{
	//_state->Update();

	_sprite->SetPosition(_trans->GetPos());
	_trans->SetPos(_physics->GetBodyPosition());
}

void EnemyNormal::Render()
{
}
