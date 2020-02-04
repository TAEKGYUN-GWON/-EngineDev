#pragma once
#include "Scene.h"
#include "Player.h"
#include "Maptool.h"

class EntranceScene : public Scene
{
private:
	vector<Tile*> tiles;
	tagTile _tagTiles[TILENUMX * TILENUMY];
	
	Player* _player;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	void SetUp();
};

