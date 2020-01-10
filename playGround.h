#pragma once
#include "Scene.h"
#include "Player.h"

class playGround : public Scene
{
private:
	Player* _player;
	Player* _player2;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void draw();

};

