#include "stdafx.h"
#include "StartScene.h"
#include "ProceduralTest.h"
#include "Maptool.h"
#include "TestScene.h"
#include "TrainScene.h"
#include "UndergroundScene.h"

void StartScene::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	//SCENEMANAGER->addScene("t", new TestScene);
	SCENEMANAGER->addScene("maptool", new Maptool);
	//SCENEMANAGER->addScene("t1", new ProceduralTest);
	SCENEMANAGER->addScene("train", new TrainScene);
	SCENEMANAGER->addScene("underground", new UndergroundScene);

	//SCENEMANAGER->changeScene("train");
}

void StartScene::Update()
{
	Scene::Update();

	if(KEYMANAGER->isOnceKeyDown('Y')) SCENEMANAGER->changeScene("maptool");
	//if(KEYMANAGER->isOnceKeyDown('T')) SCENEMANAGER->changeScene("t");
	//if(KEYMANAGER->isOnceKeyDown('P')) SCENEMANAGER->changeScene("t1");
	if(KEYMANAGER->isOnceKeyDown('1')) SCENEMANAGER->changeScene("train");
	if(KEYMANAGER->isOnceKeyDown('2')) SCENEMANAGER->changeScene("underground");
	CAMERA->Control();
}

void StartScene::Render()
{
	Scene::Render();

	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2 - 130, WINSIZEY / 2 + 30), L"[ The Final Station ]", 30, 300, 50, ColorF::AliceBlue, TextPivot::CENTER_TOP);

	//wchar_t buffer[128];
	//swprintf(buffer, 128, L"Camera X : %f\nCamera Y : %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 300, 50, ColorF::Azure);
	//
	//
	//swprintf(buffer, 128, L"Maoue X : %f\Mouse Y : %f", MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 50, ColorF::Azure);
	//
	//Vector2 pos = CAMERA->GetPosition() + _ptMouse;
	//
	//swprintf(buffer, 128, L"WorldMaoue X : %f\WorldMaoue Y : %f", pos.x, pos.y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 300), buffer, 20, 300, 50, ColorF::Azure);

	GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2 - 20, WINSIZEY / 2 - 100), Vector2(1, 1), 0.0f);
}

void StartScene::Release()
{
	Scene::Release();

}
