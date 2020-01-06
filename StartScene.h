#pragma once
#include "gameNode.h"
#include "Player.h"
class StartScene : public gameNode
{
private:
	Player* _player;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

