#include "stdafx.h"
#include "playGround.h"
#include "Transform.h"
#include "Object.h"
#include "PhysicsBody.h"
#include "Sprite.h"
#include "StartScene.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
float32 timeStep;
int32 velocityIterations;
int32 positionIterations;

playGround::playGround()
{
}

playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);
	//박스 월드 생성 및 콘텍트 리스너 세팅
	b2Vec2 gravity(0.f, 10.f);
	BOXWORLDMANAGER->CreateWorld(gravity);
	BOXWORLDMANAGER->GetWorld()->SetAllowSleeping(true);
	BOXWORLDMANAGER->GetWorld()->SetContinuousPhysics(true);
	PHYSICSMANAGER->SetWorld(BOXWORLDMANAGER->GetWorld());
	BOXWORLDMANAGER->GetWorld()->SetContactListener(PHYSICSMANAGER);

	//박스 월드 시간 세팅
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;

	//=============================== 이 밑으로 init ==============================

	GRAPHICMANAGER->AddFrameImage("number", L"number.png", 4, 1);

	SCENEMANAGER->addScene("StartScene", new StartScene);
	//SCENEMANAGER->changeScene("StartScene");

	_player = new Player;
	_player->Init(Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));

	_player2 = new Player;
	_player2->Init(Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	_player2->GetGraphic()->GetGraphic()->SetFlip(true);

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
	
	OBJECTMANAGER->Release();
	//SAFE_OBJECT_RELEASE(_player);
	//SAFE_DELETE(_player);
	//SAFE_OBJECT_RELEASE(_player2);
	//SAFE_DELETE(_player2);
}


void playGround::update()
{
	gameNode::update();
	BOXWORLDMANAGER->GetWorld()->Step(timeStep, velocityIterations, positionIterations);

	_player->Update();
	_player2->Update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) SCENEMANAGER->changeScene("StartScene");
}

void playGround::render()
{
	draw();
}

void playGround::draw()
{
	_player->Render();
	_player2->Render();
}


