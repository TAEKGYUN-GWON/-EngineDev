#include "stdafx.h"
#include "Room.h"

void Room::Init()
{
	Object::Init();
	_trans->SetPos(RND->getFromIntTo(0, WINSIZEX) , WINSIZEY / 2);
	
	_trans->SetScale(RND->getFromFloatTo(100.f, 350.f), RND->getFromFloatTo(100.f, 400.f));

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.f, 1.f, 0.f, false, true);
	_physics->GetBody()->SetFixedRotation(true);
//	_physics->SetBodyActive(false);
}
