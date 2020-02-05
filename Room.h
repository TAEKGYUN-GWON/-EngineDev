#pragma once
#include "Object.h"
class Room : public Object
{
private:
	PhysicsBody* _physics;

public:

	virtual void Init();

	PhysicsBody* GetPhysics() { return _physics; }
};

