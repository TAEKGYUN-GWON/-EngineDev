#pragma once
#include "Scene.h"
#include "Player.h"
class StartScene : public Scene
{
private:
	Player* _player;
	Player*_player2;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

