#include "stdafx.h"
#include "StartScene.h"
#include "playGround.h"

HRESULT StartScene::init()
{
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	//SCENEMANAGER->addScene("playGround", new playGround);

	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("playGround");
}

void StartScene::render()
{
	GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2, WINSIZEY / 2));
}
