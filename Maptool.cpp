#include "stdafx.h"
#include "Maptool.h"

void Maptool::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");
	GRAPHICMANAGER->AddFrameImage("test", L"pacman_sprite_2.png", 32, 20);

	Object* obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	obj->GetGraphic()->SetImgName("eagle");
	obj->GetTrans()->SetScale(Vector2(obj->GetGraphic()->GetGraphic()->GetFrameWidth(), obj->GetGraphic()->GetGraphic()->GetFrameHeight()));

	Object* obj2 = Object::CreateObject<Object>();
	obj2->GetTrans()->SetPos(Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	obj2->GetGraphic()->SetImgName("eagle");
	//obj2->GetGraphic()->GetGraphic()->SetFlip(true);
	//obj2->GetTrans()->SetScale(Vector2(obj2->GetGraphic()->GetGraphic()->GetFrameWidth(), obj2->GetGraphic()->GetGraphic()->GetFrameHeight()));
	obj2->GetTrans()->SetScale(Vector2(10, 50));

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
		if (PtInRect(&_STGround->GetTrans()->GetRect(), _ptMouse))
		{
			_STGround->GetComponent<Sprite>()->SetRectColor(ColorF::Red);
		}
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
