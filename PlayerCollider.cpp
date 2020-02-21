#include "stdafx.h"
#include "PlayerCollider.h"
#include "Tile.h"
#include "Player.h"

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
	}
}

void PlayerCollider::CollisionPreSolve(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object;

	if (to->GetTag().compare("Tile") == 0)
	{
		Tile* tile = (Tile*)obj;

		if (tile->GetAttribute() == TAttribute::INTERACTION)
		{
			cout << "come on!" << endl;
		}
	}
}

void PlayerCollider::CollisionEnd(void* obj)
{

}
