#include "stdafx.h"
#include "UndergroundScene.h"
#include "Player.h"
#include "Tile.h"
#include <filesystem>

void UndergroundScene::Init()
{
	Scene::Init();

	_player = Object::CreateObject<Player>();
	_player->Init();

	AddImage();
	MapLoad();

	_isShowRect = false;
	
	SCENEMANAGER->GetNowScene()->GetWorld()->SetGravity(b2Vec2(0.0f, 3.0f));
}

void UndergroundScene::Release()
{
	Object::Release();
}

void UndergroundScene::Update()
{
	//CAMERA->SetPos(_player->GetTrans()->GetPos() - Vector2(WINSIZEX / 2, WINSIZEY / 2));
	CAMERA->Control();

	Scene::Update();

	// tile draw rect
	if (KEYMANAGER->isOnceKeyUp(VK_F1))
	{
		_isShowRect = !_isShowRect;

		for (auto t : _vTiles)
		{
			t->GetSprite()->SetShowRect(_isShowRect);
			t->GetTileObject()->GetSprite()->SetShowRect(_isShowRect);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SCENEMANAGER->changeScene("maptool");
		return;
	}
}

void UndergroundScene::Render()
{
	Scene::Render();
}

void UndergroundScene::MapLoad()
{
	for (int i = 0; i < TILE_NUM_Y; ++i)
	{
		for (int j = 0; j < TILE_NUM_X; ++j)
		{
			Tile* tile = Object::CreateObject<Tile>();
			tile->Init();
			tile->GetTrans()->SetPos(j * TILE_WIDTH + (TILE_WIDTH / 2),
				i * TILE_HEIGHT + (TILE_HEIGHT / 2));
			tile->SetIdX(j);
			tile->SetIdY(i);
			tile->SetIndex(j + TILE_NUM_X * i);
			tile->GetSprite()->SetDepth(0);
			tile->SetAttribute(TAttribute::NONE);
			tile->SetTileObject(Object::CreateObject<Tile>());
			tile->GetTileObject()->Init();
			tile->GetTileObject()->GetTrans()->SetPos(tile->GetTrans()->GetPos());
			tile->GetTileObject()->GetSprite()->SetImgName("None");
			tile->GetTileObject()->SetIsActive(false);

			_vTiles.push_back(tile);
		}
	}

	ifstream inFile("test.map");
	Vector2 pos;
	for (Tile* t : _vTiles)
	{
		char buffer[256];
		inFile.getline(buffer, 256);
		t->SetAttribute((TAttribute)atoi(buffer));

		inFile.getline(buffer, 256);
		t->SetImgName(buffer);
		t->GetSprite()->SetImgName(t->GetImgName());

		inFile.getline(buffer, 256);
		pos.x = atof(buffer);
		inFile.getline(buffer, 256);
		pos.y = atof(buffer);
		t->GetSprite()->SetPosition(pos);

		inFile.getline(buffer, 256);
		t->GetSprite()->SetDepth(atoi(buffer));

		// tile object setting
		inFile.getline(buffer, 256);
		t->GetTileObject()->SetAttribute((TAttribute)atoi(buffer));

		inFile.getline(buffer, 256);
		t->GetTileObject()->SetImgName(buffer);
		t->GetTileObject()->GetSprite()->SetImgName(t->GetTileObject()->GetImgName());

		inFile.getline(buffer, 256);
		pos.x = atof(buffer);

		inFile.getline(buffer, 256);
		pos.y = atof(buffer);

		t->GetTileObject()->GetSprite()->SetPosition(pos);

		inFile.getline(buffer, 256);
		t->GetTileObject()->GetSprite()->SetFrameX(atoi(buffer));

		inFile.getline(buffer, 256);
		t->GetTileObject()->GetSprite()->SetFrameY(atoi(buffer));

		inFile.getline(buffer, 256);
		t->GetTileObject()->GetSprite()->SetDepth(atoi(buffer));

		inFile.getline(buffer, 256);
		t->GetTileObject()->SetIsActive(atoi(buffer));

		ColorF color = ColorF::Blue;
		inFile.getline(buffer, 256);
		color.r = atof(buffer);
		inFile.getline(buffer, 256);
		color.g = atof(buffer);
		inFile.getline(buffer, 256);
		color.b = atof(buffer);
		inFile.getline(buffer, 256);
		color.a = atof(buffer);

		t->GetTileObject()->GetSprite()->SetRectColor(color);

		inFile.getline(buffer, 256);
		t->GetTileObject()->GetSprite()->SetFillRect(atoi(buffer));

		inFile.getline(buffer, 256);
		t->SetTileParent(atoi(buffer));

		inFile.getline(buffer, 256);
		int size = atoi(buffer);

		for (int i = 0; i < size; ++i)
		{
			inFile.getline(buffer, 256);
			t->AddTileChildren(_vTiles[atoi(buffer)]);
		}

		if (t->GetAttribute() == TAttribute::WALL)
		//if (t->GetImgName().compare("Wall") == 0)
		{
			t->SetPhysics();
			t->GetPhysics()->SetBodyPosition();
		}
	}
	inFile.close();
}

void UndergroundScene::AddImage()
{
	DirectorySearch("Resource/Terrain/None/");
	DirectorySearch("Resource/Terrain/Wall/");
	DirectorySearch("Resource/Object/None/");
	DirectorySearch("Resource/Object/Door/");
	DirectorySearch("Resource/Object/Interaction/");
	DirectorySearch("Resource/Object/Dead_Body/");
	DirectorySearch("Resource/Object/Ladder/", 1, 3);
}

void UndergroundScene::DirectorySearch(string folderPath, int maxFrameX, int maxFrameY)
{
	string imgKey;
	wstring path;

	for (auto d : filesystem::directory_iterator(folderPath))
	{
		string a = d.path().string();
		path.assign(a.begin(), a.end());

		imgKey = d.path().string().substr(strlen(folderPath.c_str()), d.path().string().size() - (strlen(folderPath.c_str()) + 4));
		GRAPHICMANAGER->AddImage(imgKey, path, maxFrameX, maxFrameY);
	}
}