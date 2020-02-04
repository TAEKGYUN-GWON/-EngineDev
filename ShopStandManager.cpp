#include "stdafx.h"
#include "ShopStandManager.h"

void ShopStandManager::Init()
{
	ShopStand* shopStand;
	//1사분면부터 반시계 방향으로 1, 2, 3, 4순서로 들어감.
	{
		shopStand = Object::CreateObject<ShopStand>();
		shopStand->Init(Vector2(263, 573), Vector2(25, 25));
		shopStand->SetName("ShopStand1");
		shopStand->SetIsInUse(false);

		_vShopStand.push_back(shopStand);
	}
	{
		shopStand = Object::CreateObject<ShopStand>();
		shopStand->Init(Vector2(213, 573), Vector2(25, 25));
		shopStand->SetName("ShopStand2");
		shopStand->SetIsInUse(false);

		_vShopStand.push_back(shopStand);
	}
	{
		shopStand = Object::CreateObject<ShopStand>();
		shopStand->Init(Vector2(213, 623), Vector2(25, 25));
		shopStand->SetName("ShopStand3");
		shopStand->SetIsInUse(false);

		_vShopStand.push_back(shopStand);
	}
	{
		shopStand = Object::CreateObject<ShopStand>();
		shopStand->Init(Vector2(263, 623), Vector2(25, 25));
		shopStand->SetName("ShopStand4");
		shopStand->SetIsInUse(false);

		_vShopStand.push_back(shopStand);
	}
}

void ShopStandManager::Release()
{
}

void ShopStandManager::Update()
{
}
