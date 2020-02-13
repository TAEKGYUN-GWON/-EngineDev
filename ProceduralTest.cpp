#include "stdafx.h"
#include "ProceduralTest.h"
#include "Probe.h"

void ProceduralTest::Init()
{
	Scene::Init();

	SCENEMANAGER->addScene("PG", new StartScene);
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

	GRAPHICMANAGER->AddImage("LeftEdge", dir + L"LeftEdge2.png");
	GRAPHICMANAGER->AddImage("RightEdge", dir + L"RightEdge2.png");

	GRAPHICMANAGER->AddImage("Surround", dir + L"Surround.png");



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

	if (!GetChildrenFromTag("Probe").size() && startExploration)
		SetSubRoom();

	if (KEYMANAGER->isOnceKeyDown('2'))
		startDel = true;

	if (KEYMANAGER->isOnceKeyDown('3'))
		SetTileProperty();

	//if (KEYMANAGER->isOnceKeyDown('5'))
	//	SetWall();

	if (KEYMANAGER->isOnceKeyDown('4'))
		SetTileImg();

	if (KEYMANAGER->isOnceKeyDown('5'))
		DelTile();

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		SCENEMANAGER->changeScene("PG");
		return;
	}

	if (startDel && rooms.size())
		DelRoom();

	CAMERA->Control();
	
}

void ProceduralTest::Release()
{
	tiles.clear();
	rooms.clear();
	selRooms.clear();
	subRooms.clear();
	_vFloors.clear();
	Scene::Release();
}

void ProceduralTest::Render()
{
	Scene::Render();
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
	for (Room* r : rooms)
	{
		r->SetIsRelese();
	}
	rooms.clear();
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
	startExploration = true;
}

void ProceduralTest::SetSubRoom()
{
	for (int i = rooms.size()-1; i >= 0; i--)
	{
		Vector2 rStartIdx = rooms[i]->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 rEndIdx = rooms[i]->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 difference = rEndIdx - rStartIdx;
		bool isSubRoom = false;
		for (int j = 0; j < (int)difference.x * (int)difference.y; j++)
		{
			if (isSubRoom)break;

			int idx = (j % (int)difference.x + (int)rStartIdx.x) + (j / (int)difference.x + (int)rStartIdx.y) * MAP_TILE_MAX_X;

			if (tiles[idx]->GetAttribute() == Attribute::NONE)
			{
				rooms[i]->SetIsSubRoom(true);
				auto s = rooms[i]->AddComponent<Sprite>();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::AntiqueWhite);
				subRooms.push_back(rooms[i]);
				rooms.erase(rooms.begin() + i);
				isSubRoom = true;
				break;
			}
		}
	}

}

void ProceduralTest::SetTileProperty()
{
	//for (int i = 0; i < tiles.size(); i++)
	//{
	//	for (Room* r : subRooms)
	//	{
	//		if (r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) < tiles[i]->GetTrans()->GetPos() &&
	//			r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) > tiles[i]->GetTrans()->GetPos())
	//		{
	//			tiles[i]->SetAttribute(Attribute::NONE);
	//			auto s = tiles[i]->GetSprite();
	//			s->SetFillRect(true);
	//			s->SetRectColor(ColorF::Coral);

	//		}


	//	}

	//	for (Room* r : selRooms)
	//	{
	//		if (r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) < tiles[i]->GetTrans()->GetPos() &&
	//			r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) > tiles[i]->GetTrans()->GetPos())
	//		{
	//			tiles[i]->SetAttribute(Attribute::NONE);
	//			auto s = tiles[i]->GetSprite();
	//			s->SetFillRect(true);
	//			s->SetRectColor(ColorF::Coral);

	//		}

	//	}

	//}

	for (Room* r : subRooms)
	{
		Vector2 rStartIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 rEndIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 difference = rEndIdx - rStartIdx;
		for (int i = 0; i < (int)difference.x * (int)difference.y; i++)
		{
			int idx = (i % (int)difference.x + (int)rStartIdx.x) + (i / (int)difference.x + (int)rStartIdx.y) * MAP_TILE_MAX_X;


			if (tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				//if(tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_UP_2);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);
			}


			else if (tiles[idx]->GetIdY() == (int)rStartIdx.y + 1)
			{
				//if (tiles[idx]->GetWallType() == WallType::WALL_LEFT || tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_UP_1);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);
			}

			else if (tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{
				//if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_DOWN);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::AliceBlue);
			}


			else if (tiles[idx]->GetIdX() == (int)rStartIdx.x)
			{
			//	if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::SeaGreen);
			}

			else if (tiles[idx]->GetIdX() == (int)rEndIdx.x)
			{
				//if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::SeaGreen);
			}
			else
			{
				tiles[idx]->SetAttribute(Attribute::NONE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Coral);
			}

			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);

				tiles[idx + MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
				tiles[idx + MAP_TILE_MAX_X]->SetWallType(WallType::WALL_LEFT);
				s = tiles[idx + MAP_TILE_MAX_X]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{

				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT_DOWN_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);

			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x && tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{
			//	if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT_DOWN_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			

		}

	}

	for (Room* r : selRooms)
	{
		Vector2 rStartIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 rEndIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 difference = rEndIdx - rStartIdx;
		for (int i = 0; i < (int)difference.x * (int)difference.y; i++)
		{
			int idx = (i % (int)difference.x + (int)rStartIdx.x) + (i / (int)difference.x + (int)rStartIdx.y) * MAP_TILE_MAX_X;


			if (tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
			//	if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_UP_2);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);
			}


			else if (tiles[idx]->GetIdY() == (int)rStartIdx.y + 1)
			{
				//if (tiles[idx]->GetWallType() == WallType::WALL_LEFT || tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_UP_1);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);
			}

			else if (tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{
			//	if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_DOWN);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::AliceBlue);
			}


			else if (tiles[idx]->GetIdX() == (int)rStartIdx.x)
			{
				//if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::SeaGreen);
			}

			else if (tiles[idx]->GetIdX() == (int)rEndIdx.x)
			{
				//if (tiles[idx]->GetWallType() == WallType::None)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::SeaGreen);
			}
			else
			{
				tiles[idx]->SetAttribute(Attribute::NONE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Coral);
			}

			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
			//	if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);

				tiles[idx + MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
				tiles[idx + MAP_TILE_MAX_X]->SetWallType(WallType::WALL_LEFT);
				s = tiles[idx + MAP_TILE_MAX_X]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{

				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT_DOWN_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);

			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x && tiles[idx]->GetIdY() == (int)rEndIdx.y)
			{
				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT_DOWN_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
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
					if (i % MAP_TILE_MAX_X == 0)
					{
						tiles[i]->SetAttribute(Attribute::WALL);
						tiles[i]->SetWallType(WallType::WALL_LEFT);
						auto s = tiles[i]->GetSprite();
						s->SetFillRect(true);
						s->SetRectColor(ColorF::Red);
					}
					else
					{
						tiles[i - 1]->SetAttribute(Attribute::WALL);
						tiles[i - 1]->SetWallType(WallType::WALL_LEFT);
						auto s = tiles[i - 1]->GetSprite();
						s->SetFillRect(true);
						s->SetRectColor(ColorF::Red);
					}
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


	for (int i = 0; i < tiles.size(); i++)
	{

		if (i - 1 > 0 && i - MAP_TILE_MAX_X > 0 &&
			i + 1 < tiles.size() && i + MAP_TILE_MAX_X < tiles.size())
		{
			if (tiles[i - 1]->GetAttribute() == Attribute::WALL &&
				tiles[i + 1]->GetAttribute() == Attribute::WALL &&
				tiles[i - MAP_TILE_MAX_X]->GetAttribute() == Attribute::WALL &&
				tiles[i + MAP_TILE_MAX_X]->GetAttribute() == Attribute::WALL)
			{
				tiles[i]->SetAttribute(Attribute::WALL);
				tiles[i]->SetWallType(WallType::WALL_SURROUND);
				auto s = tiles[i + 1]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Ivory);

			}
		}

		switch (tiles[i]->GetWallType())
		{
		case WALL_UP_1:
		{

			if (i - 1 > 0)
			{
				if (tiles[i - 1]->GetAttribute() != Attribute::WALL &&
					tiles[i - 1]->GetAttribute() != Attribute::NONE)
				{
					tiles[i - 1]->SetAttribute(Attribute::WALL);
					tiles[i - 1]->SetWallType(WallType::WALL_LEFT);
					auto s = tiles[i - 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Brown);
				}
			}
			if (i + 1 < tiles.size())
			{
				if (tiles[i + 1]->GetAttribute() != Attribute::WALL &&
					tiles[i + 1]->GetAttribute() != Attribute::NONE)
				{
					tiles[i + 1]->SetAttribute(Attribute::WALL);
					tiles[i + 1]->SetWallType(WallType::WALL_RIGHT);
					auto s = tiles[i + 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Brown);
				}
			}

		}
			break;
		case WALL_UP_2:
		{
			if (i - 1 > 0)
			{
				if (tiles[i - 1]->GetAttribute() != Attribute::WALL &&
					tiles[i - 1]->GetAttribute() != Attribute::NONE)
				{
					tiles[i - 1]->SetAttribute(Attribute::WALL);
					tiles[i - 1]->SetWallType(WallType::WALL_LEFT_EDGE);
					auto s = tiles[i - 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Brown);
				}
			}
			if (i + 1 < tiles.size())
			{
				if (tiles[i + 1]->GetAttribute() != Attribute::WALL &&
					tiles[i + 1]->GetAttribute() != Attribute::NONE)
				{
					tiles[i + 1]->SetAttribute(Attribute::WALL);
					tiles[i + 1]->SetWallType(WallType::WALL_RIGHT_EDGE);
					auto s = tiles[i + 1]->GetSprite();
					s->SetFillRect(true);
					s->SetRectColor(ColorF::Brown);
				}
			}
		}
			break;
		case WALL_DOWN:
		{

		}
			break;
		case WALL_LEFT:
		{

		}
			break;
		case WALL_RIGHT:
		{

		}
			break;
		case WALL_LEFT_EDGE:
		{

		}
			break;
		case WALL_RIGHT_EDGE:
		{

		}
			break;
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

		case WALL_LEFT_EDGE:
		{
			t->SetImgName("LeftEdge");
			t->GetSprite()->SetImgName("LeftEdge");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT)+ Vector2::left * 10);
		}
		break;
		case WALL_RIGHT_EDGE:
		{
			t->SetImgName("RightEdge");
			t->GetSprite()->SetImgName("RightEdge");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT));
		}
		break;
		case WALL_SURROUND:
		{
			t->SetImgName("Surround");
			t->GetSprite()->SetImgName("Surround");
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
