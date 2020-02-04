#include "stdafx.h"
#include "PlayerAttackScript.h"
#include "Player.h"
#include "GolemEnemy.h"
#include "MintPotEnemy.h"
#include "SlimeEnemy.h"
#include "Boss.h"
void PlayerAttackScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object->GetParent();

	if (to->GetTag() == "enemy")
	{
		if (to->GetName() == "Golem")
		{
			GolemEnemy* golem = (GolemEnemy*)obj;
			if (golem->GetPhysics()->GetBody()->GetFixtureList()->IsSensor()) return;
			golem->GetHP()->DamageHP(me->GetAbility()->GetAttackPoint());
		}
		else if (to->GetName() == "Slime")
		{
			SlimeEnemy* slime = (SlimeEnemy*)obj;
			if (slime->GetPhysics()->GetBody()->GetFixtureList()->IsSensor()) return;
			slime->GetHP()->DamageHP(me->GetAbility()->GetAttackPoint());
		}
		else if (to->GetName() == "Pot")
		{
			MintPotEnemy* pot = (MintPotEnemy*)obj;
			if (pot->GetPhysics()->GetBody()->GetFixtureList()->IsSensor()) return;
			pot->GetHP()->DamageHP(me->GetAbility()->GetAttackPoint());
		}
	}
	else if (to->GetTag() == "boss")
	{
		Boss* boss = (Boss*)to;
		boss->GetHP()->DamageHP(me->GetAbility()->GetAttackPoint());
	}
}

void PlayerAttackScript::CollisionPreSolve(void* obj)
{
}

void PlayerAttackScript::CollisionEnd(void* obj)
{
}
