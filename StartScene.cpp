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
	_player2 = new Player;
	_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	//_player2->GetGraphic()->GetGraphic()->SetFlip(true);


	cout << "스타트씬" << endl;
	return S_OK;
}

void StartScene::release()
{
	cout << "릴리즈" << endl;
}

void StartScene::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("game");

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _player->GetTrans()->pos += Vector2::left * 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_player->GetTrans()->pos += Vector2::right * 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player->GetTrans()->pos += Vector2::up * 5;
	}	
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _player->GetTrans()->pos += Vector2::down * 5;


	
}

void StartScene::render()
{
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2, WINSIZEY / 2));
	char buffer[128];
	sprintf_s(buffer, "%f", _player->GetTrans()->bottomPos.y);
	GRAPHICMANAGER->DrawTextD2D(Vector2(WINSIZEX / 2, 0), buffer,15,D2D1::ColorF::Brown);

	sprintf_s(buffer, "%f", _player2->GetTrans()->bottomPos.y);
	GRAPHICMANAGER->DrawTextD2D(Vector2(0, 0), buffer, 15, D2D1::ColorF::Brown);
}
