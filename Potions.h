#pragma once

#include "Potion.h"

class Potion_L : public Potion
{

	typedef Potion super;

public:

	virtual void Init(Vector2 pos);

};

class Potion_S :public Potion
{
	typedef Potion super;

public:

	virtual void Init(Vector2 pos);
};





