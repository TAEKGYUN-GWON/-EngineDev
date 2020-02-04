#pragma once
#include"Player.h"
#include "Inventory.h"
class UiManager
{
private:

	Graphic* _coin;
	Graphic* _bag;
	Graphic* _bagButton;
	Graphic* _potionButton;
	Graphic* _heart;
	Graphic* _weapon;
	Graphic* _hp;
	int hpMaxX;
	int hpMaxY;
	//UiObject* _coin;
	//UiObject* _bag;
	//UiObject* _bagButton;
	//UiObject* _potionButton;
	//UiObject* _heart;
	//UiObject* _weapon;
	Inventory* inven;
	Player* player;

public:
	void Init();
	void Update();
	void Render();
	void SetInvenLink(Inventory* inven) { this->inven = inven; }
};

