#pragma once
#include "Collider.h"
class RockCollider : public Collider
{
private:
	bool _firstColl;

public:
	virtual void CollisionBegin(void* obj);
	virtual void CollisionPreSolve(void* obj);
	virtual void CollisionEnd(void* obj);
	void SetColl(bool active) {	_firstColl = active	; }
};

