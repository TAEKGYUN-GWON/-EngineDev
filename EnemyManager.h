#pragma once
#include "Enemy.h"
#include "Astar.h"

class Room;
class EnemyManager
{
private:
	vector<Enemy*> _vEnemys;
	Room* _owner;
	Astar* _ast;
	bool _isActive;
public:
	void Init(Room* owner);
	void Update();
	void Release();
	void SetIsActive(bool active) { _isActive = active; }
	bool GetIsActive() { return _isActive; }
	void SetEnemys();

};

