#pragma once
#include "Scene.h"
#include "Button.h"

class Train;
class Player;

class TrainScene : public Scene
{
private:
	Player* _player;
	Train* _train;
	Button* _btn;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	static void cbTest(void* obj);
};

