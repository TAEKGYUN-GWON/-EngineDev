#include "stdafx.h"
#include "AttackCollider.h"
#include "Player.h"
#include "EnemyNormal.h"
#include "EnemyState.h"

void AttackCollider::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object->GetParent();

	if (to->GetTag().compare("Enemy") == 0)
	{
		Enemy* e = (Enemy*)obj;
		e->ChangeState(make_shared<EnemyDamage>(e));
	}
}

void AttackCollider::CollisionPreSolve(void* obj)
{
}

void AttackCollider::CollisionEnd(void* obj)
{
}
