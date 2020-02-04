#include "stdafx.h"
#include "TownScene.h"
#include"Inventory.h"
#include "NpcShopState.h"

void TownScene::Init()
{
	Scene::Init();

#pragma region SetTilePage1
	GRAPHICMANAGER->AddImage("build_fountain", L"resource/img/Object/build_fountain.png");
	GRAPHICMANAGER->AddImage("build_Retaile", L"resource/img/Object/build_Retaile.png");
	GRAPHICMANAGER->AddImage("build_Shop", L"resource/img/Object/build_Shop.png");
	GRAPHICMANAGER->AddImage("build_Top1", L"resource/img/Object/build_Top1.png");
	GRAPHICMANAGER->AddImage("build_Well", L"resource/img/Object/build_Well.png");

	GRAPHICMANAGER->AddFrameImage("door", L"resource/img/Object/door.png", 5, 1);
	GRAPHICMANAGER->AddFrameImage("doordown", L"resource/img/Object/doordown.png", 5, 1);

	GRAPHICMANAGER->AddImage("dgLobbyEntry", L"resource/img/Object/dgLobbyEntry.png");
	GRAPHICMANAGER->AddImage("dgLobbyLeft", L"resource/img/Object/dgLobbyLeft.png");
	GRAPHICMANAGER->AddImage("dgLobbyRight", L"resource/img/Object/dgLobbyRight.png");
	GRAPHICMANAGER->AddImage("build_Bottom3", L"resource/img/Object/build_Bottom3.png");
	GRAPHICMANAGER->AddImage("bench", L"resource/img/Object/bench.png");
	GRAPHICMANAGER->AddImage("buildBoard", L"resource/img/Object/buildBoard.png");
	GRAPHICMANAGER->AddImage("build_Bottom1", L"resource/img/Object/build_Bottom1.png");
	GRAPHICMANAGER->AddImage("build_Bottom2", L"resource/img/Object/build_Bottom2.png");
	GRAPHICMANAGER->AddImage("VillageLamps1", L"resource/img/Object/VillageLamps1.png");
	GRAPHICMANAGER->AddImage("build_Enchant", L"resource/img/Object/build_Enchant.png");
	GRAPHICMANAGER->AddImage("VillageLamps2", L"resource/img/Object/VillageLamps2.png");

	GRAPHICMANAGER->AddFrameImage("tree", L"resource/img/Object/tree.png", 4, 1);

	GRAPHICMANAGER->AddImage("build_Forge", L"resource/img/Object/build_Forge.png");
	GRAPHICMANAGER->AddImage("dungeonRock", L"resource/img/Object/dungeonRock.png");
	GRAPHICMANAGER->AddImage("forgeBoard", L"resource/img/Object/forgeBoard.png");
	GRAPHICMANAGER->AddImage("potionBoard", L"resource/img/Object/potionBoard.png");
	GRAPHICMANAGER->AddImage("empty", L"resource/img/empty.png");
#pragma endregion

	GRAPHICMANAGER->AddFrameImage("Girl1", L"resource/img/Smithy/Girl.png", 9, 4);
	GRAPHICMANAGER->AddFrameImage("Guy1", L"resource/img/Smithy/Guy.png", 9, 4);
	GRAPHICMANAGER->AddFrameImage("Kid1", L"resource/img/Smithy/Kids.png", 6, 4);
	GRAPHICMANAGER->AddFrameImage("Lunk1", L"resource/img/Smithy/Lunk.png", 9, 4);

	GRAPHICMANAGER->AddImage("town_map", L"resource/img/Map/map.png");

	GRAPHICMANAGER->AddFrameImage("set_tile", L"set_tile3.png", 4, 6);
	GRAPHICMANAGER->AddFrameImage("set_tile_dungeon", L"set_tile_dungeon.png", 4, 6);

	_smith = GRAPHICMANAGER->AddFrameImage("Smith", L"resource/img/Smithy/Smith_Dott.png", 4, 1);

	_j = GRAPHICMANAGER->AddImage("j", L"resource/img/Smithy/J.png");



	_frameCount = _frameX = 0;


	_player = Object::CreateObject<Player>();
	_player->Init();

	_player->GetTrans()->SetPos(Vector2(2000, 1500));

	_player->GetPhysics()->SetBodyPosition();

	_player->GetSprite()->SetPosition(_player->GetTrans()->GetPos() + Vector2(0,-14));

	

	_smithy = new Smithy;
	_smithy->Init(_player->GetInventory());


	CreateNPC();
	SetDest();

	SetUp();


	_aStar = new Astar;
	_aStar->Init(this->_tiles, TILENUMX, TILENUMY);


	//_smithy->SetSmithPos(_smith->GetTrans()->GetPos());

}

void TownScene::Update()
{
	Scene::Update();

	_smithy->Update();

	_frameCount++;
	if (_frameCount >= 5)
	{
		_frameX++;
		//_frameCount = 0;

		if (_frameX >= 4)
			_frameX = 0;
	}

	if((_player->GetTrans()->GetPos().x > 1955 - 100 && _player->GetTrans()->GetPos().y == 525
		&& _player->GetTrans()->GetPos().x < 1955 + 100))//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       && _player->GetTrans()->GetPos().y <= 525 ))
	{
		cout << "h" << endl;
		//smithy->SetShow(false);
	}
	 

	CAMERA->SetPosition(Vector2(_player->GetTrans()->GetPos()), 
		"town_map");

	MoveNPC();
}

void TownScene::SetUp()
{
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			/*int index = j + TILENUMX * i;

			_tiles[index] = Object::CreateObject<Tile>();
			_tiles[index]->Init(j, i);
			_tiles[index]->AddComponent<Sprite>();
			_tiles[index]->SetAttribute("None");

			

			_tagTiles[index].attribute = "None";
			_tagTiles[index].imgKey = "None";
			_tagTiles[index].isFrame = false;
			_tagTiles[index].pivot = PIVOT::CENTER;*/

			int index = j + SHOPTILEMAXX * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->AddComponent<Sprite>();
			tile->SetAttribute("None");
			_tiles.push_back(tile);

			_tagTiles[index].attribute = "None";
			_tagTiles[index].imgKey = "None";
			_tagTiles[index].isFrame = false;
			_tagTiles[index].pivot = PIVOT::CENTER;
		}
	}


	HANDLE file;
	DWORD read;

	//string str = titleLoad;
	//str += ".map";
	string str = "Town.map";

	//file = CreateFile(titleLoad, GENERIC_READ, 0, NULL,
	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		//MessageBox(_hWnd, "load วัดู", str.c_str(), MB_OK);

		ReadFile(file, _tagTiles, sizeof(tagTile) * TILENUMX * TILENUMY, &read, NULL);
		CloseHandle(file);

		for (int i = 0; i < TILENUMX * TILENUMY; i++)
		{
			// _tiles[] initialization
			_tiles[i]->SetImgName("None");
			_tiles[i]->SetAttribute("None");
			_tiles[i]->SetIsFrame(false);
			_tiles[i]->SetPivot(PIVOT::CENTER);

			if (_tiles[i]->GetChildren().size() > 0) _tiles[i]->RemoveChild(_tiles[i]->GetChildren()[0]);


			// value setting
			_tiles[i]->SetAttribute(_tagTiles[i].attribute);
			_tiles[i]->SetImgName(_tagTiles[i].imgKey);
			_tiles[i]->SetIsFrame(_tagTiles[i].isFrame);
			_tiles[i]->SetPivot(_tagTiles[i].pivot);


			if (_tiles[i]->GetImgName() != "None")
			{
				_tiles[i]->AddChild(Object::CreateObject<Object>());

				_tiles[i]->GetChildren()[0]->GetTrans()->SetPos(_tiles[i]->GetTrans()->GetPos() + Vector2(0, TILEHEIGHT / 2));
				if (_tiles[i]->GetPivot() == RIGHT_BOTTOM) _tiles[i]->GetChildren()[0]->GetTrans()->SetPos(_tiles[i]->GetTrans()->GetPos() + Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));

				_tiles[i]->GetChildren()[0]->GetTrans()->SetScale(GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameWidth(), GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameHeight());
				_tiles[i]->GetChildren()[0]->GetTrans()->SetRect();

				if (_tiles[i]->GetIsFrame())
				{
					_tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->Init(true, true);
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetImgName(_tiles[i]->GetImgName());
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetFPS(0.5f);
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_tiles[i]->GetPivot());
				}
				else
				{
					_tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->SetImgName(_tiles[i]->GetImgName());
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_tiles[i]->GetPivot());
				}
				_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPosition(_tiles[i]->GetChildren()[0]->GetTrans()->GetPos());
				_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetSize(_tiles[i]->GetChildren()[0]->GetTrans()->GetScale());
			}
			if (_tiles[i]->GetAttribute() == "Wall")
			{
				auto p = _tiles[i]->AddComponent<PhysicsBody>();
				p->Init(BodyType::STATIC, 1, 1);
				p->SetBodyPosition();
			}
		}
	}
	else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);
}

void TownScene::Render()
{
	GRAPHICMANAGER->DrawImage("town_map", Vector2(0, 0), 1.0f, LEFT_TOP, true);


	Scene::Render();

	_player->GetInventory()->Render();

	_smithy->Render();

	if (!_smithy->GetSmithy())
	{
		_smith->FrameRender(Vector2(2470, 1080), _frameX, 1, PIVOT::CENTER);

		if (ShowJ())
		{
			_j->Render(Vector2(2520, 1040), 1.f, PIVOT::CENTER, true);
		}
	}

	if (_smithy->GetSmithy())
	{
		if (!(_player->GetTrans()->GetPos().x > 2470 - 200 && _player->GetTrans()->GetPos().y >= 1080
			&& _player->GetTrans()->GetPos().x < 2470 + 200 && _player->GetTrans()->GetPos().y <= 1080 + 200))
		{
			_smithy->SetShow(false);
		}
	}

	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->Render();
	}

	wchar_t buffer[128];
	swprintf(buffer, 128, L"x: %1.f, y:%1.f", _player->GetTrans()->GetPos().x, _player->GetTrans()->GetPos().y);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, WINSIZEY / 2), buffer, 20, 500, 300, ColorF::White);

}

bool TownScene::ShowJ()
{
	if (_player->GetTrans()->GetPos().x > 2470 - 200 && _player->GetTrans()->GetPos().y >= 1080
		&& _player->GetTrans()->GetPos().x < 2470 + 200 && _player->GetTrans()->GetPos().y <= 1080 + 250)
	{
		_smithy->SetIn(true);
		_player->SetIsInteraction(true);
		return true;
	}
	else
	{
		_smithy->SetIn(false);
		_player->SetIsInteraction(false);
		return false;
	}
}

void TownScene::CreateNPC()
{
	Npc* npc = Object::CreateObject<Npc>();
	npc->SetIsCheckSOn(false);
	npc->SetIsAstarOn(true);

	for (int i = 0; i < 10; i++)
	{
		int a = RND->getInt(4);

		if (a == 0)
		{
			npc->Init("Girl1", Vector2(632, 980));
			npc->SetName("girl");
			_vNpc.push_back(npc);
		}
		if (a == 1)
		{
			npc->Init("Guy1", Vector2(632, 980));
			npc->SetName("guy");
			_vNpc.push_back(npc);
		}
		if (a == 2)
		{
			npc->Init("Kid1", Vector2(632, 980));
			npc->SetName("kid");
			_vNpc.push_back(npc);
		}
		if (a == 3)
		{
			npc->Init("Lunk1", Vector2(632, 980));
			npc->SetName("lunk");
			_vNpc.push_back(npc);
		}
	}
}

void TownScene::FoundWay(Npc* npc, int i)
{
	if (npc->GetIsAstarOn())
	{
		npc->SetPath(_aStar->pathFinder(npc->GetTrans()->GetPos(), ReturnDest(i)));

		npc->SetIsAstarOn(false);
	}
}

void TownScene::SetDest()
{
	_destination.push_back(Vector2(2196, 1609));
	_destination.push_back(Vector2(1912, 2080));
	_destination.push_back(Vector2(384, 2186));
	_destination.push_back(Vector2(632, 980));
	_destination.push_back(Vector2(752, 206));
	_destination.push_back(Vector2(1664, 1261));
	_destination.push_back(Vector2(2553, 769));

	for (int i = 0; i < 10; i++)
	{
		_destCount.push_back(-1);
	}
}

Vector2 TownScene::ReturnDest(int i)
{
	_destCount[i] = RND->getInt(8);

	return _destination[_destCount[i]];
}

void TownScene::MoveNPC()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		//if(_vNpc[i]->GetNpcState() == NpcIdle)
		//FoundWay(_vNpc[i], i);
	}
}
