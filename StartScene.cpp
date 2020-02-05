#include "stdafx.h"
#include "StartScene.h"


void StartScene::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddFrameImage("will", L"will_dungeon.png", 10, 13);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	_obj = Object::CreateObject<Object>();
	_obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2, WINSIZEY - 200));
	_obj->AddComponent<Sprite>()->Init(true, true);
	_obj->GetComponent<Sprite>()->SetImgName("will");
	_obj->GetComponent<Sprite>()->SetFrameY(11);
	_obj->GetComponent<Sprite>()->SetScale(Vector2(0.7f, 0.3f));
}

void StartScene::Update()
{
	Scene::Update();
}

void StartScene::Render()
{
	Scene::Render();

	GRAPHICMANAGER->Text(Vector2(100, 100), L"1) Dungeon Scene", 20, 300, 50, ColorF::AliceBlue);
	GRAPHICMANAGER->Text(Vector2(100, 150), L"2) Town Scene", 20, 300, 50, ColorF::AntiqueWhite);
	GRAPHICMANAGER->Text(Vector2(100, 200), L"3) Entrance Scene", 20, 300, 50, ColorF::Aqua);
	GRAPHICMANAGER->Text(Vector2(100, 250), L"4) Shop Scene", 20, 300, 50, ColorF::Aquamarine);
	GRAPHICMANAGER->Text(Vector2(100, 300), L"5) Maptool Scene", 20, 300, 50, ColorF::Azure);


	wchar_t buffer[128];
	swprintf(buffer, 128, L"Camera X : %f\nCamera Y : %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX/2, 100), buffer, 20, 300, 50, ColorF::Azure);

	swprintf(buffer, 128, L"%d %d", GRAPHICMANAGER->FindImage("will")->GetFrameWidth(), GRAPHICMANAGER->FindImage("will")->GetFrameHeight());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 30, ColorF::AntiqueWhite);


	//GRAPHICMANAGER->DrawFrameImage("will", Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0, Vector2(0.7f, 0.5f));
	GRAPHICMANAGER->DrawImage("eagle", Vector2(400, 500), Vector2(1, 1), 0.0f);
}

void StartScene::Release()
{
	Scene::Release();

}

