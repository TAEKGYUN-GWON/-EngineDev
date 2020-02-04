#include "stdafx.h"
#include "ItemScript.h"
#include "Player.h"
#include"Inventory.h"
#include"Item.h"
void ItemScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;

	if (to->GetName() == "Will")
	{
		Player* will = (Player*)to;
		Item* me = (Item*)_object;
		will->GetInventory()->Insert(me);

	}

}

void ItemScript::CollisionPreSolve(void* obj)
{
	Object* to = (Object*)obj;

	if (to->GetName() == "Will")
	{
		Player* will = (Player*)to;
		Item* me = (Item*)_object;
		will->GetInventory()->Insert(me);
	}
}
