#include "stdafx.h"
#include "StartScene.h"
#include "DungeonScene.h"
#include "EntranceScene.h"
#include "ShopScene.h"
#include "TownScene.h"
#include "Maptool.h"
#include "TestScene.h"
#include"ETCS.h"
#include "BossRoom.h"

void StartScene::Init()
{
	Scene::Init();
	SCENEMANAGER->addScene("Dungeon", new DungeonScene);
	SCENEMANAGER->addScene("Town", new TownScene);
	SCENEMANAGER->addScene("Entrance", new EntranceScene);
	SCENEMANAGER->addScene("Shop", new ShopScene);
	SCENEMANAGER->addScene("Maptool", new Maptool);
	SCENEMANAGER->addScene("test", new TestScene);
	SCENEMANAGER->addScene("BossRoom", new BossRoom);

	GraphicsManager::getSingleton()->AddImage("dd", L"eagle.png");
	GraphicsManager::getSingleton()->AddFrameImage("fatkachu", L"fatkachu.png", 4, 1);
	GRAPHICMANAGER->AddFrameImage("bn", L"blueNumber.png", 4, 1);

	GRAPHICMANAGER->AddImage("coin", L"resource/img/UI/coin.png");
	GRAPHICMANAGER->AddImage("moneyBag", L"resource/img/UI/moneyBag.png");
	GRAPHICMANAGER->AddImage("UI_Bag", L"resource/img/UI/UI_Bag.png");
	GRAPHICMANAGER->AddImage("UI_Potion", L"resource/img/UI/UI_Potion.png");
	GRAPHICMANAGER->AddImage("heart", L"resource/img/UI/heart.png");
	GRAPHICMANAGER->AddImage("heart", L"resource/img/UI/heart.png");
	GRAPHICMANAGER->AddFrameImage("UI_WeaponSwap", L"resource/img/UI/UI_WeaponSwap.png", 4, 2);
	GRAPHICMANAGER->AddFrameImage("num", L"number.png", 4, 1);
	GRAPHICMANAGER->FindImage("num")->SetFrameSize(Vector2(10,10));
	Object* obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(WINSIZEX / 2+200, WINSIZEY - 200);
	//obj->GetTrans()->SetScale(200,200);
	auto n = obj->AddComponent<Sprite>();
	n->Init(true, true);
	n->SetImgName("num");


	GRAPHICMANAGER->AddImage("Vine", L"resource/img/Items/Vine.png");
	GRAPHICMANAGER->AddImage("Crystal_Energy", L"resource/img/Items/Crystal_Energy.png");
	GRAPHICMANAGER->AddImage("Treated_Wood", L"resource/img/Items/Treated_Wood.png");
	GRAPHICMANAGER->AddImage("Amulet_ring", L"resource/img/Items/amulet_ring.png");
	GRAPHICMANAGER->AddImage("Broken_Sword", L"resource/img/Items/Broken_Sword.png");
	GRAPHICMANAGER->AddImage("Energy_Crystal", L"resource/img/Items/Energy_Crystal.png");
	GRAPHICMANAGER->AddImage("Naja_Note", L"resource/img/Items/Naja_Note.png");
	GRAPHICMANAGER->AddImage("Reinforced_Steel_G", L"resource/img/Items/Reinforced_Steel_G.png");
	GRAPHICMANAGER->AddImage("Golem_Core", L"resource/img/Items/Golem_Core.png");
	GRAPHICMANAGER->AddImage("Familiar_Egg", L"resource/img/Items/Familiar_Egg.png");
	GRAPHICMANAGER->AddImage("Reinforced_Steel_Y", L"resource/img/Items/Reinforced_Steel_Y.png");
	GRAPHICMANAGER->AddImage("Golem_King_Design ", L"resource/img/Items/Golem_King_Design.png");
	//GRAPHICMANAGER->AddFrameImage("Items", L"resource/img/Items/Items.png",4,3);





	//ui = new UiManager;
	//ui->Init();
	//inven = new Inventory;
	//inven->Init();
	//ui->SetInvenLink(inven);

	//inven->Insert(Item::CreateItem<Golem_Core>(Vector2(0, 0)));
	//inven->Insert(Item::CreateItem<Golem_Core>(Vector2(0, 0)));
	//inven->Insert(Item::CreateItem<Crystal_Energy>(Vector2(0, 0)));
	//

	//_smithy = new Smithy;
	//_smithy->Init(inven);



	obj = Object::CreateObject<Object>();
	obj->GetTrans()->SetPos(Vector2(WINSIZEX / 2, 200));
	obj->AddComponent<Sprite>();
	obj->GetComponent<Sprite>()->SetImgName("dd");
	auto a = GRAPHICMANAGER->FindImage("dd");
	obj->GetComponent<Sprite>()->SetSize(Vector2(a->GetFrameWidth(), a->GetFrameHeight()));
	//obj->GetTrans()->SetScale(Vector2(obj->GetComponent<Sprite>()->GetGraphic()->GetFrameWidth(), obj->GetComponent<Sprite>()->GetGraphic()->GetFrameWidth()));
	obj->GetTrans()->SetScale(Vector2(100, 50));


	Object* obj2 = Object::CreateObject<Object>();
	obj2->GetTrans()->SetPos(Vector2(WINSIZEX / 2 + 100, 500));
	obj2->AddComponent<Sprite>()->Init(true);
	obj2->GetComponent<Sprite>()->SetImgName("fatkachu");
	obj2->GetComponent<Sprite>()->SetSize(Vector2(100, 38));
	obj2->GetTrans()->SetScale(Vector2(obj2->GetComponent<Sprite>()->GetGraphic()->GetFrameWidth(), obj2->GetComponent<Sprite>()->GetGraphic()->GetFrameWidth()));
}

void StartScene::Update()
{
	Scene::Update();
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("Dungeon");
	}
	if (KEYMANAGER->isOnceKeyDown('2')) SCENEMANAGER->changeScene("Town");
	if (KEYMANAGER->isOnceKeyDown('3')) SCENEMANAGER->changeScene("Entrance");
	if (KEYMANAGER->isOnceKeyDown('4')) SCENEMANAGER->changeScene("Shop");
	if (KEYMANAGER->isOnceKeyDown('5')) SCENEMANAGER->changeScene("Maptool");
	if (KEYMANAGER->isOnceKeyDown('0')) SCENEMANAGER->changeScene("test");
	if (KEYMANAGER->isOnceKeyDown('6')) SCENEMANAGER->changeScene("BossRoom");

	//inven->Update();

	//_smithy->Update();
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


	string a = "None";
	wstring b(a.begin(), a.end());
	wchar_t* str;
	str = &b[0];

	//GRAPHICMANAGER->Text(Vector2(WINSIZEX/2, 200), b, 20, 300, 50, ColorF::Azure);
	//
	//GRAPHICMANAGER->DrawFrameImage("bn", Vector2(WINSIZEX / 2, 400), 0, 0, Vector2(320, 50));
	//GRAPHICMANAGER->DrawFrameImage("bn", Vector2(WINSIZEX / 2, 460), 1, 0, Vector2(320, 50));
	//GRAPHICMANAGER->DrawFrameImage("bn", Vector2(WINSIZEX / 2, 520), 2, 0, Vector2(320, 50));
	//GRAPHICMANAGER->DrawFrameImage("bn", Vector2(WINSIZEX / 2, 580), 3, 0, Vector2(320, 50));
	//
	//GRAPHICMANAGER->DrawRect(Vector2(WINSIZEX / 2, 400), Vector2(80, 50), 0.0f, ColorF::Red);
	//GRAPHICMANAGER->DrawRect(Vector2(WINSIZEX / 2, 460), Vector2(80, 50), 0.0f, ColorF::Red);
	//GRAPHICMANAGER->DrawRect(Vector2(WINSIZEX / 2, 520), Vector2(80, 50), 0.0f, ColorF::Red);
	//GRAPHICMANAGER->DrawRect(Vector2(WINSIZEX / 2, 580), Vector2(80, 50), 0.0f, ColorF::Red);

	//swprintf(buffer, 128, L"test X : %f\test Y : %f", test->GetTrans()->GetPos().x, test->GetTrans()->GetPos().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 400), buffer, 20, 300, 50, ColorF::Azure);
	//ui->Render();
//	inven->Render();

	//_smithy->Render();
}

void StartScene::Release()
{
	Scene::Release();
	//inven->Release();
}

