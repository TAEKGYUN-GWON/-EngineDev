#include "stdafx.h"
#include "ProceduralTest.h"

void ProceduralTest::Init()
{
	Scene::Init();
		for (int i = 0; i < 100; i++)
	{
		Room* room = Object::CreateObject<Room>();
		room->Init();
		Rooms.push_back(room);
	}


}

void ProceduralTest::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown('U'))
		for (Room* r : Rooms)
			r->GetPhysics()->SetSensor(false);

	CAMERA->Control();
	
}

void ProceduralTest::Release()
{
	Scene::Release();
}

void ProceduralTest::Render()
{
	for (Object* child : _children)
	{
		child->Render();

	}
}
