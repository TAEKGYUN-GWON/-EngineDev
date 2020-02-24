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

	ShowCursor(false);

	//SCENEMANAGER->addScene("t", new TestScene);
	SCENEMANAGER->addScene("maptool", new Maptool);
	//SCENEMANAGER->addScene("t1", new ProceduralTest);
	SCENEMANAGER->addScene("train", new TrainScene);
	SCENEMANAGER->addScene("underground", new UndergroundScene);

	_logoImg = Image::CreateImage("logo", "Resource/UI/Logo dlc.png");
	_eagleImg = Image::CreateImage("eagle", "eagle.png");
	_cursorImg = Image::CreateImage("cursor", "Resource/UI/cursor.png");
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

	//GRAPHICMANAGER->DrawImage("logo", Vector2(WINSIZEX / 2 + 60, WINSIZEY / 2), 1.0f, PIVOT::CENTER, false);
	_logoImg->Render(Vector2(WINSIZEX / 2 + 60, WINSIZEY / 2), 1.0f, PIVOT::CENTER, false);

	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2 - 180, WINSIZEY / 2 + 200), L"[ The Final Station ]", 30, 300, 50, ColorF(ColorF::AliceBlue, 0.6f), TextPivot::CENTER_TOP);

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

	//GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2 - 20, WINSIZEY / 2 - 100), Vector2(1, 1), 0.0f, false, 1.0f, PIVOT::CENTER, false);
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2 - 280, WINSIZEY / 2 - 150), Vector2(1, 1), 0.0f, false, 1.0f, PIVOT::CENTER, false);
	_eagleImg->Render(Vector2(WINSIZEX / 2 - 280, WINSIZEY / 2 - 150), Vector2(1, 1), 0.0f, false, 1.0f, PIVOT::CENTER, false);

	_cursorImg->Render(MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);
}

void StartScene::Release()
{
	SAFE_OBJECT_RELEASE(_cursorImg);
	SAFE_OBJECT_RELEASE(_logoImg);
	SAFE_OBJECT_RELEASE(_eagleImg);

	Scene::Release();
}
