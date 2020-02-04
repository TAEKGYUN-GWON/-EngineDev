#pragma once

#include "Item.h"
#include "Object.h"

#include <vector>

#include "Inventory.h"
#include "Player.h"

#include <tuple>


class Smithy
{
private:

	Graphic* _back;
	Graphic* _blackSmith;
	Graphic* _anvil;
	Graphic* _title;
	Graphic* _itemName;
	Graphic* _upgradable;
	Graphic* _notUpgradeble;
	Graphic* _upgradeRecipe;
	Graphic* _itemList;
	Graphic* _pSword;

	Graphic* _pocket;
	Graphic* _pocketCircle;
	Graphic* _coin;

	Graphic* _material1;
	Graphic* _material2;
	Graphic* _material3;

	Graphic* _mOn1;
	Graphic* _mOn2;
	Graphic* _mOn3;

	string standardStr;
	wstring printStr;

	//켜지기 전에

	Vector2 _smithPos;	//대장장이의 위치

	//대장간이 켜졌습니까?
	bool _isShow;
	bool _isPlayerIn;

	Inventory* _inven;
	Player* _player;
	
	int _recipePrice;
	int _upgradeGap;

	int _m1Count;
	int _m2Count;
	int _m3Count;
	
	/*재료
	크리스탈 에너지
	초록 강철
	골렘의 코어
	*/

	//map<Graphic*, int> _mRecipe;

	tuple<string, int, int> a;

	vector<tuple<string, string, int, int>> _vMaterialCount;
	

public:

	void Init(Inventory* inven);
	void Update();
	void Release();
	void Render();

	void SetSmithPos(Vector2 smithPos) { _smithPos = smithPos; }

	void KeyInput();
	bool CheckPlayerPos();

	void SetIn(bool in) { _isPlayerIn = in; }
	void SetShow(bool show) { _isShow = show; }

	void UpdateMaterial();

	void ShowImage();
	void ShowUI();

	void Buy();
	bool CheckMaterial();
	void Upgrade();

	bool GetSmithy() { return _isShow; }



	void PrintRecipe();

};

