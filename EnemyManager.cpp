#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyNormal.h"

void EnemyManager::Init()
{
}

void EnemyManager::Release()
{
	for (Enemy* e : _vEnemy)
	{
		SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(e->GetComponent<PhysicsBody>()->GetBody());

		e->Release();
	}
	_vEnemy.clear();
}

void EnemyManager::Update()
{
	for (Enemy* e : _vEnemy)
	{
		if (e->GetIsActive() == false)
		{
			e->SetIsRelese();
			_vEnemy.remove(e);
			break;
		}
	}
}

void EnemyManager::Render()
{
}

void EnemyManager::SetEnemy(Vector2 pos)
{
	Enemy* e = Object::CreateObject<EnemyNormal>();
	e->Init();
	//e->GetTrans()->SetPos(WINSIZEX / 2 - 300, 330);
	e->GetTrans()->SetPos(pos);
	e->GetPhysics()->SetBodyPosition();
	_vEnemy.push_back(e);
}
