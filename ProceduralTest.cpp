#include "stdafx.h"
#include "ProceduralTest.h"
#include "Probe.h"

void ProceduralTest::Init()
{
	Scene::Init();

	SCENEMANAGER->addScene("PG", new StartScene);
	startDel = endCreate = count = timer = endPush = maxY = 0;

	wstring Tiledir = L"Resource/Wizard/Tile/";
	wstring Objectdir = L"Resource/Wizard/Object/";
	for (int i = 1; i <= 4; i++)
	{
		string str = "Tile";
		wstring item = to_wstring(i) + L".png";
		GRAPHICMANAGER->AddImage(str + to_string(i), Tiledir + item);
	}
	GRAPHICMANAGER->AddImage("WallUp_1", Tiledir + L"WallUp_1.png");
	GRAPHICMANAGER->AddImage("WallUp_2", Tiledir + L"WallUp_2.png");
	GRAPHICMANAGER->AddImage("WallUp", Tiledir + L"WallUp.png");



	GRAPHICMANAGER->AddImage("WallDown", Tiledir + L"WallDown.png");

	GRAPHICMANAGER->AddImage("WallLeft", Tiledir + L"WallLeft.png");
	GRAPHICMANAGER->AddImage("WallRight", Tiledir + L"WallRight.png");

	GRAPHICMANAGER->AddImage("LeftEdge", Tiledir + L"LeftEdge2.png");
	GRAPHICMANAGER->AddImage("RightEdge", Tiledir + L"RightEdge2.png");

	GRAPHICMANAGER->AddImage("Surround", Tiledir + L"Surround.png");

	GRAPHICMANAGER->AddImage("Carpet", Tiledir + L"Carpet.png");
	GRAPHICMANAGER->AddImage("Grate", Tiledir + L"Grate.png");

	GRAPHICMANAGER->AddImage("SmallProps", Objectdir + L"SmallProps.png");
	GRAPHICMANAGER->AddImage("None", Objectdir + L"empty.png");
	GRAPHICMANAGER->AddImage("PillarIce", Objectdir + L"PillarIce.png");
	GRAPHICMANAGER->AddImage("ArchwayBodyIce", Objectdir + L"ArchwayBodyIce.png");
	GRAPHICMANAGER->AddImage("IceBanner", Objectdir + L"IceBanner.png");
	GRAPHICMANAGER->AddImage("ChaosBanner", Objectdir + L"ChaosBanner.png");



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
	for (int i = 0; i < SELECT_ROOM; i++)
		SelRoom();
	SetTile();

}

void ProceduralTest::Update()
{
	Scene::Update();

	SetScene();

	if (KEYMANAGER->isOnceKeyDown('5'))
		DelTile();

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		SCENEMANAGER->changeScene("PG");
		return;
	}



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
void ProceduralTest::PhysicsUpdate()
{
#ifdef _DEBUG

	_b2World->Step(timeStep, velocityIterations, positionIterations);
	for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext())
	{

		if (!body->GetUserData())
		{
			b2Body* deletedObject = body;
			body = body->GetNext();
			_b2World->DestroyBody(deletedObject);
			continue;
		}
		if (((Object*)body->GetUserData())->GetTrans() != nullptr)
		{
			Transform* now = ((Object*)body->GetUserData())->GetTrans();
			PhysicsBody* nowP = ((Object*)body->GetUserData())->GetComponent<PhysicsBody>();
			now->SetPos(nowP->GetBodyPosition());
		}
	}

#else
	for (int i = 0; i < 50; i++)
	{
		_b2World->Step(timeStep, velocityIterations, positionIterations);
		for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext())
		{

			if (!body->GetUserData())
			{
				b2Body* deletedObject = body;
				body = body->GetNext();
				_b2World->DestroyBody(deletedObject);
				continue;
			}
			if (((Object*)body->GetUserData())->GetTrans() != nullptr)
			{
				Transform* now = ((Object*)body->GetUserData())->GetTrans();
				PhysicsBody* nowP = ((Object*)body->GetUserData())->GetComponent<PhysicsBody>();
				now->SetPos(nowP->GetBodyPosition());
			}
		}
	}
#endif

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
	mainRooms.push_back(rooms[randRoomNum]);
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
	_ast->Init(&tiles, MAP_TILE_MAX_X, MAP_TILE_MAX_Y);
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
	for (int i = rooms.size() - 1; i >= 0; i--)
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
				selRooms.push_back(rooms[i]);
				rooms.erase(rooms.begin() + i);
				isSubRoom = true;
				break;
			}
		}
	}

}

void ProceduralTest::SetTileProperty()
{
#pragma region ¹«´ý
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

	/*for (Room* r : subRooms)
	{
		Vector2 rStartIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 rEndIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		Vector2 difference = rEndIdx - rStartIdx;
		for (int i = 0; i < (int)difference.x * (int)difference.y; i++)
		{
			int idx = (i % (int)difference.x + (int)rStartIdx.x) + (i / (int)difference.x + (int)rStartIdx.y) * MAP_TILE_MAX_X;


			if (tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
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


			}
			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y + 1)
			{
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT);
				auto s = tiles[idx]->GetSprite();
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

	}*/

#pragma endregion


#pragma region ¼¿·ºÆ®
	for (Room* r : selRooms)
	{
		Vector2 rStartIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		rStartIdx = Vector2((int)rStartIdx.x, (int)rStartIdx.y);
		Vector2 rEndIdx = r->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) / Vector2(TILE_WIDTH, TILE_HEIGHT);
		rEndIdx = Vector2((int)rEndIdx.x, (int)rEndIdx.y);
		Vector2 difference = rEndIdx - rStartIdx;
		for (int i = 0; i < (int)difference.x * (int)difference.y; i++)
		{
			int idx = (i % (int)difference.x + (int)rStartIdx.x) + (i / (int)difference.x + (int)rStartIdx.y) * MAP_TILE_MAX_X;

			if (tiles[idx]->GetName() == "Road") continue;

			if (tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_UP_2);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);

				tiles[idx + MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
				tiles[idx + MAP_TILE_MAX_X]->SetWallType(WallType::WALL_UP_1);
				s = tiles[idx + MAP_TILE_MAX_X]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Green);
			}


			//else if (tiles[idx]->GetIdY() == (int)rStartIdx.y + 1)
			//{
			//	//if (tiles[idx]->GetWallType() == WallType::WALL_LEFT || tiles[idx]->GetWallType() == WallType::None)continue;
			//	tiles[idx]->SetAttribute(Attribute::WALL);
			//	tiles[idx]->SetWallType(WallType::WALL_UP_1);
			//	auto s = tiles[idx]->GetSprite();
			//	s->SetFillRect(true);
			//	s->SetRectColor(ColorF::Green);
			//}

			else if (tiles[idx]->GetIdY() == (int)rEndIdx.y - 1)
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

			else if (tiles[idx]->GetIdX() == (int)rEndIdx.x - 1)
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


			}
			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rStartIdx.y + 1)
			{
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rStartIdx.x && tiles[idx]->GetIdY() == (int)rEndIdx.y - 1)
			{

				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_LEFT_DOWN_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);

			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x - 1 && tiles[idx]->GetIdY() == (int)rStartIdx.y)
			{
				//if (tiles[idx]->GetAttribute() == Attribute::NONE)continue;
				tiles[idx]->SetAttribute(Attribute::WALL);
				tiles[idx]->SetWallType(WallType::WALL_RIGHT_EDGE);
				auto s = tiles[idx]->GetSprite();
				s->SetFillRect(true);
				s->SetRectColor(ColorF::Aqua);
			}

			if (tiles[idx]->GetIdX() == (int)rEndIdx.x - 1 && tiles[idx]->GetIdY() == (int)rEndIdx.y - 1)
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
#pragma endregion

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->GetName() != "Road")continue;

		if (tiles[i - 1]->GetAttribute() != Attribute::NONE)
		{
			tiles[i - 1]->SetAttribute(Attribute::WALL);
			tiles[i - 1]->SetWallType(WallType::WALL_LEFT);
			auto s = tiles[i - 1]->GetSprite();
			s->SetFillRect(true);
			s->SetRectColor(ColorF::SeaGreen);
		}

		if (tiles[i + 1]->GetAttribute() != Attribute::NONE)
		{
			tiles[i + 1]->SetAttribute(Attribute::WALL);
			tiles[i + 1]->SetWallType(WallType::WALL_RIGHT);
			auto s = tiles[i + 1]->GetSprite();
			s->SetFillRect(true);
			s->SetRectColor(ColorF::SeaGreen);
		}

		if (tiles[i + MAP_TILE_MAX_X]->GetAttribute() != Attribute::NONE)
		{
			tiles[i + MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
			tiles[i + MAP_TILE_MAX_X]->SetWallType(WallType::WALL_DOWN);
			auto s = tiles[i + MAP_TILE_MAX_X]->GetSprite();
			s->SetFillRect(true);
			s->SetRectColor(ColorF::SeaGreen);
		}

		if (tiles[i - MAP_TILE_MAX_X]->GetAttribute() != Attribute::NONE)
		{
			tiles[i - MAP_TILE_MAX_X]->SetAttribute(Attribute::WALL);
			tiles[i - MAP_TILE_MAX_X]->SetWallType(WallType::WALL_UP);
			auto s = tiles[i - MAP_TILE_MAX_X]->GetSprite();
			s->SetFillRect(true);
			s->SetRectColor(ColorF::SeaGreen);
		}

	}

}

void ProceduralTest::SetTileObjet()
{
	//"Carpet"
	//"Grate"
	//"SmallProps"
	//"PillarIce"
	for (Room* r : selRooms)
	{
		r->SetObject();
		for (auto o : r->GetRoomObjects())
		{
			Vector2 v2Idx((int)o.second.pos.x / TILE_WIDTH, (int)o.second.pos.y / TILE_HEIGHT);
			int idx = v2Idx.x + v2Idx.y * MAP_TILE_MAX_X;

			if (o.first == "Carpet")
			{
				tiles[idx]->SetName("Carpet");
				Object* child = Object::CreateObject<Object>();
				child->GetTrans()->SetPos(tiles[idx]->GetTrans()->GetPos());
				auto s = child->AddComponent<Sprite>();
				s->SetImgName("Carpet");
				s->SetPosition(tiles[idx]->GetTrans()->GetPos() + (Vector2::up + Vector2::left) * 30);
			}
			else if (o.first == "Grate")
			{
				Object* child = Object::CreateObject<Object>();
				child->GetTrans()->SetPos(tiles[idx]->GetTrans()->GetPos());
				auto s = child->AddComponent<Sprite>();
				s->SetImgName("Grate");
				s->SetPosition(tiles[idx]->GetTrans()->GetPos() + (Vector2::up + Vector2::left) * 30);
			}
			else if (o.first == "SmallProps")
			{
				auto s = tiles[idx]->GetSprite();
				s->SetImgName("SmallProps");
				s->SetPivot(PIVOT::BOTTOM);
				s->SetPosition(s->GetPosition() + Vector2::down * 15);
				tiles[idx]->SetAttribute(Attribute::WALL);
			}
			else if (o.first == "PillarIce")
			{
				auto s = tiles[idx]->GetSprite();
				s->SetImgName("PillarIce");
				s->SetPivot(PIVOT::BOTTOM);
				s->SetPosition(s->GetPosition() + Vector2::down * 15);
				tiles[idx]->SetAttribute(Attribute::WALL);
			}
		}
	}

	//"IceBanner"
	//"ChaosBanner"

	for (Tile* t : tiles)
	{
		if (t->GetWallType() != WallType::WALL_UP_2) continue;

		int rand = RND->getInt(50);

		if (rand != 7)continue;

		int bannerType = RND->getInt(2);
		Object* banner = Object::CreateObject<Object>(t);
		banner->GetTrans()->SetPos(t->GetTrans()->GetPos());
		auto s = banner->AddComponent<Sprite>();

		if (bannerType)
			s->SetImgName("IceBanner");
		else
			s->SetImgName("ChaosBanner");
		s->SetPosition(banner->GetTrans()->GetPos() + Vector2::down * 10);
	}

	int hubSelect = RND->getInt(mainRooms.size());
	mainRooms[hubSelect]->SetHubForBossRoom(true);

	//"ArchwayBodyIce"

	{
		Vector2 vec2BossIdx((int)mainRooms[hubSelect]->GetTrans()->GetPosToPivot(TF_PIVOT::TOP).x / TILE_WIDTH, ((int)mainRooms[hubSelect]->GetTrans()->GetPosToPivot(TF_PIVOT::TOP).y / TILE_HEIGHT) + 1);

		int bossIdx = vec2BossIdx.x + vec2BossIdx.y * MAP_TILE_MAX_X;
		//tiles[idx - MAP_TILE_MAX_X]->
		tiles[bossIdx]->SetWallType(WallType::BOSS_HUB);
		tiles[bossIdx]->GetSprite()->SetRectColor(ColorF::DarkBlue);
		tiles[bossIdx - 1]->SetWallType(WallType::BOSS_HUB);
		tiles[bossIdx - 1]->GetSprite()->SetRectColor(ColorF::DarkBlue);
		tiles[bossIdx + 1]->SetWallType(WallType::BOSS_HUB);
		tiles[bossIdx + 1]->GetSprite()->SetRectColor(ColorF::DarkBlue);

		tiles[bossIdx]->GetSprite()->SetImgName("ArchwayBodyIce");
		tiles[bossIdx - 1]->GetSprite()->SetImgName("None");

		tiles[bossIdx + 1]->GetSprite()->SetImgName("None");

		tiles[bossIdx - 1 - MAP_TILE_MAX_X]->GetSprite()->SetImgName("None");
		tiles[bossIdx + 1 - MAP_TILE_MAX_X * 2]->GetSprite()->SetImgName("None");

		tiles[bossIdx - MAP_TILE_MAX_X]->GetSprite()->SetImgName("None");
		tiles[bossIdx - MAP_TILE_MAX_X * 2]->GetSprite()->SetImgName("None");

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
				if (tiles[i + MAP_TILE_MAX_X]->GetAttribute() != Attribute::NONE &&
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

				if (tiles[i - 1]->GetAttribute() != Attribute::NONE &&
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
				if (tiles[i + 1]->GetAttribute() != Attribute::NONE &&
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
			t->SetImgName("Tile" + to_string(rand));
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
		case WALL_UP:
		{
			t->SetImgName("WallUp");
			t->GetSprite()->SetImgName("WallUp");
			t->GetSprite()->SetPosition(t->GetTrans()->GetPos() + Vector2::down * 10);
		}
		break;
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

			t->GetSprite()->SetPosition(t->GetTrans()->GetPos() + Vector2::up * 20);
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
			t->GetSprite()->SetPosition(t->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT) + Vector2::left * 10);
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
	SetTileObjet();
}

void ProceduralTest::DelTile()
{

	for (int i = tiles.size() - 1; i >= 0; i--)
	{
		if (tiles[i]->GetAttribute() == Attribute::NONE_MOVE)
		{
			tiles[i]->Release();
			tiles.erase(tiles.begin() + i);
		}
	}

}

void ProceduralTest::SetScene()
{

	timer += TIMEMANAGER->getElapsedTime();

	for (Object* c : GetChildrenFromTag("Probe"))
	{
		Probe* p = (Probe*)c;
		if (!p->GetPathSize()) p->SetIsRelese();
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
		cout << "FPS : " << TIMEMANAGER->GetFps() << endl;


#ifdef _DEBUG
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
#else
	if (timer >= 1.0f &&
		timer <= 1.1f)
		Exploration();

	if (!GetChildrenFromTag("Probe").size() && startExploration)
		SetSubRoom();

	if (timer >= 1.5f &&
		timer <= 1.6f)
		startDel = true;

	if (timer >= 2.0f &&
		timer <= 2.1f)
		SetTileProperty();

	//if (KEYMANAGER->isOnceKeyDown('5'))
	//	SetWall();

	if (timer >= 2.5f &&
		timer <= 2.6f)
		SetTileImg();

	if (timer >= 3.f &&
		timer <= 3.1f)
	{
		for (Room* r : selRooms)
			r->DeActivePhysics();
	}

#endif

	if (startDel && rooms.size())
		DelRoom();
}
