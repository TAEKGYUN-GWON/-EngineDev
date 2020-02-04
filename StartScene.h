#pragma once
#include "Scene.h"
#include "Inventory.h"
#include "Smithy.h"
#include "UiManager.h"

class StartScene : public Scene
{
private:
	//UiObject* test;
	UiManager* ui;
	Inventory* inven;
	Smithy* _smithy;

	Object* obj;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

