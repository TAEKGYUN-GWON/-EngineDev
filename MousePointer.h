#pragma once
#include "singletonBase.h"
class MousePointer :public singletonBase<MousePointer>
{
private:
	Vector2 pos;
public:

	Vector2 GetMousePosition();
};

