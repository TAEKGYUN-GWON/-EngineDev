#pragma once
#include "Object.h"

enum class EItemType
{
	useable,
	etc
};

class Item : public Object
{

protected:

	typedef Object super;

	//아이템이 소모품인지 그외 다른 모든것인지를 정한다.
	EItemType _type;

	//가격, 아이템의 수량을 나타낸다.
	int _price, _maxCount;

	//아이템이 사용할 이미지를 저장
	Sprite* _image;

	//아이템이 던전안에서 존재한다면 플에이어를 따라가야함
	bool _isDungeon = true;

	//선형보간을 위한 변수
	float _followingMovement;

	PhysicsBody* _physics;

public:
	Item();
	~Item() {}

	virtual void Init();
	virtual void Init(Vector2 pos) {};
	virtual void Update();
	virtual void Render();
	virtual void Release();

	//던전 내에서의 아이템의 움직임
	void FollowPlayer(Vector2 playerPos);

	//Get Something
	int GetMaxCount() { return _maxCount; }
	int GetPrice() { return _price; }
	Vector2 GetPos() { return _trans->GetPos(); }
	EItemType GetType() { return _type; }

	//Set Something
	//void SetItemCount(int count) {
	//	_MaxCount += count;
	//}

	void SetPrice(int price) {
		_price = price;
	}

	void SetPos(Vector2 pos) { _trans->SetPos(pos); }
	void SetInDG(bool _isTrue) { _isDungeon = _isTrue; }

	template <typename T>
	static T* CreateItem(Vector2 pos);
	PhysicsBody* GetPhysics() { return _physics; }
};

#include"Item.hpp"