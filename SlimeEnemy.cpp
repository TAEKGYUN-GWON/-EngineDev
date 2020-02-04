#include "stdafx.h"
#include "SlimeEnemy.h"
#include "Ability.h"


SlimeEnemy::SlimeEnemy()
{

}

SlimeEnemy::~SlimeEnemy()
{

}

void SlimeEnemy::Init(Vector2 pos)
{
	Enemy::Init();

	GRAPHICMANAGER->AddFrameImage("slime", L"resource/img/Enemy/slime.png", 5, 1); 
	
	_tag = "enemy";
	_name = "Slime";
	_speed = 20.f;
	_ability = new Ability(1, 1, 4);
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("slime");
	////이미지 크기, pos는 어떻게 하지 생성될때 방안에 랜덤으로 해야 할거 같음
	_trans->SetScale(Vector2(_sprite->GetGraphic()->GetFrameWidth(), 
		_sprite->GetGraphic()->GetFrameHeight()));
	_trans->SetPos(pos);
	//_sprite->SetMaxFrameX(5);
	//_sprite->SetFrameY(1);
	//_sprite->SetRectColor(ColorF::Cornsilk);

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f);	//플레이어한테 뚫림 왜 그러지?
	//가상세계의 렉트 뒤틀리는거 고정
	_physics->GetBody()->SetFixedRotation(true);	
	
}

void SlimeEnemy::Update()
{
	Enemy::Update();
	

	_sprite->SetPosition(_trans->GetPos());
	//_sprite->set
}

