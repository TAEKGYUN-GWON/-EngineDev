#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerIdle.h"
#include "UndergroundScene.h"

void PlayerMove::Enter()
{
	_state = "Move";

	_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
	_obj->GetLegs()->GetComponent<Sprite>()->SetFPS(1.5f);

	_speed = 200.0f;
}

void PlayerMove::Update()
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_obj->GetCursorWhere() == CursorWhere::Left)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run_Back");
		}
		else if (_obj->GetCursorWhere() == CursorWhere::Right)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run_Back") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
		}

		_obj->SetDirection(Dir::Right);
		_obj->GetPhysicsBody()->ApplyForce(Vector2::b2Down);
		_obj->GetPhysicsBody()->GetBody()->SetGravityScale(1);
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_obj->GetCursorWhere() == CursorWhere::Left)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run_Back") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run");
		}
		else if (_obj->GetCursorWhere() == CursorWhere::Right)
		{
			if (_obj->GetLegs()->GetComponent<Sprite>()->GetImgKey().compare("Legs_Run") == 0)
				_obj->GetLegs()->GetComponent<Sprite>()->SetImgName("Legs_Run_Back");
		}

		_obj->SetDirection(Dir::Left);
		_obj->GetPhysicsBody()->ApplyForce(Vector2::b2Down);
		_obj->GetPhysicsBody()->GetBody()->SetGravityScale(1);
	}

	if (_obj->GetIsLadderCollider())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (SCENEMANAGER->GetNowScene()->GetName().compare("underground") == 0)
			{
				UndergroundScene* scene = (UndergroundScene*)SCENEMANAGER->GetNowScene();

				int index = ((int)_obj->GetTrans()->GetPos().x / TILE_WIDTH) + TILE_NUM_X * ((int)_obj->GetTrans()->GetPos().y / TILE_HEIGHT);
				int nowIndex = ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().x / TILE_WIDTH) + TILE_NUM_X * ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().y / TILE_HEIGHT);
				int upIndex = nowIndex - TILE_NUM_X;
				int downIndex = nowIndex + TILE_NUM_X;

				if (scene->GetTiles()[downIndex]->GetAttribute() == TAttribute::WALL)
					scene->GetTiles()[downIndex]->GetPhysics()->SetSensor(false);

				if (scene->GetTiles()[upIndex]->GetTileObject()->GetAttribute() == TAttribute::LADDER)
				{
					if (scene->GetTiles()[index - TILE_NUM_X]->GetAttribute() == TAttribute::WALL)
						scene->GetTiles()[index - TILE_NUM_X]->GetPhysics()->SetSensor(true);

					_obj->GetTrans()->pos.x = _obj->GetLadderPosition().x;
					_obj->SetDirection(Dir::Up);
					_obj->GetPhysicsBody()->GetBody()->SetGravityScale(0);
				}
				else _obj->SetIsLadderCollider(false);
			}
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			UndergroundScene* scene = (UndergroundScene*)SCENEMANAGER->GetNowScene();

			// 2020.02.21 TODO : 내려가면서 사다리 끝일 때 바닥 파고 드는 거 좀 더 세세하게 잡자
			int nowIndex = ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().x / TILE_WIDTH) + TILE_NUM_X * ((int)_obj->GetJudgingFloor()->GetTrans()->GetPos().y / TILE_HEIGHT);
			int downIndex = nowIndex + TILE_NUM_X;

			if (scene->GetTiles()[nowIndex]->GetTileObject()->GetAttribute() == TAttribute::LADDER)
			{
				if (scene->GetTiles()[downIndex]->GetTileObject()->GetAttribute() == TAttribute::LADDER &&
					scene->GetTiles()[downIndex]->GetAttribute() == TAttribute::WALL)
				{
					scene->GetTiles()[downIndex]->GetPhysics()->SetSensor(true);
					cout << downIndex << endl;
				}

				_obj->GetTrans()->pos.x = _obj->GetLadderPosition().x;
				_obj->SetDirection(Dir::Down);
				_obj->GetPhysicsBody()->GetBody()->SetGravityScale(0);
			}
			else _obj->SetIsLadderCollider(false);
		}
	}

	_obj->GetTrans()->SetPos(_obj->GetTrans()->GetPos() + Vector2(cosf((int)_obj->GetDirection() * Deg2Rad), -sinf((int)_obj->GetDirection() * Deg2Rad)) * _speed * TIMEMANAGER->getElapsedTime());
	_obj->GetPhysicsBody()->SetBodyPosition();

	if (_obj->GetIsLadderCollider())
	{
		if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D') &&
			!KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
		{
			_obj->ChangeState(make_shared<PlayerIdle>(_obj));
		}
	}
	else
	{
		if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D'))
		{
			_obj->ChangeState(make_shared<PlayerIdle>(_obj));
		}
	}
}

void PlayerMove::Exit()
{
}
