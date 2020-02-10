#include "stdafx.h"
#include "TrainScene.h"
#include "Player.h"
#include "Train.h"

void TrainScene::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddFrameImage("btnSelect", L"btnSelect.png", 1, 2);

	_train = Object::CreateObject<Train>();
	_train->Init();
	//_train->GetSprite()->SetDepth()

	_btn = Object::CreateObject<Button>();
	_btn->Init();
	_btn->Setting("btnSelect", Vector2(WINSIZEX / 2, 100), PointMake(0, 0), PointMake(0, 1), cbTest, _player);
	_btn->SetScale(Vector2(0.5, 1.0f));

	_player = Object::CreateObject<Player>();
	_player->Init();
}

void TrainScene::Release()
{
	Scene::Release();

}

void TrainScene::Update()
{
	Scene::Update();
}

void TrainScene::Render()
{
	GRAPHICMANAGER->DrawFillRect(_player->GetTrans()->GetPos(), Vector2(100, 100), 0.0f, ColorF::Aquamarine);

	Scene::Render();

}

void TrainScene::cbTest(void* obj)
{
	Player* p = (Player*)obj;
	p->GetTrans()->SetPos(200, WINSIZEY / 2);
}
