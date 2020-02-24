#include "stdafx.h"
#include "UndergroundScene.h"
#include "Player.h"
#include "Tile.h"
#include <filesystem>
#include "Maptool.h"
#include "StartScene.h"
#include "UI.h"
//#include "EnemyNormal.h"
#include "EnemyManager.h"

void UndergroundScene::Init()
{
	Scene::Init();

	//ShowCursor(false);

	_name = "underground";

	_player = Object::CreateObject<Player>();
	_player->Init();
	_player->GetTrans()->SetPos(WINSIZEX / 2 - 500, 325);
	_player->GetPhysicsBody()->SetBodyPosition();

	_enemyMgr = new EnemyManager;
	_enemyMgr->Init();

	AddImage();
	MapLoad();

	_ui = new UI;
	_ui->Init();

	_cursorImg = new Graphic;
	_cursorImg->Init(Direct2D::GetInstance()->CreateBitmap(L"Resource/UI/cursor.png"), "cursor", L"Resource/UI/cursor.png");

	SCENEMANAGER->addScene("maptool", new Maptool);
	SCENEMANAGER->addScene("start", new StartScene);

	_isShowRect = false;

	SCENEMANAGER->GetNowScene()->GetWorld()->SetGravity(b2Vec2(0.0f, 15.0f));
	//SCENEMANAGER->GetNowScene()->GetWorld()->SetGravity(b2Vec2(0.0f, 100.0f));
}

void UndergroundScene::Release()
{
	_vTiles.clear();
	SAFE_OBJECT_RELEASE(_ui);
	SAFE_OBJECT_RELEASE(_enemyMgr);
	SAFE_OBJECT_RELEASE(_cursorImg);

	SAFE_DELETE(_ui);
	SAFE_DELETE(_enemyMgr);
	SAFE_DELETE(_cursorImg);

	Scene::Release();
}

void UndergroundScene::Update()
{
	CAMERA->SetPos(_player->GetTrans()->GetPos() - Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//CAMERA->Control();
	
	Scene::Update();

	_ui->Update();

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
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("start");
		return;
	}

	_enemyMgr->Update();
}

void UndergroundScene::Render()
{
	Scene::Render();

	_ui->Render();

	_cursorImg->Render(MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);

	//char buffer[128];
	//for (auto t : _vTiles)
	//{
	//	sprintf_s(buffer, "%d", t->GetIndex());
	//	GRAPHICMANAGER->Text(t->GetTrans()->GetPos(), buffer, 10, 20, 20, ColorF::Red, TextPivot::LEFT_TOP, L"¸¼Àº°íµñ", true);
	//}

	wchar_t buffer[128];
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 33; ++j)
		{
			int index = (i + (int)CAMERA->GetPosition().y / TILE_HEIGHT) * TILE_NUM_X + (j + (int)CAMERA->GetPosition().x / TILE_WIDTH);

			if (index < 0 || index >= TILE_NUM_X * TILE_NUM_Y) continue;

			//sprintf_s(buffer, "%d", index);
			swprintf(buffer, 128, L"%d", index);
			GRAPHICMANAGER->DrawTextD2D(_vTiles[index]->GetTrans()->GetPos() + Vector2(-(TILE_WIDTH / 2) + 2, TILE_HEIGHT / 7), buffer, 10, ColorF::Yellow, TextPivot::LEFT_TOP, L"¸¼Àº°íµñ", true);
		}
	}
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

	ifstream inFile("test1.map");
	Vector2 pos;
	/*for (Tile* t : _vTiles)
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
		{
			if (t->GetImgName().compare("Wall_RB") == 0)
			{
				t->GetTrans()->SetPos(t->GetTrans()->GetPos() + Vector2(14.5f, 14.5f));
				t->GetTrans()->SetScale(t->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				t->SetPhysics();
				t->GetPhysics()->SetBodyPosition();
				t->GetPhysics()->GetBody()->SetTransform(b2Vec2(t->GetPhysics()->GetBody()->GetPosition().x, t->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
			}
			else if (t->GetImgName().compare("Wall_RT") == 0)
			{
				t->GetTrans()->SetPos(t->GetTrans()->GetPos() + Vector2(14.5f, -14.5f));
				t->GetTrans()->SetScale(t->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				t->SetPhysics();
				t->GetPhysics()->SetBodyPosition();
				t->GetPhysics()->GetBody()->SetTransform(b2Vec2(t->GetPhysics()->GetBody()->GetPosition().x, t->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
			}
			else if (t->GetImgName().compare("Wall_LB") == 0)
			{
				t->GetTrans()->SetPos(t->GetTrans()->GetPos() + Vector2(-14.5f, 14.5f));
				t->GetTrans()->SetScale(t->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				t->SetPhysics();
				t->GetPhysics()->SetBodyPosition();
				t->GetPhysics()->GetBody()->SetTransform(b2Vec2(t->GetPhysics()->GetBody()->GetPosition().x, t->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
			}
			else if (t->GetImgName().compare("Wall_LT") == 0)
			{
				t->GetTrans()->SetPos(t->GetTrans()->GetPos() + Vector2(-14.5f, -14.5f));
				t->GetTrans()->SetScale(t->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				t->SetPhysics();
				t->GetPhysics()->SetBodyPosition();
				t->GetPhysics()->GetBody()->SetTransform(b2Vec2(t->GetPhysics()->GetBody()->GetPosition().x, t->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
			}
			else
			{
				t->SetPhysics();
				t->GetPhysics()->SetBodyPosition();
			}
		}

		if (t->GetTileObject()->GetAttribute() == TAttribute::LADDER)
		{
			t->GetTileObject()->SetPhysics();
			t->GetTileObject()->GetPhysics()->SetBodyPosition();
			t->GetTileObject()->GetPhysics()->SetSensor(true);
		}

		if (t->GetTileObject()->GetAttribute() == TAttribute::INTERACTION)
		{
			if (t->GetTileParent() == -1)
			{
				t->GetTileObject()->GetTrans()->SetScale(TILE_WIDTH, TILE_HEIGHT * 2);
				t->GetTileObject()->SetPhysics();
				t->GetTileObject()->GetPhysics()->SetBodyPosition();
				t->GetTileObject()->GetPhysics()->SetSensor(true);
			}
		}
	}*/
	for (int i = 0; i < _vTiles.size(); ++i)
	{
		char buffer[256];
		inFile.getline(buffer, 256);
		_vTiles[i]->SetAttribute((TAttribute)atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->SetImgName(buffer);
		_vTiles[i]->GetSprite()->SetImgName(_vTiles[i]->GetImgName());

		inFile.getline(buffer, 256);
		pos.x = atof(buffer);
		inFile.getline(buffer, 256);
		pos.y = atof(buffer);
		_vTiles[i]->GetSprite()->SetPosition(pos);

		inFile.getline(buffer, 256);
		_vTiles[i]->GetSprite()->SetDepth(atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->SetIndex(atoi(buffer));

		// tile object setting
		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->SetAttribute((TAttribute)atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->SetImgName(buffer);
		_vTiles[i]->GetTileObject()->GetSprite()->SetImgName(_vTiles[i]->GetTileObject()->GetImgName());

		inFile.getline(buffer, 256);
		pos.x = atof(buffer);

		inFile.getline(buffer, 256);
		pos.y = atof(buffer);

		_vTiles[i]->GetTileObject()->GetSprite()->SetPosition(pos);

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->GetSprite()->SetFrameX(atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->GetSprite()->SetFrameY(atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->GetSprite()->SetDepth(atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->SetIsActive(atoi(buffer));

		ColorF color = ColorF::Blue;
		inFile.getline(buffer, 256);
		color.r = atof(buffer);
		inFile.getline(buffer, 256);
		color.g = atof(buffer);
		inFile.getline(buffer, 256);
		color.b = atof(buffer);
		inFile.getline(buffer, 256);
		color.a = atof(buffer);

		_vTiles[i]->GetTileObject()->GetSprite()->SetRectColor(color);

		inFile.getline(buffer, 256);
		_vTiles[i]->GetTileObject()->GetSprite()->SetFillRect(atoi(buffer));

		inFile.getline(buffer, 256);
		_vTiles[i]->SetTileParent(atoi(buffer));

		inFile.getline(buffer, 256);
		int size = atoi(buffer);

		for (int j = 0; j < size; ++j)
		{
			inFile.getline(buffer, 256);
			_vTiles[i]->AddTileChildren(_vTiles[atoi(buffer)]);
		}

		if (_vTiles[i]->GetAttribute() == TAttribute::WALL)
		{
			b2Filter b;
			b.categoryBits = CATEGORY_SCENERY;
			b.maskBits = MASK_SCENERY;

			if (_vTiles[i]->GetImgName().compare("Wall_RB") == 0)
			{
				_vTiles[i]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(14.5f, 14.5f));
				_vTiles[i]->GetTrans()->SetScale(_vTiles[i]->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				_vTiles[i]->SetPhysics();
				_vTiles[i]->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetPhysics()->GetBody()->SetTransform(b2Vec2(_vTiles[i]->GetPhysics()->GetBody()->GetPosition().x, _vTiles[i]->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
				_vTiles[i]->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(b);
			}
			else if (_vTiles[i]->GetImgName().compare("Wall_RT") == 0)
			{
				_vTiles[i]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(14.5f, -14.5f));
				_vTiles[i]->GetTrans()->SetScale(_vTiles[i]->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				_vTiles[i]->SetPhysics();
				_vTiles[i]->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetPhysics()->GetBody()->SetTransform(b2Vec2(_vTiles[i]->GetPhysics()->GetBody()->GetPosition().x, _vTiles[i]->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
				_vTiles[i]->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(b);
			}
			else if (_vTiles[i]->GetImgName().compare("Wall_LB") == 0)
			{
				_vTiles[i]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(-14.5f, 14.5f));
				_vTiles[i]->GetTrans()->SetScale(_vTiles[i]->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				_vTiles[i]->SetPhysics();
				_vTiles[i]->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetPhysics()->GetBody()->SetTransform(b2Vec2(_vTiles[i]->GetPhysics()->GetBody()->GetPosition().x, _vTiles[i]->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
				_vTiles[i]->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(b);
			}
			else if (_vTiles[i]->GetImgName().compare("Wall_LT") == 0)
			{
				_vTiles[i]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(-14.5f, -14.5f));
				_vTiles[i]->GetTrans()->SetScale(_vTiles[i]->GetTrans()->GetScale() + Vector2(10.0f, 10.0f));
				_vTiles[i]->SetPhysics();
				_vTiles[i]->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetPhysics()->GetBody()->SetTransform(b2Vec2(_vTiles[i]->GetPhysics()->GetBody()->GetPosition().x, _vTiles[i]->GetPhysics()->GetBody()->GetPosition().y), PI / 4);
				_vTiles[i]->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(b);
			}
			else
			{
				_vTiles[i]->SetPhysics();
				_vTiles[i]->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetPhysics()->GetBody()->GetFixtureList()->SetFilterData(b);
			}
		}

		if (_vTiles[i]->GetTileObject()->GetAttribute() == TAttribute::LADDER)
		{
			cout << i << endl;
			if (_vTiles[i]->GetTileParent() == -1)
			{
				int children = _vTiles[i]->GetTileChildren().size();
				Vector2 size = Vector2(TILE_WIDTH, (children + 1) * TILE_HEIGHT);
				Vector2 pos = _vTiles[i]->GetTrans()->GetPos() + Vector2(0.0f, (size.y / 2) - (TILE_HEIGHT / 2));
				_vTiles[i]->GetTileObject()->GetTrans()->SetScale(size);
				_vTiles[i]->GetTileObject()->GetTrans()->SetPos(pos);

				_vTiles[i]->GetTileObject()->SetPhysics();
				_vTiles[i]->GetTileObject()->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetTileObject()->GetPhysics()->SetSensor(true);
			}
		}

		if (_vTiles[i]->GetTileObject()->GetAttribute() == TAttribute::INTERACTION ||
			_vTiles[i]->GetTileObject()->GetAttribute() == TAttribute::DEAD_BODY)
		{
			if (_vTiles[i]->GetTileParent() == -1)
			{
				Vector2 size;
				Vector2 pos;
				if (_vTiles[i]->GetTileChildren().size() >= 1)
				{
					size.x = abs(_vTiles[i]->GetTrans()->GetPos().x - _vTiles[_vTiles[i]->GetTileChildren()[0]]->GetTrans()->GetPos().x);
					size.y = abs(_vTiles[i]->GetTrans()->GetPos().y - _vTiles[_vTiles[i]->GetTileChildren()[0]]->GetTrans()->GetPos().y);

					if (size.x <= 0.0f)
					{
						size = Vector2(TILE_WIDTH, TILE_HEIGHT * 2);
						pos = _vTiles[i]->GetTrans()->GetPos() + Vector2(0.0f, -(TILE_HEIGHT / 2));
					}
					else if (size.x > 0.0f)
					{
						size = Vector2(TILE_WIDTH * 2, TILE_HEIGHT);
						pos = _vTiles[i]->GetTrans()->GetPos() + Vector2(TILE_WIDTH / 2, 0.0f);
					}

					_vTiles[i]->GetTileObject()->GetTrans()->SetScale(size);
					_vTiles[i]->GetTileObject()->GetTrans()->SetPos(pos);
				}

				_vTiles[i]->GetTileObject()->SetPhysics();
				_vTiles[i]->GetTileObject()->GetPhysics()->SetBodyPosition();
				_vTiles[i]->GetTileObject()->GetPhysics()->SetSensor(true);
			}
		}

		if (_vTiles[i]->GetTileObject()->GetAttribute() == TAttribute::ENEMY)
		{
			if (_vTiles[i]->GetTileParent() == -1)
			{
				_enemyMgr->SetEnemy(_vTiles[i]->GetTrans()->GetPos());
				_vTiles[i]->GetTileObject()->SetImgName("None");
				_vTiles[i]->GetTileObject()->GetSprite()->SetImgName("None");
			}
			_vTiles[i]->GetTileObject()->GetSprite()->SetRectColor(ColorF::Blue);
			_vTiles[i]->GetTileObject()->GetSprite()->SetFillRect(false);
			_vTiles[i]->GetTileObject()->SetIsActive(false);
		}
	}
	inFile.close();

	//for (int i = 0; i < _vTiles.size(); )
	//{
	//	if (_vTiles[i]->GetImgName().compare("None") == 0)
	//	{
	//		_vTiles.erase(_vTiles.begin() + i);
	//		//_vTiles[i]->SetIsActive(false);
	//	}
	//	else i++;
	//}

	for (Tile* t : _vTiles)
	{
		if (t->GetImgName().compare("None") == 0)
		{
			t->SetIsActive(false);
		}
	}
}

void UndergroundScene::AddImage()
{
	DirectorySearch("Resource/Terrain/None/");
	DirectorySearch("Resource/Terrain/Wall/");
	DirectorySearch("Resource/Object/None/");
	DirectorySearch("Resource/Object/Door/");
	DirectorySearch("Resource/Object/Interaction/");
	DirectorySearch("Resource/Object/Dead_Body/");
	DirectorySearch("Resource/NPC/");
	DirectorySearch("Resource/Enemy/Maptool/");
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