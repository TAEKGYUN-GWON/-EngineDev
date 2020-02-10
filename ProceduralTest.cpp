#include "stdafx.h"
#include "ProceduralTest.h"

void ProceduralTest::Init()
{
	Scene::Init();


	startDel = endCreate = count = timer = endPush = maxY = 0;
}

void ProceduralTest::Update()
{
	Scene::Update();


	if (count < CREATE_ROOM_MAX &&!endCreate)
		CreateRoom();
	


	if (KEYMANAGER->isOnceKeyDown('1'))
		PushRoom();

	if (KEYMANAGER->isOnceKeyDown('2'))
		endPush = true;

	if (KEYMANAGER->isOnceKeyDown('3'))
		startDel = true;

	if (endPush && count < SELECT_ROOM)
		SelRoom();

	if (startDel && rooms.size())
		DelRoom();


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

void ProceduralTest::CreateRoom()
{
	Room* room = Object::CreateObject<Room>();
	room->Init();
	rooms.push_back(room);
	count++;
	if (count == CREATE_ROOM_MAX)
	{
		count = 0;
		endCreate = true;
	}
}

void ProceduralTest::PushRoom()
{
	for (Room* r : rooms)
		r->GetPhysics()->SetSensor(false);
}

void ProceduralTest::SelRoom()
{
	int randRoomNum = RND->getInt(rooms.size());
	auto s = rooms[randRoomNum]->AddComponent<Sprite>();
	s->Init();
	s->SetFillRect(true);
	s->SetRectColor(ColorF::Red);
	selRooms.push_back(rooms[randRoomNum]);

	if (maxY > rooms[randRoomNum]->GetTrans()->GetPos().y)
	{
		if(currentRoom) currentRoom->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		maxY = rooms[randRoomNum]->GetTrans()->GetPos().y;
		currentRoom = rooms[randRoomNum];
		currentRoom->GetComponent<Sprite>()->SetRectColor(ColorF::Blue);
	}
	rooms.erase(rooms.begin() + randRoomNum);
	count++;
}

void ProceduralTest::DelRoom()
{
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(rooms[0]->GetPhysics()->GetBody());
	rooms[0]->Release();
	rooms.erase(rooms.begin());

}

void ProceduralTest::SetTile()
{
	//for(int)
}
