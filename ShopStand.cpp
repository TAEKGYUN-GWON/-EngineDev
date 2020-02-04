#include "stdafx.h"
#include "ShopStand.h"
#include "Transform.h"
#include "Sprite.h"
#include"ShopScene.h"

void ShopStand::Init(Vector2 pos, Vector2 scale)
{
	_tag = "ShopObject";

	//가판대의 렉트 만들기
	_trans->SetPos(pos);
	_trans->SetScale(scale);


	_itemPos = _trans->GetPos(); //이게 센터인지 뭔지 모르겠다..
	//★아이템 이미지 네임은(_itemImgName) 헤더에서 SetImgName으로 받음

	_isInUse = false;
	_isItemOn = false;
}

void ShopStand::Release()
{

	Object::Release();
}

void ShopStand::Update()
{

	//BuyItem();

	Object::Update();
}

void ShopStand::Render()
{
	GRAPHICMANAGER->DrawEllipse(
		_trans->GetPos().x, _trans->GetPos().y, 
		_trans->GetScale().x+10, _trans->GetScale().y+10);

	Object::Render();
}

void ShopStand::SetItem(string item)
{
	_item = item;
	_isItemOn = true;
}

void ShopStand::BuyItem()
{
	//물건을 산다
	_isItemOn = false; //아이템 없음
}

