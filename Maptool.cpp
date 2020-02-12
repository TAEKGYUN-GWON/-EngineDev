#include "stdafx.h"
#include "Maptool.h"
#include "Tile.h"
#include <filesystem>
#include "PaletteBtn.h"
#include "Player.h"

using namespace filesystem;

//void setWindowsSize(int x, int y, int width, int height);

void Maptool::Init()
{
	Scene::Init();
	
	//setWindowsSize(WINSTARTX, WINSTARTY, 720, 500);

	GRAPHICMANAGER->AddImage("blank", L"Resource/Blank.png");

	string imgKey;
	wstring path;

	for (auto d : directory_iterator("Resource/Object/None/"))
	{
		string a = d.path().string();
		path.assign(a.begin(), a.end());

		imgKey = d.path().string().substr(strlen("Resource/Object/None/"), d.path().string().size() - (strlen("Resource/Object/None/") + 4));
		GRAPHICMANAGER->AddImage(imgKey, path);

		PaletteBtn* palette = Object::CreateObject<PaletteBtn>();
		palette->SetName(imgKey);
		palette->Init();
		palette->SetAttribute(TAttribute::NONE);
		palette->SetCameraAffect(false);
		palette->GetSprite()->SetDepth(5);
		palette->SetImageSize(POINT{ GRAPHICMANAGER->FindImage(imgKey)->GetFrameWidth() , GRAPHICMANAGER->FindImage(imgKey)->GetFrameHeight() });

		_vSetObj.push_back(palette);
	}
	for (auto d : directory_iterator("Resource/Object/Interaction/"))
	{
		string a = d.path().string();
		path.assign(a.begin(), a.end());

		imgKey = d.path().string().substr(strlen("Resource/Object/Interaction/"), d.path().string().size() - (strlen("Resource/Object/Interaction/") + 4));
		GRAPHICMANAGER->AddImage(imgKey, path);

		PaletteBtn* palette = Object::CreateObject<PaletteBtn>();
		palette->SetName(imgKey);
		palette->Init();
		palette->SetAttribute(TAttribute::INTERACTION);
		palette->SetCameraAffect(false);
		palette->GetSprite()->SetDepth(5);
		palette->SetImageSize(POINT{ GRAPHICMANAGER->FindImage(imgKey)->GetFrameWidth() , GRAPHICMANAGER->FindImage(imgKey)->GetFrameHeight() });

		_vSetObj.push_back(palette);
	}
	for (auto d : directory_iterator("Resource/Terrain/Wall/"))
	{
		string a = d.path().string();
		path.assign(a.begin(), a.end());

		imgKey = d.path().string().substr(strlen("Resource/Terrain/Wall/"), d.path().string().size() - (strlen("Resource/Terrain/Wall/") + 4));
		GRAPHICMANAGER->AddImage(imgKey, path);

		PaletteBtn* palette = Object::CreateObject<PaletteBtn>();
		palette->SetName(imgKey);
		palette->Init();
		palette->SetAttribute(TAttribute::WALL);
		palette->SetCameraAffect(false);
		palette->GetSprite()->SetDepth(5);
		palette->SetImageSize(POINT{ GRAPHICMANAGER->FindImage(imgKey)->GetFrameWidth() , GRAPHICMANAGER->FindImage(imgKey)->GetFrameHeight() });

		_vSetTer_1.push_back(palette);
	}
	for (auto d : directory_iterator("Resource/Terrain/None/"))
	{
		string a = d.path().string();
		path.assign(a.begin(), a.end());

		imgKey = d.path().string().substr(strlen("Resource/Terrain/None/"), d.path().string().size() - (strlen("Resource/Terrain/None/") + 4));
		GRAPHICMANAGER->AddImage(imgKey, path);

		PaletteBtn* palette = Object::CreateObject<PaletteBtn>();
		palette->SetName(imgKey);
		palette->Init();
		palette->SetAttribute(TAttribute::NONE);
		palette->SetCameraAffect(false);
		palette->GetSprite()->SetDepth(5);
		palette->SetImageSize(POINT{ GRAPHICMANAGER->FindImage(imgKey)->GetFrameWidth() , GRAPHICMANAGER->FindImage(imgKey)->GetFrameHeight() });

		if (palette->GetName().compare("Ladder") == 0)
		{
			palette->GetSprite()->SetScale(Vector2(1.0f, 0.7f));
			palette->SetAttribute(TAttribute::LADDER);
		}

		_vSetTer_1.push_back(palette);
	}

	_page = SamplePage::Terrain_1;
	_eraser = EraserType::Single;

	SetUp();

	_rcLoad = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 100, 130, 34);
	_rcSave = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 150, 130, 34);
	_rcEraserType = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 200, 130, 34);

	_player = Object::CreateObject<Player>();
	_player->Init();
}

void Maptool::Update()
{
	CAMERA->Control();

	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcLoad,_ptMouse.Vector2ToPOINT()))
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
		if (PtInRect(&_rcSave, _ptMouse.Vector2ToPOINT()))
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
		if (PtInRect(&_rcEraserType, _ptMouse.Vector2ToPOINT()))
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
		_page = SamplePage::Terrain_1;
		SetPage();
	}
	if (KEYMANAGER->isOnceKeyUp('2'))
	{
		_page = SamplePage::Terrain_2;
		SetPage();
	}
	if (KEYMANAGER->isOnceKeyUp('3'))
	{
		_page = SamplePage::Object;
		SetPage();
	}

	// tile draw rect
	if (KEYMANAGER->isOnceKeyUp(VK_F1))
	{
		for (auto t : _vTiles)
		{
			t->GetSprite()->SetShowRect(!t->GetSprite()->GetShowRect());
		}
	}

	int index = ((int)MOUSEPOINTER->GetMouseWorldPosition().x / TILE_WIDTH) + TILE_NUM_X * ((int)MOUSEPOINTER->GetMouseWorldPosition().y / TILE_HEIGHT);
	if (index >= 0 and index <= TILE_NUM_X * TILE_NUM_Y)
	{
		if (_currentTile->GetImageSize().y <= TILE_HEIGHT)
			_currentTile->GetComponent<Sprite>()->SetPosition(_vTiles[index]->GetTrans()->GetPos());
		else if (_currentTile->GetImageSize().y <= TILE_HEIGHT * 2)
			_currentTile->GetComponent<Sprite>()->SetPosition(_vTiles[index]->GetTrans()->GetPos() - Vector2(0, TILE_HEIGHT / 2));
		else _currentTile->GetTrans()->SetPos(_vTiles[index]->GetTrans()->GetPos());
	}
}

void Maptool::Render()
{
	//wchar_t buffer[128];
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 33; ++j)
		{
			int index = (i + (int)CAMERA->GetPosition().y / TILE_HEIGHT) * TILE_NUM_X + (j + (int)CAMERA->GetPosition().x / TILE_WIDTH);
	
			if (index < 0 || index >= TILE_NUM_X * TILE_NUM_Y) continue;
	
			if (_vTiles[index]->GetAttribute() == TAttribute::WALL) _vTiles[index]->GetComponent<Sprite>()->SetFillRect(true);
			else if (_vTiles[index]->GetAttribute() == TAttribute::INTERACTION)
			{
				_vTiles[index]->GetComponent<Sprite>()->SetRectColor(ColorF::YellowGreen);
				_vTiles[index]->GetComponent<Sprite>()->SetFillRect(true);
			}
			else
			{
				_vTiles[index]->GetComponent<Sprite>()->SetFillRect(false);
				_vTiles[index]->GetComponent<Sprite>()->SetRectColor(ColorF::Blue);
			}
	
			//swprintf(buffer, 128, L"%d", index);
			//GRAPHICMANAGER->DrawTextD2D(_vTiles[index]->GetTrans()->GetPos() + Vector2(-(TILE_WIDTH / 2) + 2, TILE_HEIGHT / 7), buffer, 10, ColorF::Yellow, TextPivot::LEFT_TOP, L"맑은고딕", true);
		}
	}

	Scene::Render();

	for (int i = 0; i < _vSetObj.size(); ++i)
	{
		GRAPHICMANAGER->DrawRect(Vector2(_vSetObj[i]->GetTrans()->GetPos().x, _vSetObj[i]->GetTrans()->GetPos().y), Vector2(SET_TILE_WIDTH, SET_TILE_HEIGHT), 0.0f, ColorF::White, PIVOT::CENTER, 1.0f, true);
	}

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

	//WriteFile(file, _tagTile, sizeof(tagTile) * TILENUMX * TILENUMY, &write, NULL);
	WriteFile(file, &_vTagTiles, sizeof(tagTile) * TILE_NUM_X * TILE_NUM_Y, &write, NULL);
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

	//if (file != INVALID_HANDLE_VALUE)
	//{
	//	//MessageBox(_hWnd, "load 한다", str.c_str(), MB_OK);
	//
	//	//ReadFile(file, _tagTiles, sizeof(tagTile) * TILENUMX * TILENUMY, &read, NULL);
	//	ReadFile(file, &_vTagTiles, sizeof(tagTile) * TILE_NUM_X * TILE_NUM_Y, &read, NULL);
	//	CloseHandle(file);
	//
	//	for (int i = 0; i < TILE_NUM_X * TILE_NUM_Y; i++)
	//	{
	//		// _tiles[] initialization
	//		_vTiles[i]->SetImgName("None");
	//		_vTiles[i]->SetAttribute("None");
	//		_vTiles[i]->SetIsFrame(false);
	//		_vTiles[i]->SetPivot(PIVOT::CENTER);
	//
	//		if (_vTiles[i]->GetChildren().size() > 0) _vTiles[i]->RemoveChild(_vTiles[i]->GetChildren()[0]);
	//
	//
	//		// value setting
	//		_vTiles[i]->SetAttribute(_vTagTiles[i].attribute);
	//		_vTiles[i]->SetImgName(_vTagTiles[i].imgKey);
	//		_vTiles[i]->SetIsFrame(_vTagTiles[i].isFrame);
	//		_vTiles[i]->SetPivot(_vTagTiles[i].pivot);
	//
	//
	//		if (_vTiles[i]->GetImgName() != "None")
	//		{
	//			_vTiles[i]->AddChild(Object::CreateObject<Object>());
	//
	//			_vTiles[i]->GetChildren()[0]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(0, TILEHEIGHT / 2));
	//			if (_vTiles[i]->GetPivot() == RIGHT_BOTTOM) _vTiles[i]->GetChildren()[0]->GetTrans()->SetPos(_vTiles[i]->GetTrans()->GetPos() + Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));
	//
	//			//_tiles[i]->GetChildren()[0]->GetTrans()->SetScale(GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameWidth(), GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameHeight());
	//			_vTiles[i]->GetChildren()[0]->GetTrans()->SetRect();
	//
	//			if (_vTiles[i]->GetIsFrame())
	//			{
	//				_vTiles[i]->GetChildren()[0]->AddComponent<Sprite>()->Init(true, true);
	//				_vTiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetImgName(_vTiles[i]->GetImgName());
	//				_vTiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetFPS(0.5f);
	//				_vTiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_vTiles[i]->GetPivot());
	//			}
	//			else
	//			{
	//				_vTiles[i]->GetChildren()[0]->AddComponent<Sprite>()->SetImgName(_vTiles[i]->GetImgName());
	//				_vTiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_vTiles[i]->GetPivot());
	//			}
	//			_vTiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPosition(_vTiles[i]->GetChildren()[0]->GetTrans()->GetPos());
	//			//_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetScale(_tiles[i]->GetChildren()[0]->GetTrans()->GetScale());
	//		}
	//	}
	//}
	//else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);

	MessageBox(_hWnd, "File load!", str.c_str(), MB_OK);
}

void Maptool::SetUp()
{
	Object* paletteBg = Object::CreateObject<Object>();
	paletteBg->Init();
	Sprite* ps = paletteBg->AddComponent<Sprite>();
	ps->Init();
	ps->SetFillRect(true);
	ps->SetRectColor(ColorF::Aquamarine);
	paletteBg->GetTrans()->SetPos(Vector2(WINSIZEX - 150, WINSIZEY / 2));
	paletteBg->GetTrans()->SetScale(Vector2(300, WINSIZEY));
	paletteBg->SetCameraAffect(false);
	ps->SetDepth(4);
	ps->SetShowRect(true);


	_ctrSelect = (int)TAttribute::NONE;
	_currentTile = Object::CreateObject<PaletteBtn>();
	_currentTile->SetTag("CurrentTile");
	_currentTile->SetName("blank");
	_currentTile->Init();
	_currentTile->GetSprite()->SetAlpha(0.7f);
	_currentTile->GetSprite()->SetDepth(6);
	
	for (int i = 0; i < TILE_NUM_Y; ++i)
	{
		for (int j = 0; j < TILE_NUM_X; ++j)
		{
			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->GetSprite()->SetDepth(0);
			tile->SetAttribute(TAttribute::NONE);
			_vTiles.push_back(tile);

			//tile->Init(j, i);
			//tile->GetSprite()->SetDepth(1);
			//tile->SetAttribute(TAttribute::NONE);
			//_vObjects.push_back(tile);
	
			tagTile tag;
			tag.attribute = TAttribute::NONE;
			tag.imgKey = "None";
			tag.isFrame = false;
			tag.pivot = PIVOT::CENTER;
			_vTagTiles.push_back(tag);
		}
	}

	for (int i = 0; i < _vSetTer_1.size(); ++i)
	{
		_vSetTer_1[i]->GetTrans()->SetPos(Vector2((i % SET_TILE_NUM_X) * SET_TILE_WIDTH + WINSIZEX - 245, 
			(i / SET_TILE_NUM_X) * SET_TILE_HEIGHT + 60));
		_vSetTer_1[i]->GetSprite()->SetPosition(_vSetTer_1[i]->GetTrans()->GetPos());
		_vSetTer_1[i]->SetIsActive(true);
	}
	for (int i = 0; i < _vSetTer_2.size(); ++i)
	{
		_vSetTer_2[i]->GetTrans()->SetPos(Vector2((i % SET_TILE_NUM_X) * SET_TILE_WIDTH + WINSIZEX - 245,
			(i / SET_TILE_NUM_X) * SET_TILE_HEIGHT + 60));
		_vSetTer_2[i]->GetSprite()->SetPosition(_vSetTer_2[i]->GetTrans()->GetPos());
		_vSetTer_2[i]->SetIsActive(false);
	}
	for (int i = 0; i < _vSetObj.size(); ++i)
	{
		_vSetObj[i]->GetTrans()->SetPos(Vector2((i % SET_TILE_NUM_X) * SET_TILE_WIDTH + WINSIZEX - 245,
			(i / SET_TILE_NUM_X) * SET_TILE_HEIGHT + 60));
		_vSetObj[i]->GetSprite()->SetPosition(_vSetObj[i]->GetTrans()->GetPos());
		_vSetObj[i]->SetIsActive(false);
	}
}

void Maptool::SetMap()
{
	if (_ptMouse.x > WINSIZEX - 300) return;
	
	int index = ((int)MOUSEPOINTER->GetMouseWorldPosition().x / TILE_WIDTH) + TILE_NUM_X * ((int)MOUSEPOINTER->GetMouseWorldPosition().y  / TILE_HEIGHT);
	if (index < 0 or index > TILE_NUM_X * TILE_NUM_Y) return;
	
	SetAttribute(index, *_currentTile);
}

void Maptool::ClickSetTile()
{
	if ((int)_ptMouse.x < WINSIZEX - 278 || (int)_ptMouse.x > (WINSIZEX - 278) + (SET_TILE_WIDTH * SET_TILE_NUM_X) ||
		(int)_ptMouse.y < 30 || (int)_ptMouse.y > 30 + (SET_TILE_HEIGHT * SET_TILE_NUM_Y)) return;
	
	int index = (((int)_ptMouse.x - (WINSIZEX - 278)) / SET_TILE_WIDTH) + SET_TILE_NUM_X * (((int)_ptMouse.y - 30) / SET_TILE_HEIGHT);
	
	if (index >= _vSetTer_1.size()) return;

	_currentTile->SetName(_vSetTer_1[index]->GetName());
	_currentTile->GetSprite()->SetImgName(_currentTile->GetName());
	_currentTile->SetAttribute(_vSetTer_1[index]->GetAttribute());
	_currentTile->SetImageSize(_vSetTer_1[index]->GetImageSize());
}

void Maptool::RemoveObject()
{
	//if (_ptMouse.x > WINSIZEX - 300) return;
	//
	//int index = ((int)MOUSEPOINTER->GetMouseWorldPosition().x / TILEWIDTH) + TILENUMX * ((int)MOUSEPOINTER->GetMouseWorldPosition().y / TILEHEIGHT);
	//
	//if (_eraser == EraserType::Group)
	//{
	//	for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	//	{
	//		if (_tiles[i]->GetChildren().size())
	//		{
	//			if ((_ptMouse.x <= WINSIZEX - 300) && PtInRect(&RectMakeRightBottom(
	//				_tiles[i]->GetChildren()[0]->GetTrans()->GetPos().x, 
	//				_tiles[i]->GetChildren()[0]->GetTrans()->GetPos().y, 
	//				_tiles[i]->GetChildren()[0]->GetTrans()->GetScale().x, 
	//				_tiles[i]->GetChildren()[0]->GetTrans()->GetScale().y), 
	//				MOUSEPOINTER->GetMouseWorldPosition().Vector2ToPOINT()))
	//			{
	//				string s = _tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->GetImgKey();
	//
	//				SetAttribute(i, FindTile(s)->startPos, FindTile(s)->size, FindTile(s)->startPos2, FindTile(s)->size2, "None");
	//				_tagTiles[i].imgKey = "empty";
	//
	//				if (_tiles[i]->GetChildren().size() <= 0) return;
	//				_tiles[i]->RemoveChild(_tiles[i]->GetChildren()[0]);
	//
	//				break;
	//			}
	//		}
	//	}
	//}
	//else if (_eraser == EraserType::Single)
	//{
	//	_tiles[index]->SetAttribute("None");
	//	_tagTiles[index].attribute = "None";
	//
	//	if (_tiles[index]->GetChildren().size() <= 0) return;
	//	_tiles[index]->RemoveChild(_tiles[index]->GetChildren()[0]);
	//}
	//else if (_eraser == EraserType::NoDeleteImage)
	//{
	//	_tiles[index]->SetAttribute("None");
	//	_tagTiles[index].attribute = "None";
	//}
	//else if (_eraser == EraserType::OnlyDeleteImage)
	//{
	//	if (_tiles[index]->GetChildren().size() <= 0) return;
	//	_tiles[index]->RemoveChild(_tiles[index]->GetChildren()[0]);
	//}
}

void Maptool::SetAttribute(int curIdx, PaletteBtn& palett)
{
	if (palett.GetImageSize().y <= TILE_HEIGHT)
	{
		_vTiles[curIdx]->SetAttribute(palett.GetAttribute());
		_vTiles[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
		//_vObjects[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
	}
	else if (palett.GetImageSize().y <= TILE_HEIGHT * 2)
	{
		_vTiles[curIdx - TILE_NUM_X]->SetAttribute(palett.GetAttribute());
		_vTiles[curIdx]->SetAttribute(palett.GetAttribute());

		_vTiles[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
		_vTiles[curIdx]->GetSprite()->SetPosition(_vTiles[curIdx]->GetTrans()->GetPos() - Vector2(0, TILE_HEIGHT / 2));
		//_vObjects[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
		//_vObjects[curIdx]->GetSprite()->SetPosition(_vObjects[curIdx]->GetTrans()->GetPos() - Vector2(0, TILE_HEIGHT / 2));
	}
	else if (palett.GetImageSize().y <= TILE_HEIGHT * 3)
	{
		_vTiles[curIdx - TILE_NUM_X]->SetAttribute(palett.GetAttribute());
		_vTiles[curIdx]->SetAttribute(palett.GetAttribute());
		_vTiles[curIdx + TILE_NUM_X]->SetAttribute(palett.GetAttribute());

		_vTiles[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
		//_vObjects[curIdx]->GetSprite()->SetImgName(_currentTile->GetName());
	}
}

void Maptool::SetPage()
{
	switch (_page)
	{
	case SamplePage::Terrain_1:
	{
		for (int i = 0; i < _vSetTer_2.size(); ++i)
			_vSetTer_2[i]->SetIsActive(false);
		for (int i = 0; i < _vSetObj.size(); ++i)
			_vSetObj[i]->SetIsActive(false);

		for (int i = 0; i < _vSetTer_1.size(); ++i)
			_vSetTer_1[i]->SetIsActive(true);
	}
	break;
	case SamplePage::Terrain_2:
	{
		for (int i = 0; i < _vSetTer_1.size(); ++i) 
			_vSetTer_1[i]->SetIsActive(false);
		for (int i = 0; i < _vSetObj.size(); ++i)
			_vSetObj[i]->SetIsActive(false);

		for (int i = 0; i < _vSetTer_2.size(); ++i)
			_vSetTer_2[i]->SetIsActive(true);
	}
	break;
	case SamplePage::Object:
	{
		for (int i = 0; i < _vSetTer_1.size(); ++i)
			_vSetTer_1[i]->SetIsActive(false);
		for (int i = 0; i < _vSetTer_2.size(); ++i)
			_vSetTer_2[i]->SetIsActive(false);

		for (int i = 0; i < _vSetObj.size(); ++i)
			_vSetObj[i]->SetIsActive(true);
	}
	break;
	case SamplePage::PAGE_END: break;
	}
}
