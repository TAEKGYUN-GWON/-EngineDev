#pragma once
#include "Scene.h"

class StartScene : public Scene
{
private:
	shared_ptr<Graphic> _cursorImg;
	shared_ptr<Graphic> _logoImg;
	shared_ptr<Graphic> _eagleImg;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

