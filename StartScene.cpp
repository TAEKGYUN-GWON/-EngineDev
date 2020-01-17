#include "stdafx.h"
#include "StartScene.h"
#include "Sprite.h"
#include"Transform.h"

void StartScene::Init()
{
	Scene::Init();

	//SCENEMANAGER->addScene("maptool", new Maptool);
	//GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	_player =Object::CreateObject<Player>();
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));

	_enemy = Object::CreateObject<Enemy1>();
	_enemy->Init(Vector2(WINSIZEX / 3, WINSIZEY / 3));
	
	//_player2 = Object::CreateObject<Player>();
	//_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	//_player2->GetGraphic()->GetGraphic()->SetFlip(false);

	//Object* obj = Object::CreateObject();
	//auto a = obj->GetGraphic();
	//a->Init();
	//obj->GetGraphic()->SetImgName("eagle");
	//obj->GetTrans()->SetPos(WINSIZEX/2,WINSIZEY/2);
	//obj->GetTrans()->scale = Vector2(a->GetGraphic()->GetFrameWidth(), a->GetGraphic()->GetFrameHeight());
	//
	//_player = obj;
	_ast = new Astar;
	_ast->Init();

	timer = 0;
	cout << "½ºÅ¸Æ®¾À" << endl;
}

void StartScene::Update()
{
	Scene::Update();
	//SCENEMANAGER->changeScene("maptool");
	timer += TIMEMANAGER->getElapsedTime();
	if (timer >= 1)
	{
		_enemy->SetPath(_ast->pathFinder(_enemy->GetTrans()->pos, _player->GetTrans()->pos));
			timer = 0;
	}
}

void StartScene::Render()
{
	Scene::Render();
	_ast->Render();
}
