#include "stdafx.h"
#include "Game.h"
#include "Sprite.h"
#include"Transform.h"
Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");


	Object* obj = Object::CreateObject<Object>();
	auto a = obj->GetGraphic();
	a->Init();
	obj->GetGraphic()->SetImgName("eagle");
	obj->GetTrans()->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	obj->GetTrans()->scale = Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight());
	cout << "°ÔÀÓ¾À" << endl;
}
void Game::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("PG");
}
