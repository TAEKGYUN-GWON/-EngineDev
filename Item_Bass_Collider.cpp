#include "stdafx.h"
#include "Item_Bass_Collider.h"


void Item_Bass_Collider::CollisionBegin(void* obj)
{
	Object* _crashedObj = (Object*)obj;
	Object* _crasherObj = (Object*)_object;

	if (_crashedObj->GetName() == "Will")
	{
		_crasherObj->SetIsActive(false);
	}
}