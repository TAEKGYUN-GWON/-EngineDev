#include "stdafx.h"
#include "PlayerCollider.h"
#include "Tile.h"
#include "Player.h"
#include "EnemyNormal.h"

void PlayerCollider::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;

	if (to->GetTag().compare("Tile") == 0)
	{
		Tile* tile = (Tile*)obj;

		if (tile->GetAttribute() == TAttribute::INTERACTION)
		{
			cout << tile->GetImgName() << endl;
		}
		/*if (tile->GetImgName().compare("Wall_RB") == 0)
		{
			me->GetLegs()->GetTrans()->SetRotateToRadian(7 * PI / 4);
			me->GetBody()->GetTrans()->SetRotateToRadian(7 * PI / 4);
		}*/


		//if (tile->GetImgName().compare("Wall_RB") == 0)
		//{
		//	me->GetPhysicsBody()->GetBody()->SetGravityScale(100);
		//	me->GetPhysicsBody()->GetBody()->SetAwake(false);
		//	cout << me->GetPhysicsBody()->GetBody()->GetGravityScale() << endl;
		//}
		//if (tile->GetImgName().compare("Wall_LB") == 0)
		//{
		//	//me->GetPhysicsBody()->GetBody()->SetGravityScale(100);
		//}
	}
	if (to->GetTag().compare("Enemy") == 0)
	{
		EnemyNormal* e = (EnemyNormal*)obj;
	}
}

void PlayerCollider::CollisionPreSolve(void* obj)
{
}

void PlayerCollider::CollisionEnd(void* obj)
{

}
