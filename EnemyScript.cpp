#include "stdafx.h"
#include "EnemyScript.h"
#include "Enemy.h"
#include "Player.h"
#include "Ability.h"

void EnemyScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Enemy* me = (Enemy*)_object;

	if (me->GetName() != "Golem" && to->GetTag() == "Player")
	{
		Player* player = (Player*)obj;
		if (player->GetPhysics()->GetBody()->GetFixtureList()->IsSensor())return;
		player->GetAbility()->DamageHP(me->GetHP()->GetAttackPoint());
	}
}

void EnemyScript::CollisionPreSolve(void* obj)
{

}

void EnemyScript::CollisionEnd(void* obj)
{
}
