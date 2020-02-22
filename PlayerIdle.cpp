#include "stdafx.h"
#include "PlayerIdle.h"
#include "Player.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "PlayerLadder.h"
#include "PlayerDead.h"
#include "UndergroundScene.h"

void PlayerIdle::Enter()
{
	_state = "Idle";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Idle");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.0f);
}

void PlayerIdle::Update()
{
	if (KEYMANAGER->isStayKeyDown('D') or KEYMANAGER->isStayKeyDown('A'))
	{
		_obj->ChangeState(make_shared<PlayerMove>(_obj));
		return;
	}

	if (_obj->GetIsLadderCollider())
	{
		_obj->SetLadderDistance(fabs(_obj->GetLadderPosition().x - _obj->GetTrans()->GetPos().x));
		
		if (_obj->GetLadderDistance() <= 10.0f)
		{
			UndergroundScene* scene = (UndergroundScene*)SCENEMANAGER->GetNowScene();

			int nowIndex = ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().x / TILE_WIDTH) + TILE_NUM_X * ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().y / TILE_HEIGHT);

			if (KEYMANAGER->isStayKeyDown('W'))
			{
				if (scene->GetTiles()[nowIndex - TILE_NUM_X]->GetTileObject()->GetAttribute() == TAttribute::LADDER)
				{
					_obj->ChangeState(make_shared<PlayerLadder>(_obj));
					return;
				}
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				if (scene->GetTiles()[nowIndex + TILE_NUM_X]->GetTileObject()->GetAttribute() == TAttribute::LADDER)
				{
					_obj->ChangeState(make_shared<PlayerLadder>(_obj));
					return;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_obj->ChangeState(make_shared<PlayerAttack>(_obj));
		return;
	}

	if (_obj->GetAbility()->IsDead())
	{
		_obj->ChangeState(make_shared<PlayerDead>(_obj));
		return;
	}
	//if (KEYMANAGER->isOnceKeyDown('L'))
	//{
	//	_obj->ChangeState(make_shared<PlayerDead>(_obj));
	//	return;
	//}
}

void PlayerIdle::Exit()
{
}
