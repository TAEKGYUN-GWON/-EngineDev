#include "stdafx.h"
#include "MintPotEnemy.h"
#include "Ability.h"
//#include "Bullet.h"
//#include "BulletScript.h" //걸어줘야 하나?

MintPotEnemy::MintPotEnemy()
{
}

MintPotEnemy::~MintPotEnemy()
{
}

void MintPotEnemy::Init(Vector2 pos)
{
	Enemy::Init();

	GRAPHICMANAGER->AddFrameImage("enemyPot", L"resource/img/Enemy/pot.png", 11, 4);
	
	_tag = "enemy";
	_name = "Pot";

	_ability = new Ability(30, 30, 5);
	
	_speed = 0.f;
	_fireCount = 0;
	////이미지 크기, pos는 어떻게 하지 생성될때 방안에 랜덤으로 해야 할거 같음
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("enemyPot");
	_trans->SetScale(Vector2(_sprite->GetGraphic()->GetFrameWidth(),
		_sprite->GetGraphic()->GetFrameHeight()));
	_trans->SetPos(pos);
	//_sprite->SetMaxFrameX(5);
	//_sprite->SetFrameY(1);
	//_sprite->SetRectColor(ColorF::Cornsilk);
	_trans->SetScale(Vector2(20, 10));
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f);
	//가상세계의 렉트 뒤틀리는거 고정
	_physics->GetBody()->SetFixedRotation(true);

}

void MintPotEnemy::Update()
{
	Enemy::Update();
	_sprite->SetPosition(_trans->GetPos()+Vector2::up*10);
	IsFire();
	//Attack();
}

void MintPotEnemy::Attack()
{
	//_isAtk = true;
	//_sprite->SetImgName("Ebullet");
	//Bullet* _bullet;
	switch (_dir)
	{
	case DIRECTION::LEFT:
		_sprite->SetFrameY(1);
		//Bullet::Fire(Vector2())
		//_bullet->Fire
		break;
	case DIRECTION::RIGHT:
		_sprite->SetFrameY(2);
		break;
	case DIRECTION::TOP:
		_sprite->SetFrameY(3);
		break;
	case DIRECTION::BOTTOM:
		_sprite->SetFrameY(0);
		break;
	}
}

void MintPotEnemy::AttackEnd()
{
	_isAtk = false;
}

void MintPotEnemy::IsFire()
{
	_fireCount += TIMEMANAGER->getElapsedTime();

	if (_fireCount >= 1.5f)
	{
		_isAtk = true;
		SetState(EnemyAttack::GetInstance());
		_fireCount = 0;
	}
}
