#include "stdafx.h"
#include "CheckStand.h"
#include "Transform.h"

void CheckStand::Init()
{

	_isInUse = false;

	_tag = "ShopObject";
	_name = "CheckStand";

	//가판대의 렉트 만들기
	_trans->SetPos(423, 550);
	_trans->SetScale(25, 25);




	AddComponent<Sprite>();

	Object::Init();
}

void CheckStand::Release()
{

	Object::Release();
}

void CheckStand::Update()
{

	Object::Update();
}

void CheckStand::Render()
{
	GRAPHICMANAGER->DrawEllipse(
		_trans->GetPos().x, _trans->GetPos().y, 
		_trans->GetScale().x, _trans->GetScale().y);
	Object::Render();
}
