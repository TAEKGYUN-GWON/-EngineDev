#include "stdafx.h"
#include "BulletScript.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include "Player.h"

void BulletScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Bullet* me = (Bullet*)_object;

	if (me->GetName()=="Ebullet" && to->GetTag() == "Player")
	{
		Player* player = (Player*)obj;

		if (player->GetPhysics()->GetBody()->GetFixtureList()->IsSensor())return;
		player->GetAbility()->DamageHP(me->GetAttackPoint());
		me->SetCollision(true);
	}
	else if(me->GetName() == "Arrow" && to->GetTag() == "enemy")
	{
		Enemy* enemy = (Enemy*)obj;

		enemy->GetHP()->DamageHP(me->GetAttackPoint());
		me->SetCollision(true);
	}
}

void BulletScript::CollisionPreSolve(void* obj)
{
}

void BulletScript::CollisionEnd(void* obj)
{
}
