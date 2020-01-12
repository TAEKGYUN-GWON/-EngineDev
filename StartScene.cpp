#include "stdafx.h"
#include "StartScene.h"
#include "Sprite.h"
#include"Transform.h"
void StartScene::Init()
{
	Scene::Init();

	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	//_player = (Player*)Object::CreateObject();
	//_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	//
	//_player2 = (Player*)Object::CreateObject();
	//_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));

	Object* obj = Object::CreateObject();
	auto a = obj->GetGraphic();
	a->Init();
	obj->GetGraphic()->SetImgName("eagle");
	obj->GetTrans()->SetPos(WINSIZEX/2,WINSIZEY/2);
	obj->GetTrans()->scale = Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight());

	obj->GetGraphic()->GetGraphic()->SetFlip(true);
	_player = obj;
	cout << "½ºÅ¸Æ®¾À" << endl;
}
