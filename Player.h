#pragma once
#include "Object.h"

class Player : public Object
{
private:
	Sprite* _sprite;

	Object* _body;
	Object* _legs;
	Object* _arms;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

