#include "stdafx.h"
#include "Train.h"

void Train::Init()
{
	Object::Init();

	GRAPHICMANAGER->AddImage("train", L"Resource/Train/Train_ 2.png");

	_trans->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	_trans->SetScale(200, 100);

	_sprite = AddComponent<Sprite>();
	_sprite->SetImgName("train");
	_sprite->SetScale(Vector2(3.5f, 3.5f));
}

void Train::Update()
{
	Object::Update();
}

void Train::Render()
{
	Object::Render();
}
