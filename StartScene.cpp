#include "stdafx.h"
#include "StartScene.h"
#include "game.h"

#include "Sprite.h"
#include"Transform.h"
HRESULT StartScene::init()
{
	GRAPHICMANAGER->AddImage("eagle", L"fatkachu.png");
	SCENEMANAGER->addScene("game", new game);

	_player = new Player;
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	OBJECTMANAGER->AddObject("Start", _player);
	Player*_player2 = new Player;
	_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	//_player2->GetGraphic()->GetGraphic()->SetFlip(true);
	OBJECTMANAGER->AddObject("Start", _player2);


	cout << "스타트씬" << endl;
	return S_OK;
}

void StartScene::release()
{
	cout << "릴리즈" << endl;
	OBJECTMANAGER->SceneRelease("Start");
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("game");

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _player->GetTrans()->pos += Vector2::left * 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_player->GetTrans()->pos += Vector2::right * 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _player->GetTrans()->pos += Vector2::up * 5;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _player->GetTrans()->pos += Vector2::down * 5;

	OBJECTMANAGER->Update("Start");
}

void StartScene::render()
{
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2, WINSIZEY / 2));
	OBJECTMANAGER->Render("Start");
}
