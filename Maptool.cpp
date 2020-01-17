#include "stdafx.h"
#include "Maptool.h"

void Maptool::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");
	GRAPHICMANAGER->AddFrameImage("idle", L"idle.png", 8, 1);
	GRAPHICMANAGER->AddFrameImage("fall_right", L"fall_right.png", 10, 1);

	GRAPHICMANAGER->AddFrameImage("1", L"1.png", 9, 1);
	GRAPHICMANAGER->AddFrameImage("2", L"2.png", 9, 1);
	GRAPHICMANAGER->AddFrameImage("3", L"3.png", 9, 1);
	GRAPHICMANAGER->AddFrameImage("4", L"4.png", 9, 1);


	GRAPHICMANAGER->AddFrameImage("5", L"5.png", 10, 1);
	GRAPHICMANAGER->AddFrameImage("6", L"6.png", 8, 1);

	GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 32, 20);

	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	//obj->AddComponent<Sprite>()->SetImgName("eagle");
	auto a = obj->AddComponent<Sprite>();
	a->SetImgName("eagle");
	a->SetFlipX(true);
	a->GetGraphic()->SetFlipX(obj->GetComponent<Sprite>()->GetFlipX());
	//obj->GetComponent<Sprite>()->GetGraphic()->SetFlipX(obj->GetComponent<Sprite>()->GetF);
	//obj->GetGraphic()->SetImgName("eagle");
	//obj->GetTrans()->SetScale(Vector2(obj->GetGraphic()->GetGraphic()->GetFrameWidth(), obj->GetGraphic()->GetGraphic()->GetFrameHeight()));
	obj->GetTrans()->SetScale(Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight()));

	Object* obj2 = Object::CreateObject<Object>();
	obj2->GetTrans()->SetPos(Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	obj2->AddComponent<Sprite>()->SetImgName("eagle");
	obj2->GetTrans()->SetScale(Vector2(50, 100));
	obj2->GetComponent<Sprite>()->SetAlpha(0.3f);

	obj3 = Object::CreateObject<Object>();
	obj3->GetTrans()->SetPos(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 200));
	Sprite* s = obj3->AddComponent<Sprite>();
	s->Init(true, true);
	s->SetImgName("idle");
	//s->SetFlipX(true);
	obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth() - 10, s->GetGraphic()->GetFrameHeight() - 10));

	//SetUp();
}

void Maptool::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//if (PtInRect(&_btn1->GetTrans()->GetRect(), _ptMouse))
		//{
		//	_btn1->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		//}
		//if (PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		//{
		//	_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		//}
	}

	if (KEYMANAGER->isOnceKeyDown('U')) obj->GetComponent<Sprite>()->SetFlipX(!obj->GetComponent<Sprite>()->GetFlipX());
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("fall_right");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));

	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("idle");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("4");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("1");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("2");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("3");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("5");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		obj3->GetComponent<Sprite>()->SetImgName("6");
		//Sprite* s = obj3->AddComponent<Sprite>();
		//obj3->GetTrans()->SetScale(Vector2(s->GetGraphic()->GetFrameWidth(), s->GetGraphic()->GetFrameHeight()));
	}
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
			_tiles[i * TILENUMX + j] = Object::CreateObject<Tile>();
			_tiles[i * TILENUMX + j]->Init(j, i);

			SetRect(&_tiles[i * TILENUMX + j]->GetTrans()->GetRect(),
				j * TILEWIDTH,
				i * TILEHEIGHT,
				j * TILEWIDTH + TILEHEIGHT,
				i * TILEWIDTH + TILEHEIGHT);
		}
	}

	_STGround = Object::CreateObject<Object>();
	_STGround->GetTrans()->SetPos(Vector2(WINSIZEX / 2, 200));
	_STGround->GetTrans()->SetScale(Vector2(300, 200));
	_STGround->AddComponent<Sprite>();
}

void Maptool::SetMap()
{
}
