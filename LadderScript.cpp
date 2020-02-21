#include "stdafx.h"
#include "LadderScript.h"
#include "Tile.h"
#include "Player.h"

void LadderScript::CollisionBegin(void* obj)
{
	Object* to = (Object*)obj;
	Player* me = (Player*)_object->GetParent();

	if (to->GetTag().compare("Tile") == 0)
	{
		Tile* tile = (Tile*)obj;

		if (tile->GetAttribute() == TAttribute::LADDER)
		{
			//if (tile->GetTileParent() == -1)
			//{
			//	for (int i = 0; i < tile->GetTileChildren().size(); ++i)
			//	{
			//		cout << tile->GetTileChildren()[i] << endl;
			//	}
			//}

			me->SetIsLadderCollider(true);
			me->SetLadderPosition(to->GetTrans()->GetPos());
		}
	}
}

void LadderScript::CollisionPreSolve(void* obj)
{
}

void LadderScript::CollisionEnd(void* obj)
{
	
}
