#include "stdafx.h"
#include "ProceduralTest.h"
#include "Probe.h"

void ProceduralTest::Init()
{
	Scene::Init();


	startDel = endCreate = count = timer = endPush = maxY = 0;



	Object* obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(MAP_MAX_WIDTH / 2, -5);
	obj->GetTrans()->SetScale(MAP_MAX_WIDTH, 10);
	_vFloors.push_back(obj);

	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(-5, MAP_MAX_HEIGHT / 2);
	obj->GetTrans()->SetScale(10, MAP_MAX_HEIGHT);
	_vFloors.push_back(obj);

	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(MAP_MAX_WIDTH + 5, MAP_MAX_HEIGHT / 2);
	obj->GetTrans()->SetScale(10, MAP_MAX_HEIGHT);
	_vFloors.push_back(obj);

	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(MAP_MAX_WIDTH / 2, MAP_MAX_HEIGHT + 5);
	obj->GetTrans()->SetScale(MAP_MAX_WIDTH, 10);
	_vFloors.push_back(obj);

	_ast = new Astar;

	for (Object* obj : _vFloors)
	{
		auto p = obj->AddComponent<PhysicsBody>();
		p->Init(BodyType::STATIC, 1);
	}
	//SetTile();
	for (int i = 0; i < CREATE_ROOM_MAX; i++)
	{
		Room* room = Object::CreateObject<Room>();
		room->Init();
		rooms.push_back(room);
	}
	SetTile();
}

void ProceduralTest::Update()
{
	Scene::Update();
	
	for (Object* c : GetChildrenFromTag("Prove"))
		if (!c->GetIsActive())
			c->Release();

	if (KEYMANAGER->isOnceKeyDown('1'))
		PushRoom();

	if (KEYMANAGER->isOnceKeyDown('2'))
		endPush = true;

	if (KEYMANAGER->isOnceKeyDown('3'))
		Exploration();

	if (KEYMANAGER->isOnceKeyDown('4'))
		SetSubRoom();

	if (KEYMANAGER->isOnceKeyDown('5'))
		startDel = true;

	if (KEYMANAGER->isOnceKeyDown('6'))
		SetTileProperty();

	if (KEYMANAGER->isOnceKeyDown('7'))
		DelTile();

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
	Scene::Render();
}

void ProceduralTest::CreateRoom()
{

}

void ProceduralTest::PushRoom()
{
	for (Room* r : rooms)
		r->GetPhysics()->SetSensor(false);
}

void ProceduralTest::SelRoom()
{
	int randRoomNum = RND->getInt(rooms.size());
	rooms[randRoomNum]->SetIsMainRoom(true);
	auto s = rooms[randRoomNum]->AddComponent<Sprite>();
	s->Init();
	s->SetFillRect(true);
	s->SetRectColor(ColorF::Red);
	selRooms.push_back(rooms[randRoomNum]);

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
	for (int i = 0; i < MAP_TILE_MAX_Y; ++i)
	{
		for (int j = 0; j < MAP_TILE_MAX_X+1; ++j)
		{
			int index = j + MAP_TILE_MAX_Y * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->AddComponent<Sprite>();
			tile->SetAttribute(Attribute::NONE_MOVE);
			tiles.push_back(tile);
		}
	}
	_ast->Init(tiles, MAP_TILE_MAX_X + 1, MAP_TILE_MAX_Y);
}

void ProceduralTest::Exploration()
{
	for (int i = 0; i < selRooms.size(); i++)
	{
		Probe* probe = Object::CreateObject<Probe>();
		probe->Init(selRooms[i]->GetTrans()->GetPos());
		probe->SetTiles(&tiles);

		if (i != selRooms.size() - 1)
			probe->SetPath(_ast->PathFinderFor4Way(probe->GetTrans()->GetPos(),
				selRooms[i + 1]->GetTrans()->GetPos()));
		else
			probe->SetPath(_ast->PathFinderFor4Way(probe->GetTrans()->GetPos(),
				selRooms[0]->GetTrans()->GetPos()));
	}
}

void ProceduralTest::SetSubRoom()
{
	for (int i = rooms.size()-1; i >= 0; i--)
	{
		if (rooms[i]->GetIsSubRoom())
		{
			auto s = rooms[i]->AddComponent<Sprite>();
			s->SetFillRect(true);
			s->SetRectColor(ColorF::AntiqueWhite);
			subRooms.push_back(rooms[i]);
			rooms.erase(rooms.begin() + i);
		}
	}
}

void ProceduralTest::SetTileProperty()
{
	for (Tile* t : tiles)
	{
		for (Room* r : subRooms)
		{
			if (r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) < t->GetTrans()->GetPos() &&
				r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) > t->GetTrans()->GetPos())
			{
				t->SetAttribute(Attribute::NONE);
				auto s = t->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Coral);

			}

		}

		for (Room* r : selRooms)
		{
			if (r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) < t->GetTrans()->GetPos() &&
				r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) > t->GetTrans()->GetPos())
			{
				t->SetAttribute(Attribute::NONE);
				auto s = t->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Coral);

			}

		}

	}
}

void ProceduralTest::SetTileImg()
{

}

void ProceduralTest::DelTile()
{

	for (int i = tiles.size()-1; i >= 0; i--)
	{
		if (tiles[i]->GetAttribute() == Attribute::NONE_MOVE)
		{
			tiles[i]->Release();
			tiles.erase(tiles.begin() + i);
		}
	}

}
