#pragma once
#include"Tile.h"

#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class Astar
{
private:
	vector<Tile*>			_vTotalList;
	vector<Tile*>::iterator _viTotalList;

	vector<Tile*>				_vOpenList;
	vector<Tile*>::iterator		_viOpenList;

	vector<Tile*>				_vClosedList;
	vector<Tile*>::iterator		_viClosedList;

	Tile* _startTile;
	Tile* _endTile;
	Tile* _currentTile;

	//요건 나중에 테스트할때 쓸것.
	bool _start;
	int _count;

public:
	Astar();
	~Astar();

	void Init();
	void SetTiles();
	vector<Tile*> AddOpenList(Tile* currentTile);

	void pathFinder(Tile* currentTile);

	void Release();
	void Update();
	void Render();
};

