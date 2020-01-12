#include "stdafx.h"
#include "Scene.h"
#include "PhysicsBody.h"
#include "Transform.h"
float32 timeStep;
int32 velocityIterations;
int32 positionIterations;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	_b2World = new b2World(b2Vec2(0,0));
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;
	PHYSICSMANAGER->SetWorld(_b2World);
	_b2World->SetContactListener(PHYSICSMANAGER);
	_b2World->SetAllowSleeping(true);
	_b2World->SetContinuousPhysics(true);
}


void Scene::Release()
{
	if (SCENEMANAGER->GetNowScene() == this)
	{
		_allowRelease = true;
		return;
	}
	Object::Release();
}

void Scene::Update()
{
	for (int i = 0; i < _children.size(); i++)
	{
		if (_children[i]->GetAllowInit()) _children[i]->Init();
		_children[i]->Update();
	}

}

void Scene::PhysicsUpdate()
{
	_b2World->Step(timeStep, velocityIterations, positionIterations);
	for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext())
	{
		if (!body->GetUserData())
		{
			b2Body* deletedObject = body;
			body = body->GetNext();
			_b2World->DestroyBody(deletedObject);
			continue;
		}

		Transform* now = ((Object*)body->GetUserData())->GetTrans();
		PhysicsBody* nowP = ((Object*)body->GetUserData())->GetComponent<PhysicsBody>();
		now->SetPos(nowP->GetBodyPosition());
	}
}

void Scene::Render()
{
	if (_allowRelease) return;
	for (Object* child : _children)
		child->Render();
}

