#pragma once
#include "Object.h"

class Enemy1 : public Object
{
private:
	typedef Object super;

public:
	list<Vector2> path;
	virtual void Init(Vector2 pos);
	virtual void Update();

	void SetPath(list<Vector2> path);
};

