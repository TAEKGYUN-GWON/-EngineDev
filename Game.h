#pragma once
#include "Scene.h"
class Game :
	public Scene
{
public:
	Game();
	~Game();
	virtual void Init();
	virtual void Update();
};

