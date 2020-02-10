#pragma once
#include "Component.h"

class Transform;

class DrawComponent : public Component
{
protected:
	Transform* _trans;
	bool _isCameraEffect = true;
	int _depth;

public:
	DrawComponent();
	~DrawComponent();
	virtual void Render() = 0;
	Transform* GetTransform() { return _trans; }

	void SetCameraEffected(bool isEffect) { _isCameraEffect = isEffect; }
	bool GetCameraEffected() { return _isCameraEffect; }
};

