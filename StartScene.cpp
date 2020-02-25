#include "stdafx.h"
#include "StartScene.h"
#include "ProceduralTest.h"
#include "Maptool.h"
#include "TestScene.h"
#include "Knight.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Player.h"
#include "ChaosCircle.h"
void StartScene::Init()
{
	Scene::Init();

	//GRAPHICMANAGER->AddFrameImage("will", L"blueNumber.png", 4, 1);
	//GRAPHICMANAGER->AddImage("will", L"blueNumber.png");
	//GRAPHICMANAGER->AddFrameImage("eagle", L"BossUp.png",32,1);
	GRAPHICMANAGER->AddImage("eagle", L"eagle.png");

	wstring dir = L"Resource/Wizard/Tile/";
	for (int i = 1; i <= 4; i++)
	{
		string str = "Tile";
		wstring item = to_wstring(i) + L".png";
		GRAPHICMANAGER->AddImage(str + to_string(i), dir + item);
	}

	//CAMERA->SetScale(Vector2(1, 1));
	//CAMERA->SetPos(Vector2(430, 204));
	SCENEMANAGER->addScene("t", new TestScene);
	//SCENEMANAGER->addScene("tt", new Maptool);
	SCENEMANAGER->addScene("t1", new ProceduralTest);

	Object* wall = Object::CreateObject<Object>();
	wall->SetName("Wall");
	wall->Init();
	wall->GetTrans()->SetPos(WINSIZE/2 +Vector2(100,100));
	wall->GetTrans()->SetScale(50, 50);
	auto p = wall->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1);

	Rogue* so = Object::CreateObject<Rogue>();
	so->Init(WINSIZE / 3);

	Player* test = Object::CreateObject<Player>();
	test->Init(WINSIZE / 2);

	//_obj = Object::CreateObject<Object>();
	//_obj->GetTrans()->SetPos(WINSIZEX / 2-100, WINSIZEY / 2);
	//_obj->GetTrans()->SetScale(100, 100);
	//_obj->SetName("1");
	//auto s = _obj->AddComponent<Sprite>();
	//s->Init();
	//s->SetImgName("eagle");
	//
	//
	//Object* obj = Object::CreateObject<Object>();
	//obj->Init();
	//obj->SetName("2");
	//obj->GetTrans()->SetPos(WINSIZE / 2);
	//s = obj->AddComponent<Sprite>();
	//s->Init();
	//s->SetImgName("eagle");
	_bar = new ProgressBar;
	_bar->Init("gaugeUp", "gaugeDown", Vector2(200, 200));
	current = max = 100;
}

void StartScene::Update()
{
	Scene::Update();
	_bar->SetGauge(current -= 3.0f * TIMEMANAGER->getElapsedTime(), max);
	if(KEYMANAGER->isOnceKeyDown('Y')) SCENEMANAGER->changeScene("tt");
	if(KEYMANAGER->isOnceKeyDown('T')) SCENEMANAGER->changeScene("t");
	if(KEYMANAGER->isOnceKeyDown('P')) SCENEMANAGER->changeScene("t1");
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		Player* player = (Player*)GetChildFromName("Player");
		float angle = Vector2::GetAngle(player->GetTrans()->GetPos(), _ptMouse);
		player->GetPhysics()->ApplyForce(b2Vec2(cosf(angle), -sinf(angle))); 
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		Player* player = (Player*)GetChildFromName("Player");
		player->GetPhysics()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
	}
	CAMERA->Update();
}

void StartScene::Render()
{
	Scene::Render();
	_bar->Render();
	//GRAPHICMANAGER->Text(Vector2(100, 100), L"1) Dungeon Scene", 20, 300, 50, ColorF::AliceBlue);
	//GRAPHICMANAGER->Text(Vector2(100, 150), L"2) Town Scene", 20, 300, 50, ColorF::AntiqueWhite);
	//GRAPHICMANAGER->Text(Vector2(100, 200), L"3) Entrance Scene", 20, 300, 50, ColorF::Aqua);
	//GRAPHICMANAGER->Text(Vector2(100, 250), L"4) Shop Scene", 20, 300, 50, ColorF::Aquamarine);
	//GRAPHICMANAGER->Text(Vector2(100, 300), L"5) Maptool Scene", 20, 300, 50, ColorF::Azure);
	//
	//
	//wchar_t buffer[128];
	//swprintf(buffer, 128, L"Camera X : %f\nCamera Y : %f", CAMERA->GetPosition().x, CAMERA->GetPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 100), buffer, 20, 300, 50, ColorF::Azure);
	//
	//
	//swprintf(buffer, 128, L"Maoue X : %f\Mouse Y : %f", MOUSEPOINTER->GetMouseWorldPosition().x, MOUSEPOINTER->GetMouseWorldPosition().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 50, ColorF::Azure);
	//
	//Vector2 pos = CAMERA->GetPosition() + _ptMouse;
	//
	//swprintf(buffer, 128, L"WorldMaoue X : %f\WorldMaoue Y : %f", pos.x, pos.y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 300), buffer, 20, 300, 50, ColorF::Azure);


	//swprintf(buffer, 128, L"%d %d", GRAPHICMANAGER->FindImage("will")->GetFrameWidth(), GRAPHICMANAGER->FindImage("will")->GetFrameHeight());
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, 200), buffer, 20, 300, 30, ColorF::AntiqueWhite);


	//GRAPHICMANAGER->DrawFrameImage("will", Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0, Vector2(0.7f, 0.5f));
	//GRAPHICMANAGER->DrawImage("eagle", Vector2(400, 500), Vector2(1, 1), 0.0f);
}

void StartScene::Release()
{
	Scene::Release();
}
