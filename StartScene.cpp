#include "stdafx.h"
#include "StartScene.h"
#include "game.h"
#include "Player.h"
#include "Sprite.h"
HRESULT StartScene::init()
{
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");
	SCENEMANAGER->addScene("game", new game);

	Player* _player = new Player;
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	OBJECTMANAGER->AddObject("Start", _player);
	Player*_player2 = new Player;
	_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	_player2->GetGraphic()->GetGraphic()->SetFlip(true);

	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("game");
	OBJECTMANAGER->Update("Start");
}

void StartScene::render()
{
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(WINSIZEX / 2, WINSIZEY / 2));
	OBJECTMANAGER->Render("Start");
}
