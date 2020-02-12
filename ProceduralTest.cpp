#include "stdafx.h"
#include "ProceduralTest.h"
#include "Probe.h"

void ProceduralTest::Init()
{
	Scene::Init();


	startDel = endCreate = count = timer = endPush = maxY = 0;

	wstring dir = L"Resource/Wizard/Tile/";
	for (int i = 1; i <= 4; i++)
	{
		string str = "Tile";
		wstring item = to_wstring(i) + L".png";
		GRAPHICMANAGER->AddImage(str + to_string(i), dir + item);
	}
	GRAPHICMANAGER->AddImage("WallUp_1", dir + L"WallUp_1.png");
	GRAPHICMANAGER->AddImage("WallUp_2", dir + L"WallUp_2.png");

	GRAPHICMANAGER->AddImage("WallDown", dir + L"WallDown.png");

	GRAPHICMANAGER->AddImage("WallLeft", dir + L"WallLeft.png");
	GRAPHICMANAGER->AddImage("WallRight", dir + L"WallRight.png");

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
	PushRoom();
	for(int i = 0; i< SELECT_ROOM;i++)
		SelRoom();
	SetTile();
}

void ProceduralTest::Update()
{
	Scene::Update();
	for (Object* c : GetChildrenFromTag("Probe"))
	{
		Probe* p = (Probe*)c;
		if (!p->GetPathSize()) p->SetIsRelese();
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
		cout << "FPS : " << TIMEMANAGER->GetFps() << endl;



	if (KEYMANAGER->isOnceKeyDown('1'))
		Exploration();

	if (KEYMANAGER->isOnceKeyDown('2'))
		SetSubRoom();

	if (KEYMANAGER->isOnceKeyDown('3'))
		startDel = true;

	if (KEYMANAGER->isOnceKeyDown('4'))
		SetTileProperty();

	if (KEYMANAGER->isOnceKeyDown('5'))
		SetWall();

	if (KEYMANAGER->isOnceKeyDown('6'))
		SetTileImg();

	if (KEYMANAGER->isOnceKeyDown('7'))
		DelTile();


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
		for (int j = 0; j < MAP_TILE_MAX_X; ++j)
		{
			int index = j + MAP_TILE_MAX_Y * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->AddComponent<Sprite>();
			tile->SetAttribute(Attribute::NONE_MOVE);
			tiles.push_back(tile);
		}
	}
	_ast->Init(tiles, MAP_TILE_MAX_X, MAP_TILE_MAX_Y);
}

void ProceduralTest::Exploration()
{
	for (int i = 0; i < selRooms.size(); i++)
	{
		Probe* probe = Object::CreateObject<Probe>();

		if (i != selRooms.size() - 1)
		{
			probe->Init(selRooms[i]->GetTrans()->GetPos(),
				_ast->PathFinderFor4Way(selRooms[i]->GetTrans()->GetPos(),
					selRooms[i + 1]->GetTrans()->GetPos()));
		}
		else
		{
			probe->Init(selRooms[i]->GetTrans()->GetPos(),
				_ast->PathFinderFor4Way(selRooms[i]->GetTrans()->GetPos(),
					selRooms[0]->GetTrans()->GetPos()));
		}
			probe->SetTiles(&tiles);
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

void ProceduralTest::SetWall()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->GetAttribute() == Attribute::NONE)
		{

			if (i - MAP_TILE_MAX_X >= 0)
			{
				if (tiles[i - MAP_TILE_MAX_X]->GetAttribute() != Attribute::NONE &&
					tiles[i - MAP_TILE_MAX_X]->GetAttribute() != Attribute::WALL)
				{
					tiles[i - MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
					tiles[i - MAP_TILE_MAX_X]->SetWallType(WallType::WALL_UP_1);
					auto s = tiles[i - MAP_TILE_MAX_X]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Lime);

					if (i - (MAP_TILE_MAX_X * 2) >= 0)
					{
						tiles[i - (MAP_TILE_MAX_X * 2)]->SetAttribute(Attribute::WALL);
						tiles[i - (MAP_TILE_MAX_X * 2)]->SetWallType(WallType::WALL_UP_2);
						s = tiles[i - (MAP_TILE_MAX_X * 2)]->GetSprite();
						s->SetFillRect(true);
						s->SetRectColor(ColorF::Green);
					}
				}
			}

			if (i + MAP_TILE_MAX_X < tiles.size())
			{
				if (tiles[i + MAP_TILE_MAX_X]->GetAttribute() != Attribute::NONE&&
					tiles[i + MAP_TILE_MAX_X]->GetAttribute() != Attribute::WALL)
				{
					tiles[i + MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
					tiles[i + MAP_TILE_MAX_X]->SetWallType(WallType::WALL_DOWN);
					auto s = tiles[i + MAP_TILE_MAX_X]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::AliceBlue);
				}
			}


			if (i - 1 >= 0)
			{
				if (tiles[i - 1]->GetAttribute() != Attribute::NONE&&
					tiles[i - 1]->GetAttribute() != Attribute::WALL)
				{
					tiles[i - 1]->SetAttribute(Attribute::WALL);
					tiles[i - 1]->SetWallType(WallType::WALL_LEFT);
					auto s = tiles[i - 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Red);
				}

			}

			if (i + 1 < tiles.size())
			{
				if (tiles[i + 1]->GetAttribute() != Attribute::NONE&&
					tiles[i + 1]->GetAttribute() != Attribute::WALL)
				{
					tiles[i + 1]->SetAttribute(Attribute::WALL);
					tiles[i + 1]->SetWallType(WallType::WALL_RIGHT);
					auto s = tiles[i + 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Red);
				}

			}
			
		}
	}
}

void ProceduralTest::SetTileImg()
{
	for (Tile* t : tiles)
	{
		if (t->GetAttribute() == Attribute::NONE)
		{
			int rand = RND->getFromIntTo(1, 4);
			t->SetImgName("Tile"+to_string(rand));
			t->GetSprite()->SetImgName("Tile" + to_string(rand));
		}

		/*
		"WallUp_1",
		"WallUp_2",

		"WallDown",

		"WallLeft",
		"WallRight"
		*/

		switch (t->GetWallType())
		{
		case WALL_UP_1:
		{
			t->SetImgName("WallUp_1");
			t->GetSprite()->SetImgName("WallUp_1");
		}
			break;
		case WALL_UP_2:
		{
			t->SetImgName("WallUp_2");
			t->GetSprite()->SetImgName("WallUp_2");
		}
			break;
		case WALL_DOWN:
		{
			t->SetImgName("WallDown");
			t->GetSprite()->SetImgName("WallDown");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPos()+ Vector2::up * 20);
		}
			break;
		case WALL_LEFT:
		{
			t->SetImgName("WallLeft");
			t->GetSprite()->SetImgName("WallLeft");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT) + Vector2::left * 10);
		}
			break;
		case WALL_RIGHT:
		{
			t->SetImgName("WallRight");
			t->GetSprite()->SetImgName("WallRight");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT));
		}
			break;
		}
	}
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
