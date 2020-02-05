#pragma once
#include "Scene.h"

class StartScene : public Scene
{
private:
	
	Object* _obj;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

