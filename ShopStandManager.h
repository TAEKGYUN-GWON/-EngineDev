#pragma once
#include "ShopStand.h"

class ShopStandManager
{
private:
	vector<ShopStand*> _vShopStand;


public:
	void Init();
	void Release();
	void Update();

	vector<ShopStand*> GetShopStandVector() { return _vShopStand; }


};

