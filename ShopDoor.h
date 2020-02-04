#pragma once
#include "Object.h"
#include "Sprite.h"

class ShopDoor :public Object
{
private:

	Sprite* _sprite;

//얘는 Npc가 문이랑 닿았는지 알려줘야함
//닿으면 문을 열고 몇초후에 다시 닫아줘야 함
//근데 여러명이 나가면 몇초후에 나가면 안되니까
//충돌중인 NPC가 있으면 열고, 없으면 닫고 이런식으로 해야될듯

	//충돌은 NpcManager에서 할거니까
	//NpcManager를 include해야하나?

	//아니면 그냥 NpcManager에서
	//충돌시 여기다가 문열어주는거 SetDoor해도 될듯

public:
	virtual void Init() override;
	virtual void Update() override;

};

