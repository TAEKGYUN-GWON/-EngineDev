#pragma once
#include "Collider.h"

class PlayerAttackScript : public Collider
{
	virtual void CollisionBegin(void* obj);
	virtual void CollisionPreSolve(void* obj);
	virtual void CollisionEnd(void* obj);
};
