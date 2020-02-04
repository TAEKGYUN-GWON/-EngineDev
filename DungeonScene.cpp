#include "stdafx.h"
#include "DungeonScene.h"
#include "EntranceScene.h"
#include "TownScene.h"
#include "Ability.h"
#include "Inventory.h"

void DungeonScene::Init()
{
	Scene::Init();

	cout << "´øÀü¾Àµé¾î¿È" << endl;

	

	_player = Object::CreateObject<Player>();
	_player->Init();
	_player->GetTrans()->SetPos(Vector2(1170,1440)+ Vector2((TILEWIDTH * Dungeon_X)/2, (TILEHEIGHT * Dungeon_Y)-150));
	_player->GetComponent<PhysicsBody>()->SetBodyPosition();
	CAMERA->SetPos(Vector2(1170, 1440));
	//_player-;
	//_player->GetHP()->GetCurrentHP();
	
	_dMgr = new DungeonMgr;
	_dMgr->Init(_player);
	//test = new Dungeon;
	//test->Init(Vector2::zero);
	UI = new UiManager;
	UI->Init();
}

void DungeonScene::Update()
{
	Scene::Update();
	_dMgr->Update();
	if (KEYMANAGER->isOnceKeyDown('0')) SCENEMANAGER->changeScene("test");
	//test->Update();
}

void DungeonScene::Render()
{
	_dMgr->Render();
	//test->Render();
	Scene::Render();

	_player->GetInventory()->Render();
	GRAPHICMANAGER->Text(Vector2(10, 6), L"Dungeon Scene", 20, 200, 30, ColorF::AliceBlue);

	wchar_t buffer[128];
	swprintf(buffer, 128, L"Fps : %f", TIMEMANAGER->GetFps());

	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 0), buffer, 20, 300, 50, ColorF::Azure);

	//swprintf(buffer, 128, L"x : %d \n y : %d ", _ptMouse.x, _ptMouse.y);
	swprintf(buffer, 128, L"x : %d \n y : %d ", (55 + _ptMouse.x) / TILEWIDTH,_ptMouse.y);

	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2-200, 0), buffer, 20, 300, 50, ColorF::Azure);

	GRAPHICMANAGER->Text(Vector2(10, 6), L"Dungeon Scene", 20, 200, 30, ColorF::AliceBlue);


	//wchar_t buffer[128];
	//int a = 0;
	//for (int i = 0; i < _dMgr->GetRoom().size(); i++)
	//{
	//	a++;
	//	swprintf(buffer, 128, L"c : %d", _dMgr->GetRoom()[i]->GetChildren().size());

	//	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 50 + a * 50), buffer, 20, 300, 50, ColorF::Azure);

	//}
	UI->Render();
}

void DungeonScene::Release()
{
	_player->Release();
	Scene::Release();
}
