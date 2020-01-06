#pragma once
#include "Object.h"

class PhysicsBody;

class D2DEffect : public Object
{
private:
	typedef Object super;

	PhysicsBody* _physics;

public:
	void Init(Vector2 pos);
	virtual void Release() override;
	virtual void Update() override;
};

