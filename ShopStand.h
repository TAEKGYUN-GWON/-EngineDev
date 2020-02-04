#pragma once
#include "Object.h"
#include "Item.h"

#include"Maptool.h"
#define SHOPTILEMAXX 22
#define SHOPTILEMAXY 28
class ShopScene;
class ShopStand :public Object
{
private:
	Vector2 _itemPos; //아이템 이미지 보여줄 좌표
	string _item; //올라갈 아이템 이미지 네임
	//bool _isActive; //부모꺼 사용, 이미지 올라가면 true 상태
	Tile* _tiles[SHOPTILEMAXX * SHOPTILEMAXY];
	tagTile _tagTiles[SHOPTILEMAXX * SHOPTILEMAXY];
	//Item* _item;

	bool _isItemOn;

	bool _isInUse; //npc가 충돌해서 계산중이면 사용중임

public:

	virtual void Init(Vector2 pos, Vector2 scale);
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render()override;

	//이미지 네임은 인벤토리에서 줘야 할 것 같음..
	void SetItem(string item); //플레이어가 아이템 셋팅하기
	void BuyItem();


	bool GetActive() { return _isActive; }
	void SetActive(bool isActive) { _isActive = isActive; }

	bool GetIsInUse() { return _isInUse; }
	void SetIsInUse(bool isinuse) { _isInUse = isinuse; }

	bool GetIsItemOn() { return _isItemOn; }
	Vector2 GetItemPos() { return _itemPos; }



};

