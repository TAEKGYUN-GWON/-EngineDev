#pragma once
#include "Collider.h"
class ItemScript :	public Collider
{
public:

	//충돌한 직후
	virtual void CollisionBegin(void* obj);
	virtual void CollisionPreSolve(void* obj);
};

