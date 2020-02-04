#include "stdafx.h"
#include "RockCollider.h"
#include "Player.h"
#include "Ability.h"
void RockCollider::CollisionBegin(void* obj)
{

	Object* to = (Object*)obj;
	if (to->GetName() == "Will")
	{
		Player* will = (Player*)to;
		if (!_firstColl) {

			_firstColl = true;
			will->GetAbility()->DamageHP(7);
			cout << will->GetAbility()->GetCurrentHP() << endl;
		}
	}
	
}

void RockCollider::CollisionPreSolve(void* obj)
{
	Object* to = (Object*)obj;
	if (to->GetName() == "Will")
	{
		Player* will = (Player*)to;
		if (!_firstColl) {

			_firstColl = true;
			will->GetAbility()->DamageHP(7);
			cout << will->GetAbility()->GetCurrentHP() << endl;
		}
	}

}

void RockCollider::CollisionEnd(void* obj)
{
	Object* to = (Object*)obj;
	if (to->GetName() == "Will")
	{
		Player* will = (Player*)to;
		if (!_firstColl) {

			_firstColl = true;
			will->GetAbility()->DamageHP(7);
			cout << will->GetAbility()->GetCurrentHP() << endl;
		}
	}
}
