#include "stdafx.h"
#include "Dungeon.h"

void Dungeon::Init(Vector2 start)
{
	Object::Init();
	_name = "Dungeon";
	SetParent(SCENEMANAGER->GetNowScene());

	GRAPHICMANAGER->AddImage("smallRock", L"resource/img/Object/smallRock.png");
	GRAPHICMANAGER->AddImage("smallRock_slime", L"resource/img/Object/smallRock_slime.png");
	GRAPHICMANAGER->AddImage("bigRock", L"resource/img/Object/bigRock.png");
	GRAPHICMANAGER->AddImage("book", L"resource/img/Object/book.png");
	GRAPHICMANAGER->AddImage("pot", L"resource/img/Object/pot.png");
	GRAPHICMANAGER->AddImage("pot_slime", L"resource/img/Object/pot_slime.png");
	GRAPHICMANAGER->AddImage("lathe", L"resource/img/Object/lathe.png");
	GRAPHICMANAGER->AddImage("fountain", L"resource/img/Object/fountain.png");
	GRAPHICMANAGER->AddImage("pillar", L"resource/img/Object/pillar.png");
	GRAPHICMANAGER->AddImage("skull1", L"resource/img/Object/skull1.png");
	GRAPHICMANAGER->AddImage("skull2", L"resource/img/Object/skull2.png");
	GRAPHICMANAGER->AddImage("skull3", L"resource/img/Object/skull3.png");
	GRAPHICMANAGER->AddImage("brokenPillar", L"resource/img/Object/brokenPillar.png");
	GRAPHICMANAGER->AddImage("Dungeon", L"resource/img/Dungeon/background.png");
	GRAPHICMANAGER->AddImage("empty", L"resource/img/empty.png");
	//_player = Object::CreateObject<Player>();
	//_player->Init(this);

	pos = start;
	_trans->SetPos(pos);


	_eMgr = new EnemyManeger;
}

void Dungeon::Update()
{


	if (!_roomActive)return;

	Object::Update();

	_eMgr->Update();
}

void Dungeon::Render()
{
	if (!_roomActive)return;

	GRAPHICMANAGER->FindImage("Dungeon")->Render(pos.x, pos.y, PIVOT::LEFT_TOP);
	Object::Render();

	_eMgr->Render();
}


void Dungeon::SetUp()
{
	for (int i = 0; i < Dungeon_Y; ++i)
	{
		for (int j = 0; j < Dungeon_X; ++j)
		{
			int index = j + Dungeon_X * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->GetTrans()->SetPos(pos.x + j * TILEWIDTH + (TILEWIDTH / 2),
				pos.y + i * TILEHEIGHT + (TILEHEIGHT / 2));
			tile->AddComponent<Sprite>();
			tile->SetAttribute("None");

			tiles.push_back(tile);

			//tiles[index] = Object::CreateObject<Tile>(this);
			//tiles[index]->Init(j , i );
			//tiles[index]->GetTrans()->SetPos(pos.x + j * TILEWIDTH + (TILEWIDTH / 2),
			//	pos.y + i * TILEHEIGHT + (TILEHEIGHT / 2));
			//tiles[index]->AddComponent<Sprite>();
			//tiles[index]->SetAttribute("None");

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
	
	string a = "Dungeon";

	char buffer[128];
	sprintf_s(buffer, "%d.map", RND->getFromIntTo(1, 8));
	string b = buffer;

	string str = a + b;

	//file = CreateFile(titleLoad, GENERIC_READ, 0, NULL,
	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		//MessageBox(_hWnd, "load วัดู", str.c_str(), MB_OK);

		ReadFile(file, _tagTiles, sizeof(tagTile) * Dungeon_X * Dungeon_Y, &read, NULL);
		CloseHandle(file);

		for (int i = 0; i < Dungeon_X * Dungeon_Y; i++)
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

void Dungeon::SetRoom()
{
	_roomActive = true;
	SetUp();
	_eMgr->Init(this);
}

void Dungeon::CloseRoom()
{
	_roomActive = false;
	_eMgr->Release();
	for (Tile* c : tiles)
	{
		if(c->GetAttribute()=="Wall")
			SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(c->GetComponent<PhysicsBody>()->GetBody());
		c->Release();
	}
	tiles.clear();
}

vector<Tile*> Dungeon::GetTiles()
{
	vector<Tile*> t;

	for (int i = 0; i < Dungeon_X * Dungeon_Y; i++)
		t.push_back(tiles[i]);

	return t;
}
