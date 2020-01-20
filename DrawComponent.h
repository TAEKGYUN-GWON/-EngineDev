#pragma once
#include "Component.h"

class Transform;

class DrawComponent : public Component
{
protected:
	Transform* _trans;
	bool _isCameraAffect = false;

public:
	DrawComponent();
	~DrawComponent();
	virtual void Render() = 0;
	Transform* GetTransform() { return _trans; }
};

