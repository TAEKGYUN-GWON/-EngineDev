#include "stdafx.h"
#include "StartScene.h"
#include "ProceduralTest.h"
#include "Maptool.h"
#include "TestScene.h"
void StartScene::Init()
{
	Scene::Init();

	//GRAPHICMANAGER->AddFrameImage("will", L"will_dungeon.png", 10, 13);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	SCENEMANAGER->addScene("t", new TestScene);
	SCENEMANAGER->addScene("tt", new Maptool);
	SCENEMANAGER->addScene("t1", new ProceduralTest);

}

void StartScene::Update()
{
	Scene::Update();
	
	if(KEYMANAGER->isOnceKeyDown('Y')) SCENEMANAGER->changeScene("tt");
	if(KEYMANAGER->isOnceKeyDown('T')) SCENEMANAGER->changeScene("t");
	if(KEYMANAGER->isOnceKeyDown('P')) SCENEMANAGER->changeScene("t1");
	CAMERA->Control();
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
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 300, 50, ColorF::Azure);


	swprintf(buffer, 128, L"Maoue X : %f\Mouse Y : %f", MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 50, ColorF::Azure);

	Vector2 pos = CAMERA->GetPosition() + _ptMouse;

	swprintf(buffer, 128, L"WorldMaoue X : %f\WorldMaoue Y : %f", pos.x, pos.y);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 300), buffer, 20, 300, 50, ColorF::Azure);


	//swprintf(buffer, 128, L"%d %d", GRAPHICMANAGER->FindImage("will")->GetFrameWidth(), GRAPHICMANAGER->FindImage("will")->GetFrameHeight());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 30, ColorF::AntiqueWhite);


	//GRAPHICMANAGER->DrawFrameImage("will", Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0, Vector2(0.7f, 0.5f));
	GRAPHICMANAGER->DrawImage("eagle", Vector2(400, 500), Vector2(1, 1), 0.0f);
}

void StartScene::Release()
{
	Scene::Release();

}

