#pragma once
#include "gameNode.h"
class game : public Scene
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

