#include "stdafx.h"
#include "GolemScript.h"
#include "GolemEnemy.h"
#include "Ability.h"

void GolemScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;

	GolemEnemy* Golem = (GolemEnemy* )_object->GetParent();

	if (to->GetTag() == "Player")
	{
		Player* player = (Player*)obj;
		if (player->GetPhysics()->GetBody()->GetFixtureList()->IsSensor())return;
		player->GetAbility()->DamageHP(Golem->GetHP()->GetAttackPoint());
	}
}

void GolemScript::CollisionPreSolve(void* obj)
{
}

void GolemScript::CollisionEnd(void* obj)
{
}
