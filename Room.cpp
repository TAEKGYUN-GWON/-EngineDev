#include "stdafx.h"
#include "Room.h"

void Room::Init()
{
	Object::Init();
	_trans->SetPos(RND->getFromIntTo(0, WINSIZEX) , RND->getFromIntTo(WINSIZEY / 2-100, WINSIZEY / 2 + 100));
	
	_trans->SetScale(RND->getFromFloatTo(100.f, 300.f), RND->getFromFloatTo(100.f, 300));

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.f, 1.f, 0.f, false, true);
	_physics->GetBody()->SetFixedRotation(true);


	for (int i = 0; i < 10; i++)
		cout<<i<<endl;

//	_physics->SetBodyActive(false);
}
