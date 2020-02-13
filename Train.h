#pragma once
#include "Object.h"

class Train : public Object
{
private:
	vector<Vector2> _vChair;
	Sprite* _sprite;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	Sprite* GetSprite() { return _sprite; }
};

