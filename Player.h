#pragma once
#include "Object.h"

class Player : public Object
{
private:
	typedef Object super;
public:
	Player();
	~Player();
	
	virtual void Init(Vector2 pos);
};

