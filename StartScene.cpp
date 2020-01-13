#include "stdafx.h"
#include "StartScene.h"
#include "Sprite.h"
#include"Transform.h"
#include"Game.h"
void StartScene::Init()
{
	Scene::Init();

	SCENEMANAGER->addScene("game", new Game);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	_player =Object::CreateObject<Player>();
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	
	_player2 = Object::CreateObject<Player>();
	_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	_player2->GetGraphic()->GetGraphic()->SetFlip(false);

	//Object* obj = Object::CreateObject();
	//auto a = obj->GetGraphic();
	//a->Init();
	//obj->GetGraphic()->SetImgName("eagle");
	//obj->GetTrans()->SetPos(WINSIZEX/2,WINSIZEY/2);
	//obj->GetTrans()->scale = Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight());
	//
	//_player = obj;
	cout << "½ºÅ¸Æ®¾À" << endl;
}

void StartScene::Update()
{
	Scene::Update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("game");
}
