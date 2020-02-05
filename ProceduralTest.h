#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Room.h"
class ProceduralTest : public Scene
{
private:
	vector<Tile*> tiles;
	vector<Room*> Rooms;
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
};

