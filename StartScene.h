#pragma once
#include "Scene.h"
#include "Player.h"
class StartScene : public Scene
{
private:
	Object* _player;
	Player*_player2;
public:
	virtual void Init();

	virtual void Render();
};

