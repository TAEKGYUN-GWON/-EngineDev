#include "stdafx.h"
#include "EnemyManager.h"
#include "Knight.h"
#include "Sorcerer.h"
#include "Rogue.h"
#include "ProceduralTest.h"
#include "Room.h"
void EnemyManager::Init(Room* owner)
{
	_owner = owner;
	SetEnemys();
	
	if (!_ast)
	{
		_ast = new Astar;
		ProceduralTest* scene = (ProceduralTest*) SCENEMANAGER->GetNowScene();
		_ast->Init(scene->GetTiles(), MAP_TILE_MAX_X, MAP_TILE_MAX_Y);
	}

}

void EnemyManager::Update()
{
	for (Enemy* e : _vEnemys)
	{
		e->SetPath(_ast->PathFinder(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));
		e->SetAngle(Vector2::GetAngle(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));
		e->SetDistance(Vector2::Distance(e->GetTrans()->GetPos(), SCENEMANAGER->GetNowScene()->GetChildFromName("Player")->GetTrans()->GetPos()));
	}
}

void EnemyManager::Release()
{
	for (Enemy* e : _vEnemys)
		e->SetIsRelese();

	_vEnemys.clear();

	_ast->Release();

	delete _ast;
}

void EnemyManager::SetEnemys()
{
	int some = RND->getFromIntTo(3, 7);
	for (int i = 0; i < some; i++)
	{
		int type = RND->getInt(3);

		switch (type)
		{
		case 0:
		{
			Knight* enemy = Object::CreateObject<Knight>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));
			
			enemy->Init(pos);
			_vEnemys.push_back(enemy);
		}
		break;

		case 1:
		{
			//Sorcerer
			Sorcerer* enemy = Object::CreateObject<Sorcerer>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));

			enemy->Init(pos);
			_vEnemys.push_back(enemy);
		}
		break;


		case 2:
		{
			//Rogue
			Rogue* enemy = Object::CreateObject<Rogue>();
			Vector2 pos = Vector2::RandPosition(_owner->GetTrans()->GetPosToPivot(TF_PIVOT::LEFT_TOP) + Vector2(TILE_WIDTH * 2, TILE_HEIGHT),
				_owner->GetTrans()->GetPosToPivot(TF_PIVOT::RIGHT_BOTTOM) - Vector2(TILE_WIDTH, TILE_HEIGHT));

			enemy->Init(pos);
			_vEnemys.push_back(enemy);
		}
		break;

		}
	}

}
