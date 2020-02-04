#pragma once
#include "Dungeon.h"
#include "BossRoom.h"
#include "Player.h"
class DungeonMgr
{
private:
	vector<Dungeon*> _rooms;
	//BossRoom* _Broom;
	Player* _player;

	int _count = 0;
public:
	void Init(Player* player);
	void Update();
	void Render();
	vector<Dungeon*> GetRoom() { return _rooms; }
};

