#pragma once
#include "singletonBase.h"
class MousePointer :public singletonBase<MousePointer>
{
private:
	Vector2 _pos;
public:

	Vector2 GetMouseWorldPosition();
	Vector2 GetResolution();
	Vector2 GetMouseLocalPosition();
};

