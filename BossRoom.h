#pragma once
#include "Scene.h"
#include "Player.h"
#include "Maptool.h"
#include "Tile.h"
#include "Boss.h"
#include "DungeonMgr.h"
#include "Dungeon.h"
#include "UiManager.h"
#define Bossroom_X 70
#define Bossroom_Y 48

class BossRoom : public Scene
{
private:
	Player* _player;
	Boss* _boss;
	UiManager* UI;
	vector<Tile*> _tiles;
	tagTile _tagTiles[Bossroom_X * Bossroom_Y];
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	void SetUP();
	//void SetRoom();
	//void CloseRoom();
	//void GetRoomActive() {}

};

