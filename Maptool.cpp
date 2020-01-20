#include "stdafx.h"
#include "Maptool.h"

void Maptool::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	//GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 32, 20);
	GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 4, 2);

	//obj = Object::CreateObject<Object>();
	//obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	//Sprite* a = obj->AddComponent<Sprite>();
	//a->SetImgName("eagle");
	////a->SetFlipX(true);
	//obj->GetTrans()->SetScale(Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight()));

	SetUp();

	_isDown = false;

	_curFrameX = _curFrameY = 0;
}

void Maptool::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//_isDown = true;
		//_prevMouse = _ptMouse;

		
		//if (PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		//{
		//	//_STGround->SetIsActive(true);
		//}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//_isDown = false;

		//if (PtInRect(&_btn1->GetTrans()->GetRect(), _ptMouse))
		//{
		//	_btn1->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		//}
		//if (PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		//{
		//	_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Green);
		//}
	}

	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	//{
	//	//if (PtInRect(&_btn1->GetTrans()->GetRect(), _ptMouse))
	//	//{
	//	//	_btn1->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
	//	//}
	//	if (_STGround->GetIsActive() && PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
	//	{
	//		_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
	//		
	//		_STGround->GetTrans()->SetPos(
	//		Vector2(_STGround->GetTrans()->GetPos().x + (_ptMouse.x - _prevMouse.x),
	//				_STGround->GetTrans()->GetPos().y + (_ptMouse.y - _prevMouse.y)));
	//	}
	//}
	//if (_isDown) _prevMouse = _ptMouse;


	//_STGround->GetTrans()->SetPos(Vector2((CAMERA->GetPosition().x + WINSIZEX) - (_STGround->GetTrans()->GetScale().x / 2), _STGround->GetTrans()->GetScale().y / 2 + 2));

	if (KEYMANAGER->isOnceKeyUp('1')) _curFrameX = (_curFrameX + 1) % 3;
	if (KEYMANAGER->isOnceKeyUp('2')) _curFrameY = (_curFrameY + 1) % 2;
}

void Maptool::Render()
{
	Scene::Render();

	char buffer[128];

	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 43; ++j)
		{
			int cullX = CAMERA->GetPosition().x / TILEWIDTH;
			int cullY = CAMERA->GetPosition().y / TILEHEIGHT;

			_index = (i + cullY) * TILENUMX + (j + cullX);

			if (_index < 0 || _index >= TILENUMX * TILENUMY) continue;

			//_tiles[_index]->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
			_tiles[_index]->SetAllowsRender(true);

			sprintf_s(buffer, "%d", _index);
			GRAPHICMANAGER->DrawTextD2D(_tiles[_index]->GetTrans()->GetPos(), buffer, 10, 1.0f, ColorF::Yellow);
		}
	}

	GRAPHICMANAGER->DrawFillRect(Vector2(WINSIZEX - 150, WINSIZEY / 2), Vector2(300, WINSIZEY), 0.0f, ColorF::Aquamarine, 1.0f, CENTER, false);

	GRAPHICMANAGER->DrawFrameImage("test", Vector2(WINSIZEX - 150, WINSIZEY / 4), _curFrameX, _curFrameY, CENTER, false);

	//GRAPHICMANAGER->DrawTextD2D(Vector2(200, 100), L"Here!!", 20, 1.0f, ColorF::White);
}

void Maptool::SetUp()
{
	// TODO : button role?
	//_btn1 = Object::CreateObject<Object>();
	//_btn1->GetTrans()->SetPos(Vector2(WINSIZEX / 2, 200));
	//_btn1->GetTrans()->SetScale(Vector2(100.0f, 50.0f));
	//_btn1->AddComponent<Sprite>();

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_index = j + TILENUMX * i;

			_tiles[_index] = Object::CreateObject<Tile>();
			_tiles[_index]->Init(j, i);
			_tiles[_index]->SetAllowsRender(false);
		}
	}

	for (int i = 0; i < SAMPLE_TILE_Y_NUM; ++i)
	{
		for (int j = 0; j < SAMPLE_TILE_X_NUM; ++j)
		{
			// 20200120 TODO : Sample tile, adjust the position
			_sampleTile[i * SAMPLE_TILE_X_NUM + j] = Object::CreateObject<Tile>();
			_sampleTile[i * SAMPLE_TILE_X_NUM + j]->Init(30 + j, i);
			_sampleTile[i * SAMPLE_TILE_X_NUM + j]->AddComponent<Sprite>()->SetRectColor(ColorF::White);	// ???
			_sampleTile[i * SAMPLE_TILE_X_NUM + j]->GetComponent<Sprite>()->SetStrokeWidth(3.0f);
			
			_sampleTile[i * SAMPLE_TILE_X_NUM + j]->GetComponent<Sprite>()->SetCameraAffect(false);
			//_sampleTile[i * SAMPLE_TILE_X_NUM + j]->SetAllowsRender(false);
		}
	}

	// 20200120 FIXME : Text를 살려라..!
	//obj = Object::CreateObject<Object>();
	//obj->GetTrans()->SetPos(200, 100);
	//obj->AddComponent<Text>();
	//obj->GetComponent<Text>()->CreateText(L"Where are you", 20, 200, 200, ColorF::White);
}

void Maptool::SetMap()
{
}
