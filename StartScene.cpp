#include "stdafx.h"
#include "StartScene.h"


void StartScene::Init()
{
	Scene::Init();}

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

	wchar_t buffer[1024];
	swprintf(buffer, 128, L"Camera X : %f\nCamera Y : %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX/2, 100), buffer, 20, 300, 50, ColorF::Azure);


	
}

void StartScene::Release()
{
	Scene::Release();
}

