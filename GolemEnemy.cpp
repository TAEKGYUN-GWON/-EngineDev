#include "stdafx.h"
#include "GolemEnemy.h"
#include "Ability.h"
#include"GolemScript.h"
GolemEnemy::GolemEnemy()
{
}

GolemEnemy::~GolemEnemy()
{
}

void GolemEnemy::Init(Vector2 pos)
{
	Enemy::Init();

	GRAPHICMANAGER->AddFrameImage("Golem", L"resource/img/Enemy/GolemMove.png", 8, 4);
	GRAPHICMANAGER->AddFrameImage("Golem_Atk", L"resource/img/Enemy/GolemAttack.png", 13, 4);
	_tag = "enemy";
	_name = "Golem";

	_ability = new Ability(50, 50, 8);

	_speed = 30.f;

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("Golem");
	_trans->SetScale(Vector2(_sprite->GetGraphic()->GetFrameWidth(),
		_sprite->GetGraphic()->GetFrameHeight()));
	_trans->SetPos(pos);
	_sprite->SetRectColor(ColorF::Cornsilk);

	_trans->SetScale(Vector2(62, 25));
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f);
	////가상세계의 렉트 뒤틀리는거 고정
	_physics->GetBody()->SetFixedRotation(true);

	_atkRange = GolemEnemy::GetAtkRange();


#pragma region 공격 오브젝트
	_lAtk = Object::CreateObject<Object>(this);
	_rAtk = Object::CreateObject<Object>(this);
	_tAtk = Object::CreateObject<Object>(this);
	_bAtk = Object::CreateObject<Object>(this);

	 _lAtk->SetTag("GolemAtk");
	 _rAtk->SetTag("GolemAtk");
	 _tAtk->SetTag("GolemAtk");
	 _bAtk->SetTag("GolemAtk");

	_lAtk->GetTrans()->SetPos(_trans->GetPos()+Vector2::left*50);
	_rAtk->GetTrans()->SetPos(_trans->GetPos()+Vector2::right*50);
	_tAtk->GetTrans()->SetPos(_trans->GetPos()+Vector2::up*50);
	_bAtk->GetTrans()->SetPos(_trans->GetPos()+Vector2::down*50);

	_lAtk->GetTrans()->SetScale(100,40);
	_rAtk->GetTrans()->SetScale(100,40);
	_tAtk->GetTrans()->SetScale(40,100);
	_bAtk->GetTrans()->SetScale(40,100);

	_lAtk->AddComponent<PhysicsBody>()->Init(BodyType::STATIC,1.f,1.f);
	_rAtk->AddComponent<PhysicsBody>()->Init(BodyType::STATIC,1.f,1.f);
	_tAtk->AddComponent<PhysicsBody>()->Init(BodyType::STATIC,1.f,1.f);
	_bAtk->AddComponent<PhysicsBody>()->Init(BodyType::STATIC,1.f,1.f);

	_lAtk->GetComponent<PhysicsBody>()->GetBody()->SetFixedRotation(true);
	_rAtk->GetComponent<PhysicsBody>()->GetBody()->SetFixedRotation(true);
	_tAtk->GetComponent<PhysicsBody>()->GetBody()->SetFixedRotation(true);
	_bAtk->GetComponent<PhysicsBody>()->GetBody()->SetFixedRotation(true);
	_lAtk->GetComponent<PhysicsBody>()->SetSensor(true);
	_rAtk->GetComponent<PhysicsBody>()->SetSensor(true);
	_tAtk->GetComponent<PhysicsBody>()->SetSensor(true);
	_bAtk->GetComponent<PhysicsBody>()->SetSensor(true);

	_lAtk->GetComponent<PhysicsBody>()->SetBodyActive(false);
	_rAtk->GetComponent<PhysicsBody>()->SetBodyActive(false);
	_tAtk->GetComponent<PhysicsBody>()->SetBodyActive(false);
	_bAtk->GetComponent<PhysicsBody>()->SetBodyActive(false);
	_atks.push_back(_lAtk);
	_atks.push_back(_rAtk);
	_atks.push_back(_tAtk);
	_atks.push_back(_bAtk);

	_lAtk->AddComponent<GolemScript>();
	_rAtk->AddComponent<GolemScript>();
	_tAtk->AddComponent<GolemScript>();
	_bAtk->AddComponent<GolemScript>();

#pragma endregion


}

void GolemEnemy::Update()
{
	Enemy::Update();

	_sprite->SetPosition(_trans->GetPos()+Vector2::up*30);
	AtkPosUpdate();
	if (KEYMANAGER->isOnceKeyDown('8'))GetLeftAtk()->SetBodyActive(true);

}

void GolemEnemy::Attack()
{
	if (_isAtk)
	{
		_sprite->SetImgName("Golem_Atk");
		_sprite->SetFPS(1.4f);
	}
	switch (_dir)
	{
	case DIRECTION::LEFT:
	{
		_sprite->SetFrameY(0);
		if (!GetLeftAtk()->GetBodyActive() && _sprite->GetCurrentFrameX() == 6)
			GetLeftAtk()->SetBodyActive(true);
	}
		break;
	case DIRECTION::RIGHT:
	{
		_sprite->SetFrameY(1);
		if(!GetRightAtk()->GetBodyActive() && _sprite->GetCurrentFrameX() == 6)
			GetRightAtk()->SetBodyActive(true);
	}
		break;
	case DIRECTION::TOP:
	{
		_sprite->SetFrameY(2);
		if(!GetTopAtk()->GetBodyActive() && _sprite->GetCurrentFrameX() == 6)
			GetTopAtk()->SetBodyActive(true);
	}
		break;
	case DIRECTION::BOTTOM:
	{
		_sprite->SetFrameY(3);
		if (!GetBottomAtk()->GetBodyActive() && _sprite->GetCurrentFrameX() == 6)
			GetBottomAtk()->SetBodyActive(true);
	}
		break;
	}
	
}

void GolemEnemy::AttackEnd()
{
	for (Object* atk : _atks)
		if (atk->GetComponent<PhysicsBody>()->GetBodyActive())
			atk->GetComponent<PhysicsBody>()->SetBodyActive(false);
}



void GolemEnemy::AtkPosUpdate()
{
	_lAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::left * 50);
	_rAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::right * 50);
	_tAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::up * 50);
	_bAtk->GetTrans()->SetPos(_trans->GetPos() + Vector2::down * 50);

	_lAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
	_rAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
	_tAtk->GetComponent<PhysicsBody>()->SetBodyPosition();
	_bAtk->GetComponent<PhysicsBody>()->SetBodyPosition();


}



void GolemEnemy::Release()
{

	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(GetLeftAtk()->GetBody());
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(GetRightAtk()->GetBody());
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(GetTopAtk()->GetBody());
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(GetBottomAtk()->GetBody());

	_lAtk->Release();
	_rAtk->Release();
	_tAtk->Release();
	_bAtk->Release();
	Object::Release();
}

void GolemEnemy::Render()
{
	if(KEYMANAGER->isToggleKey(VK_F5))
		GRAPHICMANAGER->DrawEllipse(_trans->GetPos().x, _trans->GetPos().y, _atkRange, _atkRange, ColorF::AntiqueWhite, 1.5f);
	Object::Render();

}
