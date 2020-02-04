#pragma once
#include "Collider.h"

class BulletScript : public Collider
{
public:
	//충돌한 직후
	virtual void CollisionBegin(void* obj);
	//충돌중
	virtual void CollisionPreSolve(void* obj);
	//충돌 끝난 시점
	virtual void CollisionEnd(void* obj);
};

