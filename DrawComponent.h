#pragma once
#include "Component.h"
class Transform;

class DrawComponent :
	public Component
{
protected:
	Transform* _trans;
public:
	DrawComponent();
	~DrawComponent();
	virtual void Render() = 0;
};
