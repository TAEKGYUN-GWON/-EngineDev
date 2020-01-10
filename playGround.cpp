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
	Scene::init(true);
	//�ڽ� ���� ���� �� ����Ʈ ������ ����
	b2Vec2 gravity(0.f, 10.f);
	BOXWORLDMANAGER->CreateWorld(gravity);
	BOXWORLDMANAGER->GetWorld()->SetAllowSleeping(true);
	BOXWORLDMANAGER->GetWorld()->SetContinuousPhysics(true);
	PHYSICSMANAGER->SetWorld(BOXWORLDMANAGER->GetWorld());
	BOXWORLDMANAGER->GetWorld()->SetContactListener(PHYSICSMANAGER);

	//�ڽ� ���� �ð� ����
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;

	//=============================== �� ������ init ==============================

	GRAPHICMANAGER->AddFrameImage("number", L"eric_idle.png", 2, 2);

	SCENEMANAGER->addScene("StartScene", new StartScene);
	SCENEMANAGER->changeScene("StartScene");



	return S_OK;
}

void playGround::release()
{
	Scene::release();
}


void playGround::update()
{
	Scene::update();
	BOXWORLDMANAGER->GetWorld()->Step(timeStep, velocityIterations, positionIterations);

	SCENEMANAGER->GetNowScene()->update();
}

void playGround::render()
{
	draw();
}

void playGround::draw()
{
	SCENEMANAGER->GetNowScene()->render();
}


