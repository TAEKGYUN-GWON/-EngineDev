#include "stdafx.h"
#include "BossRoom.h"
#include "Ability.h"



void BossRoom::Init()
{
	Scene::Init();
	
	_name = "BossRoom";
	GRAPHICMANAGER->AddImage("BossRoom_bg", L"resource/img/Dungeon/bossRoom.png");

	GRAPHICMANAGER->AddFrameImage("Open_Boss", L"resource/img/Enemy/BossUp.png", 32, 1);
	GRAPHICMANAGER->AddFrameImage("deadBoss1", L"resource/img/Enemy/dead1.png", 41, 1);
	GRAPHICMANAGER->AddFrameImage("deadBoss2", L"resource/img/Enemy/dead2.png", 41, 1);
	//GRAPHICMANAGER->AddFrameImage("lll", L"resource/img/Enemy/lll.png", 10, 5);
	GRAPHICMANAGER->AddFrameImage("FistShoot", L"resource/img/Enemy/FistShoot.png", 41, 3);
	GRAPHICMANAGER->AddFrameImage("Hand_Shoot_First", L"resource/img/Enemy/Hand_Shoot_First.png", 20, 1);
	GRAPHICMANAGER->AddFrameImage("Hand_Shoot_Last", L"resource/img/Enemy/Hand_Shoot_Last.png", 11, 1);
	GRAPHICMANAGER->AddFrameImage("idleBoss", L"resource/img/Enemy/idleBoss.png", 2, 1);
	GRAPHICMANAGER->AddFrameImage("Hand", L"resource/img/Enemy/hand.png", 19, 1);
	

	GRAPHICMANAGER->AddImage("Boss_Rock0", L"resource/img/Enemy/Boss_Rock0.png");
	GRAPHICMANAGER->AddImage("Boss_Rock1", L"resource/img/Enemy/Boss_Rock1.png");
	GRAPHICMANAGER->AddImage("Boss_Rock2", L"resource/img/Enemy/Boss_Rock2.png");
	GRAPHICMANAGER->AddImage("Boss_Rock3", L"resource/img/Enemy/Boss_Rock3.png");
	GRAPHICMANAGER->AddFrameImage("Shadow", L"resource/img/Enemy/Shadow.png",1,1);
	GRAPHICMANAGER->FindImage("Open_Boss");

	_player = Object::CreateObject<Player>();
	_player->Init();
	//_player->GetTrans()->SetPos(Vector2(35, 37) + Vector2((TILEWIDTH * Bossroom_X) / 2, (TILEHEIGHT * Bossroom_Y) - 150));
	//_player->GetTrans()->SetPos(Vector2 (((TILEWIDTH * 35) + (TILEWIDTH / 2)), ((TILEHEIGHT * 37) + (TILEHEIGHT / 2))));
	_player->GetTrans()->SetPos(Vector2 (((TILEWIDTH * 35) ), ((TILEHEIGHT * 37) )));
	_player->GetComponent<PhysicsBody>()->SetBodyPosition();
	//CAMERA->SetPos(Vector2(1170, 1440)); //player 쫓아가게 가능? 쫓아가야 하나? 보스 보여줘야 하는데?

	//_boss->GetComponent<PhysicsBody>()->SetBodyPosition();
	
	SetUP();
	_boss = Object::CreateObject<Boss>();
	_boss->Init(Vector2(((TILEWIDTH * 35)), ((TILEHEIGHT * 15))),_tiles);

	UI = new UiManager;
	UI->Init();
}

void BossRoom::Update()
{
	Scene::Update();
	CAMERA->SetPosition(_player->GetTrans()->GetPos(), "BossRoom_bg");
	UI->Update();
}

void BossRoom::Render()
{
	GRAPHICMANAGER->DrawImage("BossRoom_bg", 0, 0, LEFT_TOP);
	wchar_t buffer[128];
	//swprintf(buffer, 128, L"x : %d \n y : %d ", (55 + _ptMouse.x) / TILEWIDTH, _ptMouse.y);
	//swprintf(buffer, 128, L"x : %f \n y : %f ", _ptMouse.x + CAMERA->GetPosition().x, _ptMouse.y + CAMERA->GetPosition().y);
	swprintf(buffer, 128, L"x : %d \n y : %d ", (int)(_ptMouse.x + CAMERA->GetPosition().x) / TILEWIDTH
		, (int)(_ptMouse.y + CAMERA->GetPosition().y) / TILEHEIGHT);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2 - 200, 0), buffer, 20, 300, 50, ColorF::Azure);

	Scene::Render();
	UI->Render();
}

void BossRoom::SetUP()
{
	for (int i = 0; i < Bossroom_Y; ++i)
	{
		for (int j = 0; j < Bossroom_X; ++j)
		{
			int index = j + Bossroom_X * i;

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
	string str = "bossroom.map";

	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		ReadFile(file, _tagTiles, sizeof(tagTile) * Bossroom_X * Bossroom_Y, &read, NULL);
		CloseHandle(file);

		for (int i = 0; i < Bossroom_X * Bossroom_Y; i++)
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
		}
	}
	else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);

}
