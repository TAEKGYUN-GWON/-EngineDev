#include "stdafx.h"
#include "EntranceScene.h"

void EntranceScene::Init()
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

	GRAPHICMANAGER->AddImage("fatkachu", L"resource/img/Object/popcorn.png");
	GRAPHICMANAGER->AddImage("loby", L"resource/img/Map/Dungeon_Lobby.png");

	SetUp();

	_player = Object::CreateObject<Player>();
	_player->Init();
	_player->GetTrans()->SetPos(1249, 2020);
	_player->SetTiles(tiles, TILENUMX, TILENUMY);
}

void EntranceScene::Update()
{
	Scene::Update();

	CAMERA->SetPosition(_player->GetTrans()->GetPos(),"loby");
}


void EntranceScene::Render()
{
	GRAPHICMANAGER->DrawImage("loby", Vector2(0, 0), 1.0f, LEFT_TOP, true);

	//Scene::Render();
	_player->Render();

	GRAPHICMANAGER->Text(Vector2(10, 6), L"Entrance Scene", 20, 200, 30, ColorF::Aqua);
}

void EntranceScene::SetUp()
{
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			int index = j + TILENUMX * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->AddComponent<Sprite>();
			tile->SetAttribute("None");

			tiles.push_back(tile);

			_tagTiles[index].attribute = "None";
			_tagTiles[index].imgKey = "None";
			_tagTiles[index].isFrame = false;
			_tagTiles[index].pivot = PIVOT::CENTER;
		}
	}

	HANDLE file;
	DWORD read;

	string str = "loby.map";

	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		ReadFile(file, _tagTiles, sizeof(tagTile) * TILENUMX * TILENUMY, &read, NULL);
		CloseHandle(file);

		for (int i = 0; i < TILENUMX * TILENUMY; i++)
		{
			// tiles[] initialization
			tiles[i]->SetImgName("None");
			tiles[i]->SetAttribute("None");
			tiles[i]->SetIsFrame(false);
			tiles[i]->SetPivot(PIVOT::CENTER);

			if (tiles[i]->GetChildren().size() > 0) tiles[i]->RemoveChild(tiles[i]->GetChildren()[0]);

			// value setting
			tiles[i]->SetAttribute(_tagTiles[i].attribute);
			tiles[i]->SetImgName(_tagTiles[i].imgKey);
			tiles[i]->SetIsFrame(_tagTiles[i].isFrame);
			tiles[i]->SetPivot(_tagTiles[i].pivot);

			if (tiles[i]->GetImgName() != "None")
			{
				tiles[i]->AddChild(Object::CreateObject<Object>());

				tiles[i]->GetChildren()[0]->GetTrans()->SetPos(tiles[i]->GetTrans()->GetPos() + Vector2(0, TILEHEIGHT / 2));
				if (tiles[i]->GetPivot() == RIGHT_BOTTOM) tiles[i]->GetChildren()[0]->GetTrans()->SetPos(tiles[i]->GetTrans()->GetPos() + Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));

				tiles[i]->GetChildren()[0]->GetTrans()->SetScale(GRAPHICMANAGER->FindImage(tiles[i]->GetImgName())->GetFrameWidth(), GRAPHICMANAGER->FindImage(tiles[i]->GetImgName())->GetFrameHeight());
				tiles[i]->GetChildren()[0]->GetTrans()->SetRect();

				if (tiles[i]->GetIsFrame())
				{
					tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->Init(true, true);
					tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetImgName(tiles[i]->GetImgName());
					tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetFPS(0.5f);
					tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(tiles[i]->GetPivot());
				}
				else
				{
					tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->SetImgName(tiles[i]->GetImgName());
					tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(tiles[i]->GetPivot());
				}

				tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPosition(tiles[i]->GetChildren()[0]->GetTrans()->GetPos());

			}
			if (tiles[i]->GetAttribute() == "Wall")
			{
				auto p = tiles[i]->AddComponent<PhysicsBody>();
				p->Init(BodyType::STATIC, 1, 1);
				p->SetBodyPosition();
			}
		}
	}
	else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);
}