#include "stdafx.h"
#include "Maptool.h"

void Maptool::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	//GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 32, 20);
	GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 2, 2);

	//obj = Object::CreateObject<Object>();
	//obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	//Sprite* a = obj->AddComponent<Sprite>();
	//a->SetImgName("eagle");
	////a->SetFlipX(true);
	//obj->GetTrans()->SetScale(Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight()));
	
	_STState = NONE;

	SetUp();

	_isDown = false;

	_curFrameX = _curFrameY = 0;
}

void Maptool::Update()
{
	Scene::Update();

	if(KEYMANAGER->isStayKeyDown('D'))
	{
		_STTab->GetTrans()->SetPos(_STTab->GetTrans()->GetPos() + Vector2::right * (300.0f * TIMEMANAGER->getElapsedTime()));
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2::right * (300.0f * TIMEMANAGER->getElapsedTime()));
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		_STTab->GetTrans()->SetPos(_STTab->GetTrans()->GetPos() + Vector2::left * (300.0f * TIMEMANAGER->getElapsedTime()));
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2::left * (300.0f * TIMEMANAGER->getElapsedTime()));
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_STTab->GetTrans()->SetPos(_STTab->GetTrans()->GetPos() + Vector2::up * (300.0f * TIMEMANAGER->getElapsedTime()));
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2::up * (300.0f * TIMEMANAGER->getElapsedTime()));
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_STTab->GetTrans()->SetPos(_STTab->GetTrans()->GetPos() + Vector2::down * (300.0f * TIMEMANAGER->getElapsedTime()));
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2::down * (300.0f * TIMEMANAGER->getElapsedTime()));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//_isDown = true;
		//_prevMouse = _ptMouse;

		if (PtInRect(&_STTab->GetTrans()->GetRect(), _ptMouse))
		{
			//_STGround->SetIsActive(true);
			_STState = OPEN;
		}
		if (_STState == SHOW && !PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		{
			//_STGround->SetIsActive(true);
			_STState = CLOSE;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//_isDown = false;

		//if (PtInRect(&_btn1->GetTrans()->GetRect(), _ptMouse))
		//{
		//	_btn1->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		//}
		if (PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		{
			_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Green);
		}
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
	

	switch (_STState)
	{
	case OPEN:
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2().left * 800.0f * TIMEMANAGER->getElapsedTime());
		if (_STGround->GetTrans()->GetPos().x <= (CAMERA->GetPosition().x + WINSIZEX) - (_STGround->GetTrans()->GetScale().x / 2))
		{
			//_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetScale().x / 2);
			_STGround->GetTrans()->SetPos(Vector2((CAMERA->GetPosition().x + WINSIZEX) - (_STGround->GetTrans()->GetScale().x / 2), _STGround->GetTrans()->GetScale().y / 2 + 2));
			_STState = SHOW;
		}
		break;
	case SHOW:
		break;
	case CLOSE:
		_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetPos() + Vector2().right * 800.0f * TIMEMANAGER->getElapsedTime());
		if (_STGround->GetTrans()->GetPos().x >= (CAMERA->GetPosition().x + WINSIZEX) + (_STGround->GetTrans()->GetScale().x / 2))
		{
			//_STGround->GetTrans()->SetPos(_STGround->GetTrans()->GetScale().x / 2);
			_STGround->GetTrans()->SetPos(Vector2((CAMERA->GetPosition().x + WINSIZEX) + (_STGround->GetTrans()->GetScale().x / 2), _STGround->GetTrans()->GetScale().y / 2 + 2));
			_STState = NONE;
		}
		break;
	case NONE:
		break;
	default:
		break;
	}

	if (KEYMANAGER->isOnceKeyUp('1'))
	{
		_curFrameX = (_curFrameX + 1) % 2;
	}
	if (KEYMANAGER->isOnceKeyUp('2'))
	{
		_curFrameY = (_curFrameY + 1) % 2;
	}
}

void Maptool::Render()
{
	Scene::Render();

	//GRAPHICMANAGER->DrawImage("test", _STGround->GetTrans()->GetPos());
	//GRAPHICMANAGER->DrawFrameImage("test", _STGround->GetTrans()->GetPos(), 3, 1);

	char buffer[128];

	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 43; ++j)
		{
			int cullX = CAMERA->GetPosition().x / TILEWIDTH;
			int cullY = CAMERA->GetPosition().y / TILEHEIGHT;

			//int cullX = 200 / TILEWIDTH;
			//int cullY = 200 / TILEHEIGHT;

			_index = (i + cullY) * TILENUMX + (j + cullX);
			
			if (_index < 0 || _index >= TILENUMX * TILENUMY) continue;
			
			//_tiles[_index]->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
			_tiles[_index]->SetAllowsRender(true);

			sprintf_s(buffer, "%d", _index);
			GRAPHICMANAGER->DrawTextD2D(_tiles[_index]->GetTrans()->GetPos(), buffer, 10, 1.0f, ColorF::Yellow);
		}
	}

	if(_STState == SHOW) GRAPHICMANAGER->DrawFrameImage("test", _STGround->GetTrans()->GetPos(), _curFrameX, _curFrameY);

	
	obj->Render();

	_STTab->Render();
	_STGround->Render();

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

			SetRect(&_tiles[i * TILENUMX + j]->GetTrans()->GetRect(),
				j * TILEWIDTH,
				i * TILEHEIGHT,
				j * TILEWIDTH + TILEHEIGHT,
				i * TILEWIDTH + TILEHEIGHT);
		}
	}
	
	_STTab = Object::CreateObject<Object>();
	_STTab->GetTrans()->SetScale(50, 118);
	_STTab->GetTrans()->SetPos((CAMERA->GetPosition().x + WINSIZEX) - (_STTab->GetTrans()->GetScale().x / 2), CAMERA->GetPosition().y + (_STTab->GetTrans()->GetScale().y / 2) + 2);
	_STTab->AddComponent<Sprite>();
	_STTab->GetComponent<Sprite>()->SetStrokeWidth(3.0f);
	_STTab->GetComponent<Sprite>()->SetRectColor(ColorF::DarkRed);
	_STTab->GetComponent<Sprite>()->SetFillRect(true);




	_STGround = Object::CreateObject<Object>();
	_STGround->GetTrans()->SetScale(Vector2(500, 418));
	//_STGround->GetTrans()->SetPos(Vector2(WINSIZEX - (_STGround->GetTrans()->GetScale().x / 2), _STGround->GetTrans()->GetScale().y / 2 + 2));
	_STGround->GetTrans()->SetPos(Vector2((CAMERA->GetPosition().x + WINSIZEX) + (_STGround->GetTrans()->GetScale().x / 2), CAMERA->GetPosition().y + _STGround->GetTrans()->GetScale().y / 2 + 2));
	_STGround->AddComponent<Sprite>();
	_STGround->GetComponent<Sprite>()->SetStrokeWidth(3.0f);
	_STGround->GetComponent<Sprite>()->SetFillRect(true);
	_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Green);


	
	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(200, 100);
	obj->AddComponent<Text>();
	obj->GetComponent<Text>()->CreateText(L"Where are you", 20, 200, 200, ColorF::White);
}

void Maptool::SetMap()
{
}
