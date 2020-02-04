#include "stdafx.h"
#include "Maptool.h"

void Maptool::Init()
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

#pragma region SetTilePage2
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
	GRAPHICMANAGER->AddImage("npcNone", L"resource/img/npcNone.png");
#pragma endregion

	GRAPHICMANAGER->AddImage("town_map", L"resource/img/Map/map.png");
	GRAPHICMANAGER->AddImage("loby", L"resource/img/Map/Dungeon_Lobby.png");
	GRAPHICMANAGER->AddImage("Shop_map", L"resource/img/Shop/shop_background.png");
	GRAPHICMANAGER->AddFrameImage("set_tile", L"set_tile3.png", 4, 6);
	GRAPHICMANAGER->AddFrameImage("set_tile_dungeon", L"set_tile_dungeon.png", 4, 6);

	_page = SamplePage::TOWN;
	_eraser = EraserType::Single;

	SetUp();

	//obj = Object::CreateObject<Object>();
	//obj->GetTrans()->SetPos(100, 50);
	//obj->AddComponent<Text>()->CreateText(L"test word hellow", 20, 100, 30, ColorF::Red);

	_rcLoad = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 100, 130, 34);
	_rcSave = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 150, 130, 34);
	_rcEraserType = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 200, 130, 34);
}

void Maptool::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcLoad, _ptMouse))
		{
#pragma region FileLoadTest
			//OPENFILENAME ofn;
			//char filePathSize[1028] = "";
			//ZeroMemory(&ofn, sizeof(OPENFILENAME));
			//
			//ofn.lStructSize = sizeof(OPENFILENAME);
			//ofn.hwndOwner = NULL;
			//ofn.lpstrFile = filePathSize;
			//ofn.nMaxFile = sizeof(filePathSize);
			//ofn.nFilterIndex = true;
			//ofn.lpstrFileTitle = NULL;
			//ofn.nMaxFileTitle = NULL;
			//ofn.lpstrInitialDir = NULL;
			//ofn.lpstrFilter = ("음악파일만넣어줘라");
			//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			//
			//if (GetOpenFileName(&ofn) == FALSE) return;
			//
			//char temp[1028];
			//strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));
			//
			//char* context = NULL;
			//char* token = strtok_s(temp, "\\", &context);
			//
			//while (strlen(context))
			//{
			//	token = strtok_s(NULL, "\\", &context);
			//}
			//
			//char* title = token;
			//token = strtok_s(title, ".", &context);
#pragma endregion

			Load();
		}
		if (PtInRect(&_rcSave, _ptMouse))
		{
#pragma region FileSaveTest
			//OPENFILENAME ofn;
			//char filePathSize[1028] = "";
			////TCHAR filter[] = "Every file(*.*) \0*.*\0TextFile\0*.txt;*.doc\0";
			//char filter[1028] = "Every file(*.*) \0*.*\0TextFile\0*.txt;*.doc\0맵(.map)\0*.map*\0";
			//
			//ZeroMemory(&ofn, sizeof(OPENFILENAME));
			//
			//ofn.lStructSize = sizeof(OPENFILENAME);
			//ofn.hwndOwner = NULL;
			////ofn.lpstrFile = filePathSize;
			//ofn.lpstrFile = filePathSize;
			//ofn.nMaxFile = sizeof(filePathSize);
			//ofn.nFilterIndex = true;
			//ofn.lpstrFileTitle = NULL;
			//ofn.nMaxFileTitle = NULL;
			//ofn.lpstrInitialDir = NULL;
			//ofn.lpstrFilter = filter;
			//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
			//
			////if (GetSaveFileName(&ofn) == FALSE) return;
			//if (GetSaveFileName(&ofn) != FALSE)
			//{
			//	wsprintf(filePathSize, "%s 파일", ofn.lpstrFile);
			//	MessageBox(_hWnd, filePathSize, "저장", MB_OK);
			//}
			//else return;

#pragma endregion

			Save();
		}
		if (PtInRect(&_rcEraserType, _ptMouse))
		{
			_eraser = (EraserType)(((int)_eraser + 1) % (int)EraserType::End);
		}

		ClickSetTile();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		SetMap();
	}

	//// 렉트 충돌부분 색 변하게 해주는 거
	//RECT temp;
	//for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	//{
	//	//if ((_ptMouse.x <= WINSIZEX - 300) && PtInRect(&RectMakeCenter(_tiles[i]->GetTrans()->GetPos().x - CAMERA->GetPosition().x, _tiles[i]->GetTrans()->GetPos().y - CAMERA->GetPosition().y, TILEWIDTH, TILEHEIGHT), _ptMouse))
	//	if ((_ptMouse.x <= WINSIZEX - 300) && IntersectRect(&temp, &RectMakeCenter(_tiles[i]->GetTrans()->GetPos().x - CAMERA->GetPosition().x, _tiles[i]->GetTrans()->GetPos().y - CAMERA->GetPosition().y, TILEWIDTH, TILEHEIGHT), &RectMakeBottomCenter(_ptMouse.x, _ptMouse.y, _currentTile.colSize.x, _currentTile.colSize.y)))
	//	{
	//		//if (_tiles[i]->GetChildren().size() > 0) return;
	//
	//		_tiles[i]->GetComponent<Sprite>()->SetFillRect(true);
	//
	//		continue;
	//	}
	//	else
	//	{
	//		_tiles[i]->GetComponent<Sprite>()->SetFillRect(false);
	//	}
	//}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		RemoveObject();
	}

	if (KEYMANAGER->isOnceKeyUp('1'))
	{
		_page = SamplePage::TOWN;
		SetPage();
	}
	if (KEYMANAGER->isOnceKeyUp('2'))
	{
		_page = SamplePage::DUNGEON;
		SetPage();
	}
}

void Maptool::Render()
{
	GRAPHICMANAGER->DrawImage("Shop_map", Vector2(0, 0), 1.0f, LEFT_TOP, true);
	//GRAPHICMANAGER->DrawImage("loby", Vector2(0, 0), 1.0f, LEFT_TOP, true);

	//char buffer[128];
	wchar_t buffer[128];
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 33; ++j)
		{
			int index = (i + (int)CAMERA->GetPosition().y / TILEHEIGHT) * TILENUMX + (j + (int)CAMERA->GetPosition().x / TILEWIDTH);
	
			if (index < 0 || index >= TILENUMX * TILENUMY) continue;
	
			if (_tiles[index]->GetAttribute() == "Wall") _tiles[index]->GetComponent<Sprite>()->SetFillRect(true);
			else if (_tiles[index]->GetAttribute() == "NpcNone")
			{
				_tiles[index]->GetComponent<Sprite>()->SetRectColor(ColorF::YellowGreen);
				_tiles[index]->GetComponent<Sprite>()->SetFillRect(true);
			}
			//else if (_tiles[index]->GetAttribute() != "Wall") _tiles[index]->GetComponent<Sprite>()->SetFillRect(false);
			else _tiles[index]->GetComponent<Sprite>()->SetFillRect(false);
	
			//sprintf_s(buffer, "%d", index);
			swprintf(buffer, 128, L"%d", index);
			GRAPHICMANAGER->DrawTextD2D(_tiles[index]->GetTrans()->GetPos() + Vector2(-(TILEWIDTH / 2) + 2, TILEHEIGHT / 7), buffer, 10, ColorF::Yellow, TextPivot::LEFT_TOP, L"맑은고딕", true);
		}
	}

	Scene::Render();

	// sample tile image background
	GRAPHICMANAGER->DrawFillRect(Vector2(WINSIZEX - 150, WINSIZEY / 2), Vector2(300, WINSIZEY), 0.0f, ColorF::Aquamarine, 1.0f, CENTER, false);
	
	for (int i = 0; i < SAMPLE_TILE_X_NUM * SAMPLE_TILE_Y_NUM; ++i)
	{
		GRAPHICMANAGER->DrawRect(Vector2(_sampleTile[i].pos.x, _sampleTile[i].pos.y), Vector2(SET_TILEWIDTH, SET_TILEHEIGHT), 0.0f, ColorF::White, PIVOT::CENTER, 1.0f, false);
	}

	switch (_page)
	{
	case SamplePage::TOWN: GRAPHICMANAGER->DrawImage("set_tile", Vector2(WINSIZEX - 150, 30), 1.0f, PIVOT::TOP, false); break;
	case SamplePage::DUNGEON: GRAPHICMANAGER->DrawImage("set_tile_dungeon", Vector2(WINSIZEX - 150, 30), 1.0f, PIVOT::TOP, false); break;
	}

	// is the sample image a frame?
	if (_currentTile.isFrame) GRAPHICMANAGER->DrawFrameImage(_currentTile.imgKey, _ptMouse, 0, 0, 0.85f, _currentTile.pivot, false);
	else GRAPHICMANAGER->DrawImage(_currentTile.imgKey, _ptMouse, 0.85f, _currentTile.pivot, false);

	// draw a square for attributes
	if (_currentTile.pivot == RIGHT_BOTTOM) GRAPHICMANAGER->DrawRect(Vector2(_ptMouse.x, _ptMouse.y) - Vector2(FindTile(_currentTile.imgKey)->startPos.x * TILEWIDTH, FindTile(_currentTile.imgKey)->startPos.y * TILEHEIGHT), Vector2(_currentTile.size.x * TILEWIDTH, _currentTile.size.y * TILEHEIGHT), 0.0f, ColorF::Red, PIVOT::LEFT_TOP, 1.0f, false);
	else if (_currentTile.pivot == BOTTOM) GRAPHICMANAGER->DrawRect(_ptMouse, Vector2(_currentTile.size.x * TILEWIDTH, _currentTile.size.y * TILEHEIGHT), 0.0f, ColorF::Red, _currentTile.pivot, 1.0f, false);
	else GRAPHICMANAGER->DrawRect(_ptMouse, Vector2(_currentTile.size.x * TILEWIDTH, _currentTile.size.y * TILEHEIGHT), 0.0f, ColorF::Red, _currentTile.pivot, 1.0f, false);

	// draw load button
	GRAPHICMANAGER->DrawRect(Vector2(_rcLoad.left, _rcLoad.top), Vector2((_rcLoad.right - _rcLoad.left), (_rcLoad.bottom - _rcLoad.top)), 0.0f, ColorF::Blue, PIVOT::LEFT_TOP, 1.0f, false);
	GRAPHICMANAGER->Text(Vector2(_rcLoad.left, _rcLoad.top), L"Load Buttom", 14, _rcLoad.right - _rcLoad.left, _rcLoad.bottom - _rcLoad.top, ColorF::Black, TextPivot::CENTER);

	// draw save button
	GRAPHICMANAGER->DrawRect(Vector2(_rcSave.left, _rcSave.top), Vector2((_rcSave.right - _rcSave.left), (_rcSave.bottom - _rcSave.top)), 0.0f, ColorF::Red, PIVOT::LEFT_TOP, 1.0f, false);
	GRAPHICMANAGER->Text(Vector2(_rcSave.left, _rcSave.top), L"Save Buttom", 14, _rcSave.right - _rcSave.left, _rcSave.bottom - _rcSave.top, ColorF::Black, TextPivot::CENTER);

	// draw eraser button
	GRAPHICMANAGER->DrawRect(Vector2(_rcEraserType.left, _rcEraserType.top), Vector2((_rcEraserType.right - _rcEraserType.left), (_rcEraserType.bottom - _rcEraserType.top)), 0.0f, ColorF::Green, PIVOT::LEFT_TOP, 1.0f, false);
	if (_eraser == EraserType::Single) GRAPHICMANAGER->DrawTextD2D(Vector2(_rcEraserType.left + 8, _rcEraserType.top - 4), L"eraser type\n : Single", 14);
	else if (_eraser == EraserType::Group) GRAPHICMANAGER->DrawTextD2D(Vector2(_rcEraserType.left + 8, _rcEraserType.top - 4), L"eraser type\n : Group", 14);
	else if (_eraser == EraserType::NoDeleteImage) GRAPHICMANAGER->DrawTextD2D(Vector2(_rcEraserType.left + 8, _rcEraserType.top - 4), L"eraser type\n : NoDeleteImage", 14);
	else if (_eraser == EraserType::OnlyDeleteImage) GRAPHICMANAGER->DrawTextD2D(Vector2(_rcEraserType.left + 8, _rcEraserType.top - 4), L"eraser type\n : OnlyDeleteImage", 14);

#pragma region CoordinatesTest
	
	//char str[128];
	//sprintf_s(buffer, "%d, %d", _ptMouse.x, _ptMouse.y);

	// 카메라 비율 식
	//sprintf_s(str, "%d, %d", (int)CAMERA->GetPosition().x + (int)(_ptMouse.x / CAMERA->GetScale().x), (int)CAMERA->GetPosition().y + (int)(_ptMouse.y / CAMERA->GetScale().y));
	////GRAPHICMANAGER->DrawTextD2D(Vector2(100, 100), buffer, 20, 1.0f, ColorF::Red, DWRITE_TEXT_ALIGNMENT_LEADING, L"맑은고딕", false);
	//GRAPHICMANAGER->DrawTextD2D(Vector2(100, 100), str, 20, ColorF::Red);

	//sprintf_s(buffer, "%f, %f", CAMERA->GetScale().x, CAMERA->GetScale().y);
	//sprintf_s(str, "%f, %f", CAMERA->GetScale().x, CAMERA->GetScale().y);
	//GRAPHICMANAGER->DrawTextD2D(Vector2(100, 70), str, 20, ColorF::Red);

	// ? 가로 칸 수만 나오는 거 같은데 줌 인 줌 아웃 하면 안 맞음
	//sprintf_s(str, "%d", ((int)CAMERA->GetPosition().x + (int)(_ptMouse.x / CAMERA->GetScale().x) / TILEWIDTH)) + TILENUMX * (((int)CAMERA->GetPosition().y + (int)(_ptMouse.y / CAMERA->GetScale().y) / TILEHEIGHT));
	//GRAPHICMANAGER->DrawTextD2D(Vector2(100, 130), str, 20, ColorF::Blue);

	//swprintf(buffer, 128, L"%f, %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);

	// 화면 중앙이 중점인 수식
	//sprintf_s(buffer, "%f, %f", CAMERA->GetPosition().x - (WINSIZEX / CAMERA->GetScale().x / 2) + (_ptMouse.x / CAMERA->GetScale().x), 
	//	CAMERA->GetPosition().y - (WINSIZEY / CAMERA->GetScale().y / 2) + (_ptMouse.y / CAMERA->GetScale().y));
	
	//swprintf(buffer, 128, L"%1.f %1.f", CAMERA->GetPosition().x - (WINSIZEX / CAMERA->GetScale().x / 2) + (_ptMouse.x / CAMERA->GetScale().x),
	//	CAMERA->GetPosition().y - (WINSIZEY / CAMERA->GetScale().y / 2) + (_ptMouse.y / CAMERA->GetScale().y));

	//sprintf_s(str, "%1.f, %1.f", CAMERA->GetPosition().x - (WINSIZEX / CAMERA->GetScale().x / 2) + (_ptMouse.x / CAMERA->GetScale().x) + (WINSIZEX / 2),
	//	CAMERA->GetPosition().y - (WINSIZEY / CAMERA->GetScale().y / 2) + (_ptMouse.y / CAMERA->GetScale().y) + (WINSIZEY / 2));

	//GRAPHICMANAGER->Text(Vector2(100, 200), buffer, 20, 200, 50, ColorF::Blue);
	//GRAPHICMANAGER->DrawTextD2D(Vector2(100, 100), str, 20, 1.0f, ColorF::Red);
#pragma endregion
}

void Maptool::Save()
{
	HANDLE file;
	DWORD write;

	//string str = "shop.map";
	//string str = "Town.map";
	string str = "shop.map";
	//string str = "test.map";

	//GetWindowText(_saveName, titleSave, 256);

	//string str = titleSave;
	//str += ".map";

	file = CreateFile(str.c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tagTiles, sizeof(tagTile) * TILENUMX * TILENUMY, &write, NULL);
	CloseHandle(file);

	MessageBox(_hWnd, "Save Ok!", str.c_str(), MB_OK);
}

void Maptool::Load()
{
	HANDLE file;
	DWORD read;

	//string str = titleLoad;
	//str += ".map";
	string str = "shop.map";
	//string str = "Town.map";
	//string str = "test.map";

	//file = CreateFile(titleLoad, GENERIC_READ, 0, NULL,
	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		//MessageBox(_hWnd, "load 한다", str.c_str(), MB_OK);

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
		}
	}
	else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);

	MessageBox(_hWnd, "File load!", str.c_str(), MB_OK);
}

void Maptool::SetUp()
{
	_ctrSelect = NONE_MOVE;
	_currentTile.imgKey = "empty";

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			int index = j + TILENUMX * i;

			_tiles[index] = Object::CreateObject<Tile>();
			_tiles[index]->Init(j, i);
			_tiles[index]->AddComponent<Sprite>();
			_tiles[index]->SetAttribute("None");

			_tagTiles[index].attribute = "None";
			_tagTiles[index].imgKey = "None";
			_tagTiles[index].isFrame = false;
			_tagTiles[index].pivot = PIVOT::CENTER;
		}
	}
	for (int i = 0; i < SAMPLE_TILE_Y_NUM; ++i)
	{
		for (int j = 0; j < SAMPLE_TILE_X_NUM; ++j)
		{
			//Vector2((i % SAMPLE_TILE_X_NUM) * (100 / SAMPLE_TILE_X_NUM), (i / SAMPLE_TILE_X_NUM) * (100 / SAMPLE_TILE_Y_NUM);
			_sampleTile[i * SAMPLE_TILE_X_NUM + j].pos = { (WINSIZEX - 240) + j * SET_TILEWIDTH, 60 + i * SET_TILEHEIGHT };
			_sampleTile[i * SAMPLE_TILE_X_NUM + j].imgKey.clear();
		}
	}

	TileSetting();
}

void Maptool::SetMap()
{
	if (_ptMouse.x > WINSIZEX - 300) return;
	
	int index = ((_ptMouse.x + (int)CAMERA->GetPosition().x) / TILEWIDTH) + TILENUMX * ((_ptMouse.y + (int)CAMERA->GetPosition().y) / TILEHEIGHT);

	if (_tiles[index]->GetChildren().size() > 0) return;

	SetAttribute(index, _currentTile.startPos, _currentTile.size, _currentTile.startPos2, _currentTile.size2, FindTile(_currentTile.imgKey)->attribute);

	_tiles[index]->AddChild(Object::CreateObject<Object>());

	_tiles[index]->GetChildren()[0]->GetTrans()->SetPos(_tiles[index]->GetTrans()->GetPos() + Vector2(0, TILEHEIGHT / 2));
	if (_currentTile.pivot == RIGHT_BOTTOM) _tiles[index]->GetChildren()[0]->GetTrans()->SetPos(_tiles[index]->GetTrans()->GetPos() + Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));

	_tiles[index]->GetChildren()[0]->GetTrans()->SetScale(GRAPHICMANAGER->FindImage(_currentTile.imgKey)->GetFrameWidth(), GRAPHICMANAGER->FindImage(_currentTile.imgKey)->GetFrameHeight());
	_tiles[index]->GetChildren()[0]->GetTrans()->SetRect();

	_tagTiles[index] = *FindTile(_currentTile.imgKey);

	if (_currentTile.isFrame)
	{
		_tiles[index]->GetChildren()[0]->AddComponent<Sprite>()->Init(true, true);
		_tiles[index]->GetChildren()[0]->GetComponent<Sprite>()->SetImgName(_currentTile.imgKey);
		_tiles[index]->GetChildren()[0]->GetComponent<Sprite>()->SetFPS(0.5f);
	}
	else _tiles[index]->GetChildren()[0]->AddComponent<Sprite>()->SetImgName(_currentTile.imgKey);

	_tiles[index]->GetChildren()[0]->GetComponent<Sprite>()->SetPosition(_tiles[index]->GetChildren()[0]->GetTrans()->GetPos());
	_tiles[index]->GetChildren()[0]->GetComponent<Sprite>()->SetSize(_tiles[index]->GetChildren()[0]->GetTrans()->GetScale());
	_tiles[index]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_currentTile.pivot);
}

void Maptool::ClickSetTile()
{
	if (_ptMouse.x < WINSIZEX - 270 || _ptMouse.x >(WINSIZEX - 270) + (SET_TILEWIDTH * SAMPLE_TILE_X_NUM) ||
		_ptMouse.y < 30 || _ptMouse.y > 30 + (SET_TILEHEIGHT * SAMPLE_TILE_Y_NUM)) return;

	int index = ((_ptMouse.x - (WINSIZEX - 270)) / SET_TILEWIDTH) + SAMPLE_TILE_X_NUM * ((_ptMouse.y - 30) / SET_TILEHEIGHT);

	_currentTile.imgKey = FindTile(_sampleTile[index].imgKey)->imgKey;
	_currentTile.isFrame = FindTile(_sampleTile[index].imgKey)->isFrame;

	//_currentTile.vStartPos = FindTile(_sampleTile[i].imgKey)->vStartPos;
	//_currentTile.vSize = FindTile(_sampleTile[i].imgKey)->vSize;
	_currentTile.startPos = FindTile(_sampleTile[index].imgKey)->startPos;
	_currentTile.size = FindTile(_sampleTile[index].imgKey)->size;
	_currentTile.startPos2 = FindTile(_sampleTile[index].imgKey)->startPos2;
	_currentTile.size2 = FindTile(_sampleTile[index].imgKey)->size2;

	_currentTile.pivot = FindTile(_sampleTile[index].imgKey)->pivot;
}

void Maptool::RemoveObject()
{
	if (_ptMouse.x > WINSIZEX - 300) return;

	int index = ((_ptMouse.x + (int)CAMERA->GetPosition().x) / TILEWIDTH) + TILENUMX * ((_ptMouse.y + (int)CAMERA->GetPosition().y) / TILEHEIGHT);

	if (_eraser == EraserType::Group)
	{
		for (int i = 0; i < TILENUMX * TILENUMY; ++i)
		{
			if (_tiles[i]->GetChildren().size())
			{
				if ((_ptMouse.x <= WINSIZEX - 300) && PtInRect(&RectMakeRightBottom(_tiles[i]->GetChildren()[0]->GetTrans()->GetPos().x - CAMERA->GetPosition().x, _tiles[i]->GetChildren()[0]->GetTrans()->GetPos().y - CAMERA->GetPosition().y, _tiles[i]->GetChildren()[0]->GetTrans()->GetScale().x, _tiles[i]->GetChildren()[0]->GetTrans()->GetScale().y), _ptMouse))
				{
					string s = _tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->GetImgKey();

					SetAttribute(i, FindTile(s)->startPos, FindTile(s)->size, FindTile(s)->startPos2, FindTile(s)->size2, "None");
					_tagTiles[i].imgKey = "empty";

					if (_tiles[i]->GetChildren().size() <= 0) return;
					_tiles[i]->RemoveChild(_tiles[i]->GetChildren()[0]);

					break;
				}
			}
		}
	}
	else if (_eraser == EraserType::Single)
	{
		_tiles[index]->SetAttribute("None");
		_tagTiles[index].attribute = "None";

		if (_tiles[index]->GetChildren().size() <= 0) return;
		_tiles[index]->RemoveChild(_tiles[index]->GetChildren()[0]);
	}
	else if (_eraser == EraserType::NoDeleteImage)
	{
		_tiles[index]->SetAttribute("None");
		_tagTiles[index].attribute = "None";
	}
	else if (_eraser == EraserType::OnlyDeleteImage)
	{
		if (_tiles[index]->GetChildren().size() <= 0) return;
		_tiles[index]->RemoveChild(_tiles[index]->GetChildren()[0]);
	}
}

void Maptool::SetAttribute(int curIdx, Vector2 StartPos, Vector2 size, Vector2 StartPos2, Vector2 size2, string attribute)
{
	int start = ( curIdx- (TILENUMX * (StartPos.y - 1))) - (StartPos.x - 1);

	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			if (start + j + (TILENUMX * i) < 0)continue;

			_tiles[start + j + (TILENUMX * i)]->SetAttribute(attribute);
			_tagTiles[start + j + (TILENUMX * i)].attribute = attribute;
		}
	}

	start = (curIdx - (TILENUMX * (StartPos2.y - 1))) - (StartPos2.x - 1);

	for (int i = 0; i < size2.y; ++i)
	{
		for (int j = 0; j < size2.x; ++j)
		{
			if (start + j + (TILENUMX * i) < 0)continue;

			_tiles[start + j + (TILENUMX * i)]->SetAttribute(attribute);
			_tagTiles[start + j + (TILENUMX * i)].attribute = attribute;
		}
	}
}

tagTile* Maptool::FindTile(string imgKey)
{
	mapTileIter key = _mTileList.find(imgKey);

	if (key != _mTileList.end()) return key->second;
	return nullptr;
}

void Maptool::TileSetting()
{
#pragma region Town
	_mTileList.insert(make_pair(("build_fountain"), tagTile().Clone("build_fountain", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(3, 1), Vector2(3, 1))));
	_mTileList.insert(make_pair(("build_Retaile"), tagTile().Clone("build_Retaile", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(12, 14), Vector2(12, 12), Vector2(10, 2), Vector2(3, 2))));
	//_mTileList.insert(make_pair(("build_Retaile"), tagTile().Clone("build_Retaile", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM)));

	//Vector2 v[] = { Vector2(12, 14), Vector2(10, 2) };
	//Vector2 s[] = {Vector2(12, 12), Vector2(3, 2)};
	//_mTileList.find("build_Retaile")->second->Setting(v, s, 2);

	_mTileList.insert(make_pair(("build_Shop"), tagTile().Clone("build_Shop", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(17, 12), Vector2(17, 12))));
	_mTileList.insert(make_pair(("build_Top1"), tagTile().Clone("build_Top1", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(11, 10), Vector2(11, 10))));
	_mTileList.insert(make_pair(("build_Well"), tagTile().Clone("build_Well", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(4, 3), Vector2(4, 3))));

	_mTileList.insert(make_pair(("door"), tagTile().Clone("door", "Wall", true, 5, 1, PIVOT::RIGHT_BOTTOM, Vector2(5, 1), Vector2(2, 1), Vector2(2, 1), Vector2(2, 1))));
	_mTileList.insert(make_pair(("doordown"), tagTile().Clone("doordown", "Wall", true, 5, 1, PIVOT::RIGHT_BOTTOM, Vector2(5, 3), Vector2(2, 1), Vector2(2, 3), Vector2(2, 1))));
	_mTileList.insert(make_pair(("dgLobbyEntry"), tagTile().Clone("dgLobbyEntry", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(12, 1), Vector2(4, 1), Vector2(4, 1), Vector2(4, 1))));
	_mTileList.insert(make_pair(("dgLobbyLeft"), tagTile().Clone("dgLobbyLeft", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(4, 2), Vector2(4, 2))));
	_mTileList.insert(make_pair(("dgLobbyRight"), tagTile().Clone("dgLobbyRight", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(4, 2), Vector2(4, 2))));

	_mTileList.insert(make_pair(("build_Bottom3"), tagTile().Clone("build_Bottom3", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(17, 16), Vector2(10, 10), Vector2(7, 14), Vector2(3, 7))));
	_mTileList.insert(make_pair(("bench"), tagTile().Clone("bench", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(5, 3), Vector2(5, 3))));
	_mTileList.insert(make_pair(("buildBoard"), tagTile().Clone("buildBoard", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(7, 1), Vector2(7, 1))));
	_mTileList.insert(make_pair(("build_Bottom1"), tagTile().Clone("build_Bottom1", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(11, 10), Vector2(11, 10), Vector2(16, 3), Vector2(1, 1))));
	_mTileList.insert(make_pair(("build_Bottom2"), tagTile().Clone("build_Bottom2", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(11, 10), Vector2(11, 10))));

	_mTileList.insert(make_pair(("VillageLamps1"), tagTile().Clone("VillageLamps1", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("build_Enchant"), tagTile().Clone("build_Enchant", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(20, 6), Vector2(20, 6), Vector2(11, 16), Vector2(8, 10))));
	_mTileList.insert(make_pair(("build_Forge"), tagTile().Clone("build_Forge", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(12, 14), Vector2(10, 14), Vector2(20, 12), Vector2(8, 9))));
	_mTileList.insert(make_pair(("tree"), tagTile().Clone("tree", "Wall", true, 4, 1, PIVOT::RIGHT_BOTTOM, Vector2(5, 1), Vector2(3, 1), Vector2(5, 1), Vector2(3, 1))));
	_mTileList.insert(make_pair(("VillageLamps2"), tagTile().Clone("VillageLamps2", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("dungeonRock"), tagTile().Clone("dungeonRock", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(2, 1), Vector2(2, 1))));

	_mTileList.insert(make_pair(("forgeBoard"), tagTile().Clone("forgeBoard", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(2, 1), Vector2(2, 1))));
	_mTileList.insert(make_pair(("potionBoard"), tagTile().Clone("potionBoard", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(2, 1), Vector2(2, 1))));

	_mTileList.insert(make_pair(("empty"), tagTile().Clone("empty", "Wall", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(1, 1), Vector2(1, 1))));
#pragma endregion

#pragma region Dungeon
	_mTileList.insert(make_pair(("bigRock"), tagTile().Clone("bigRock", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("book"), tagTile().Clone("book", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("brokenPillar"), tagTile().Clone("brokenPillar", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("fountain"), tagTile().Clone("fountain", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("lathe"), tagTile().Clone("lathe", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("pillar"), tagTile().Clone("pillar", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("pot"), tagTile().Clone("pot", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("pot_slime"), tagTile().Clone("pot_slime", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("skull1"), tagTile().Clone("skull1", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("skull2"), tagTile().Clone("skull2", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("skull3"), tagTile().Clone("skull3", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("smallRock"), tagTile().Clone("smallRock", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("smallRock_slime"), tagTile().Clone("smallRock_slime", "Wall", false, 1, 1, PIVOT::BOTTOM, Vector2(1, 1), Vector2(1, 1))));
	_mTileList.insert(make_pair(("npcNone"), tagTile().Clone("npcNone", "NpcNone", false, 1, 1, PIVOT::RIGHT_BOTTOM, Vector2(1, 1), Vector2(1, 1))));
#pragma endregion

	SetPage();
}

void Maptool::SetPage()
{
	switch (_page)
	{
	case SamplePage::TOWN:
	{
		_sampleTile[0].imgKey = _mTileList.find("build_fountain")->second->imgKey;
		_sampleTile[1].imgKey = _mTileList.find("build_Retaile")->second->imgKey;
		_sampleTile[2].imgKey = _mTileList.find("build_Shop")->second->imgKey;
		_sampleTile[3].imgKey = _mTileList.find("build_Top1")->second->imgKey;
		_sampleTile[4].imgKey = _mTileList.find("build_Well")->second->imgKey;
		_sampleTile[5].imgKey = _mTileList.find("door")->second->imgKey;
		_sampleTile[6].imgKey = _mTileList.find("doordown")->second->imgKey;
		_sampleTile[7].imgKey = _mTileList.find("dgLobbyEntry")->second->imgKey;
		_sampleTile[8].imgKey = _mTileList.find("dgLobbyLeft")->second->imgKey;
		_sampleTile[9].imgKey = _mTileList.find("dgLobbyRight")->second->imgKey;
		_sampleTile[10].imgKey = _mTileList.find("build_Bottom3")->second->imgKey;
		_sampleTile[11].imgKey = _mTileList.find("bench")->second->imgKey;
		_sampleTile[12].imgKey = _mTileList.find("buildBoard")->second->imgKey;
		_sampleTile[13].imgKey = _mTileList.find("build_Bottom1")->second->imgKey;
		_sampleTile[14].imgKey = _mTileList.find("build_Bottom2")->second->imgKey;
		_sampleTile[15].imgKey = _mTileList.find("VillageLamps1")->second->imgKey;
		_sampleTile[16].imgKey = _mTileList.find("build_Enchant")->second->imgKey;
		_sampleTile[17].imgKey = _mTileList.find("build_Forge")->second->imgKey;
		_sampleTile[18].imgKey = _mTileList.find("tree")->second->imgKey;
		_sampleTile[19].imgKey = _mTileList.find("VillageLamps2")->second->imgKey;
		_sampleTile[20].imgKey = _mTileList.find("dungeonRock")->second->imgKey;
		_sampleTile[21].imgKey = _mTileList.find("forgeBoard")->second->imgKey;
		_sampleTile[22].imgKey = _mTileList.find("potionBoard")->second->imgKey;
		_sampleTile[23].imgKey = _mTileList.find("empty")->second->imgKey;
	}
	break;
	case SamplePage::DUNGEON:
	{
		_sampleTile[0].imgKey = _mTileList.find("smallRock")->second->imgKey;
		_sampleTile[1].imgKey = _mTileList.find("smallRock_slime")->second->imgKey;
		_sampleTile[2].imgKey = _mTileList.find("bigRock")->second->imgKey;
		_sampleTile[3].imgKey = _mTileList.find("book")->second->imgKey;
		_sampleTile[4].imgKey = _mTileList.find("pot")->second->imgKey;
		_sampleTile[5].imgKey = _mTileList.find("pot_slime")->second->imgKey;
		_sampleTile[6].imgKey = _mTileList.find("lathe")->second->imgKey;
		_sampleTile[7].imgKey = _mTileList.find("fountain")->second->imgKey;
		_sampleTile[8].imgKey = _mTileList.find("pillar")->second->imgKey;
		_sampleTile[9].imgKey = _mTileList.find("skull1")->second->imgKey;
		_sampleTile[10].imgKey = _mTileList.find("skull2")->second->imgKey;
		_sampleTile[11].imgKey = _mTileList.find("skull3")->second->imgKey;
		_sampleTile[12].imgKey = _mTileList.find("brokenPillar")->second->imgKey;
		_sampleTile[13].imgKey = _mTileList.find("npcNone")->second->imgKey;
		_sampleTile[14].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[15].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[16].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[17].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[18].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[19].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[20].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[21].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[22].imgKey = _mTileList.find("empty")->second->imgKey;
		_sampleTile[23].imgKey = _mTileList.find("empty")->second->imgKey;
	}
	break;
	case SamplePage::PAGE_END: break;
	}
}
