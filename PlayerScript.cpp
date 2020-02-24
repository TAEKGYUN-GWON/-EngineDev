#include "stdafx.h"
#include "PlayerScript.h"
#include "Ability.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"


void PlayerScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;
}

void PlayerScript::CollisionPreSolve(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;
}

void PlayerScript::CollisionEnd(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;
}

