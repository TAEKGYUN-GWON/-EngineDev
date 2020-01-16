#include "stdafx.h"
#include "StartScene.h"
void StartScene::Init()
{
	Scene::Init();

	//SCENEMANAGER->addScene("game", new Game);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	_player = Object::CreateObject<Player>();
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	//
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
	cout << "스타트씬" << endl;

	_enemy1 = Object::CreateObject<Enemy1>();
	_enemy1->Init(Vector2(500, 500));
	vEnemy.push_back(_enemy1);
	//Enemy1* enemy;
	//enemy = Object::CreateObject<Enemy1>();
	//enemy->Init(Vector2(300, 0));
	//vEnemy.push_back(enemy);
	//enemy = Object::CreateObject<Enemy1>();
	//enemy->Init(Vector2(600, 300));
	//vEnemy.push_back(enemy);
	//enemy = Object::CreateObject<Enemy1>();
	//enemy->Init(Vector2(900, 500));
	//vEnemy.push_back(enemy);
	time = 0;
	Vector2 a(5, 5);
	Vector2 b(10, 10);
	if (a < b) cout<<"맞음"<<endl;
	else cout << "틀림" << endl;
}

void StartScene::Update()
{
	Scene::Update();
	time += TIMEMANAGER->getElapsedTime();
	/*if (time >= 0.5)
	{
		for (Enemy1* e : vEnemy)
		{
			if (Vector2::Distance(_player->GetTrans()->pos, e->GetTrans()->pos) < 60)break;
			if (Vector2::Distance(_player->GetTrans()->pos, e->GetTrans()->pos) < 300)
				e->SetPath(_ast->pathFinder(e->GetTrans()->pos, _player->GetTrans()->pos));
		}
		time = 0;
	}*/
}

void StartScene::Render()
{
	_ast->Render();
	Scene::Render();
}
