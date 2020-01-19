#pragma once
#include"Tile.h"
#define TILENUMX (1335 / TILEWIDTH)
#define TILENUMY (1100 / TILEHEIGHT)
//ㅇ
class Astar
{
private:

	enum dir
	{
		Left = -1,
		Right = 1,
		Up = -1,
		Down = 1,

	};
	vector<Tile*>_vTotalList;
	vector<Tile*>::iterator _viTotalList;


	vector <Tile*> _OpenList;
	vector <Tile*>::iterator _iOpenList;

	vector <Tile*> _ClosedList;
	vector <Tile*>::iterator _iClosedList;


	list<Vector2> _pathList;
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

	void InitTotalList();

	vector <Tile*> GetDirList(Vector2 idx);

	list<Vector2> pathFinder(Vector2 start, Vector2 end);

	void Release();
	void Update();
	void Render();

	bool CanOpenLeft(Vector2 idx);
	bool CanOpenRight(Vector2 idx);
	bool CanOpenUp(Vector2 idx);
	bool CanOpenDown(Vector2 idx);

	bool SetCost(Tile* node, float cost, Tile* parent );

	void AddOpenList(Tile* node);
	void AddCloseList(Tile* node);

	Tile* GetMinFNode();

	void SetPathcList();

};

