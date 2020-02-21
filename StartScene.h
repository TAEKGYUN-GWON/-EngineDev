#pragma once
#include "Scene.h"
#include "ProgressBar.h"
class StartScene : public Scene
{
private:
	Object* _obj;
	ProgressBar* _bar;
	float current, max;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();



};

