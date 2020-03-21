#include "stdafx.h"
#include "Astar.h"

Astar::Astar()
{

}


Astar::~Astar()
{
}

void Astar::Init(vector<Tile*>* tiles, int x, int y)
{
	SetTiles(tiles);
	maxX = x;
	maxY = y;
}

void Astar::Release()
{
	_vTotalList->clear();
	delete this;
}

void Astar::SetTiles(vector<Tile*> *tiles)
{
	_vTotalList = tiles;
}

void Astar::InitTotalList()
{
	for (Tile* t : *_vTotalList)
	{
		if (t->GetAttribute() == Attribute::WALL || t->GetAttribute() == Attribute::NPC_NONE)continue;
		t->SetCostF(-1);
		t->SetCostG(0);
		t->SetCostH(0);
		t->SetIsClose(0);
		t->SetIsOpen(0);
		t->SetParentNode(nullptr);
	}
	if (_startTile != nullptr)	_startTile->SetAttribute(Attribute::NONE);
	if (_endTile != nullptr)  _endTile->SetAttribute(Attribute::NONE);
	_startTile = _endTile = nullptr;

	_OpenList.clear();
	_ClosedList.clear();
}


vector <Tile*> Astar::GetDirList(Vector2 idx)
{
	vector<Tile*> dirList;

	vector<Tile*> nodeList;

	if (CanOpenLeft(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1]);



	if (CanOpenRight(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1]);



	if (CanOpenUp(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX]);

	if (CanOpenDown(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX]);

	for (Tile* t : nodeList)
	{

		if (SetCost(t, 10, (*_vTotalList)[((int)idx.x + maxX * (int)idx.y)]))
			dirList.push_back(t);
	}

	nodeList.clear();

	if (CanOpenRight(idx) && CanOpenDown(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1 + maxX]);
	
	
	if (CanOpenLeft(idx) && CanOpenDown(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1 + maxX]);
	
	if (CanOpenRight(idx) && CanOpenUp(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1 - maxX]);
	
	
	if (CanOpenLeft(idx) && CanOpenUp(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1 - maxX]);
	
	for (Tile* t : nodeList)
	{
		if (SetCost(t, 14, (*_vTotalList)[((int)idx.x + maxX * (int)idx.y)]))
			dirList.push_back(t);
	}

	return dirList;
}

vector<Tile*> Astar::GetDirListFor4Way(Vector2 idx)
{
	vector<Tile*> dirList;

	vector<Tile*> nodeList;

	if (CanOpenLeft(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1]);


	if (CanOpenRight(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1]);

	if (CanOpenUp(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX]);

	if (CanOpenDown(idx))
		nodeList.push_back((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX]);

	for (Tile* t : nodeList)
	{

		if (SetCost(t, 10, (*_vTotalList)[((int)idx.x + maxX * (int)idx.y)]))
			dirList.push_back(t);
	}

	return dirList;
}

list<Vector2> Astar::PathFinder(Vector2 start, Vector2 end)
{
	InitTotalList();

	Vector2 startId = start / TILE_WIDTH;

	Vector2 endId = end / TILE_WIDTH;

	startId = startId.Vector2ToPOINT();

	endId = endId.Vector2ToPOINT();

	_startTile = (*_vTotalList)[(int)startId.x + maxX * (int)startId.y];
	_startTile->SetAttribute(Attribute::START);

	_endTile = (*_vTotalList)[(int)endId.x + maxX * (int)endId.y];
	_endTile->SetAttribute(Attribute::END);

	_currentTile = _startTile;
	AddOpenList(_currentTile);
	bool theEnd = false;

	while (!theEnd)
	{
		for (Tile* t : GetDirList(Vector2(_currentTile->GetIdX(), _currentTile->GetIdY())))
		{

			if (t == _endTile)
			{
				theEnd = true;
				AddOpenList(t);
				SetPathcList();

				break;
			}
			else
				AddOpenList(t);
		}
		AddCloseList(_currentTile);
		_currentTile = GetMinFNode();
		if (_currentTile == nullptr) break;
	}

	return _pathList;
}

list<Vector2> Astar::PathFinderFor4Way(Vector2 start, Vector2 end)
{
	InitTotalList();

	Vector2 startId((int)(start.x / TILE_WIDTH), (int)(start.y / TILE_HEIGHT));
	Vector2 endId((int)(end.x / TILE_WIDTH), (int)(end.y / TILE_HEIGHT));


	_startTile = (*_vTotalList)[(int)startId.x + maxX * (int)startId.y];
	_startTile->SetAttribute(Attribute::START);

	_endTile = (*_vTotalList)[(int)endId.x + maxX * (int)endId.y];
	_endTile->SetAttribute(Attribute::END);

	_currentTile = _startTile;
	AddOpenList(_currentTile);
	bool theEnd = false;

	while (!theEnd)
	{
		for (Tile* t : GetDirListFor4Way(Vector2(_currentTile->GetIdX(), _currentTile->GetIdY())))
		{

			if (t == _endTile)
			{
				theEnd = true;
				SetPathcList();
				break;
			}
			else
				AddOpenList(t);
		}
		AddCloseList(_currentTile);
		_currentTile = GetMinFNode();
		if (_currentTile == nullptr) break;
	}

	return _pathList;
}

list<Vector2> Astar::PathFinderForIndex(Vector2 start, Vector2 end)
{

	InitTotalList();

	Vector2 startId((int)(start.x / TILE_WIDTH), (int)(start.y / TILE_HEIGHT));
	Vector2 endId((int)(end.x / TILE_WIDTH), (int)(end.y / TILE_HEIGHT));


	_startTile = (*_vTotalList)[start.x + maxX * start.y];
	_startTile->SetAttribute(Attribute::START);

	_endTile = (*_vTotalList)[end.x + maxX * end.y];
	_endTile->SetAttribute(Attribute::END);

	_currentTile = _startTile;
	AddOpenList(_currentTile);
	bool theEnd = false;

	while (!theEnd)
	{
		for (Tile* t : GetDirList(Vector2(_currentTile->GetIdX(), _currentTile->GetIdY())))
		{

			if (t == _endTile)
			{
				theEnd = true;
				SetPathcList();
				break;
			}
			else
				AddOpenList(t);
		}
		AddCloseList(_currentTile);
		_currentTile = GetMinFNode();
		if (_currentTile == nullptr) break;
	}

	return _pathList;
}

list<Vector2> Astar::PathFinderForIndexFor4Way(Vector2 start, Vector2 end)
{
	InitTotalList();

	Vector2 startId((int)(start.x / TILE_WIDTH), (int)(start.y / TILE_HEIGHT));
	Vector2 endId((int)(end.x / TILE_WIDTH), (int)(end.y / TILE_HEIGHT));


	_startTile = (*_vTotalList)[start.x + maxX * start.y];
	_startTile->SetAttribute(Attribute::START);

	_endTile = (*_vTotalList)[end.x + maxX * end.y];
	_endTile->SetAttribute(Attribute::END);

	_currentTile = _startTile;
	AddOpenList(_currentTile);
	bool theEnd = false;

	while (!theEnd)
	{
		for (Tile* t : GetDirListFor4Way(Vector2(_currentTile->GetIdX(), _currentTile->GetIdY())))
		{

			if (t == _endTile)
			{
				theEnd = true;
				AddOpenList(t);
				SetPathcList();
				break;
			}
			else
				AddOpenList(t);
		}
		AddCloseList(_currentTile);
		_currentTile = GetMinFNode();
		if (_currentTile == nullptr) break;
	}

	return _pathList;
}

bool Astar::CanOpenLeft(Vector2 idx)
{
	if (idx.x - (int)1 <= -1) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1]->GetAttribute() == Attribute ::WALL ||
		(*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1]->GetAttribute() == Attribute ::NPC_NONE  ) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1]->GetIsClose()) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - 1] == nullptr) return false;

	return true;
}

bool Astar::CanOpenRight(Vector2 idx)
{

	if (idx.x + (int)1 >= maxX) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1]->GetAttribute() == Attribute::WALL ||
		(*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1]->GetAttribute() == Attribute::NPC_NONE) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1]->GetIsClose()) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + 1] == nullptr) return false;

	return true;
}

bool Astar::CanOpenUp(Vector2 idx)
{

	if (idx.y - (int)1 <= -1) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX]->GetAttribute() == Attribute::WALL ||
		(*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX]->GetAttribute() == Attribute::NPC_NONE) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX]->GetIsClose()) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) - maxX] == nullptr) return false;

	return true;
}

bool Astar::CanOpenDown(Vector2 idx)
{

	if (idx.y + (int)1 >= maxY) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX]->GetAttribute() == Attribute::WALL ||
		(*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX]->GetAttribute() == Attribute::NPC_NONE) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX]->GetIsClose()) return false;

	if ((*_vTotalList)[((int)idx.x + maxX * (int)idx.y) + maxX] == nullptr) return false;

	return true;
}

bool Astar::SetCost(Tile* node, float cost, Tile* parent)
{
	if (node == nullptr || node->GetAttribute() == Attribute::WALL || node->GetAttribute() == Attribute::NPC_NONE || node->GetIsClose() || node->GetIsOpen()) return false;

	float valH = 0;
	cost += node->GetCostG();
	int x = abs(_endTile->GetIdX() - node->GetIdX());
	int y = abs(_endTile->GetIdY() - node->GetIdY());
	valH = (x + y) * 10;

	if (node->GetCostF() < 0 || node->GetCostG() > cost)
	{
		node->SetCostG(cost);
		node->SetCostH(valH);
		node->SetCostF(cost + valH);
		node->SetParentNode(parent);
	}

	return true;
}

void Astar::AddOpenList(Tile* node)
{
	if (node == nullptr || node->GetAttribute() == Attribute::WALL|| node->GetAttribute() == Attribute::NPC_NONE) return;

	if (node->GetIsClose()) return;
	if (node->GetIsOpen()) return;


	node->SetIsOpen(true);

	_OpenList.push_back(node);
}

void Astar::AddCloseList(Tile* node)
{

	if (node == nullptr) return;
	node->SetIsOpen(false);
	node->SetIsClose(true);

	for (int i = 0; i < _OpenList.size(); i++)
	{
		if (_OpenList[i] == node) {
			_OpenList.erase(_OpenList.begin() + i);
			break;
		}

	}
	_ClosedList.push_back(node);
}

Tile* Astar::GetMinFNode()
{
	float tempTotalCost = FLT_MAX;
	Tile* tempTile = nullptr;

	for (Tile* t : _OpenList)
	{
		if (t->GetCostF() < tempTotalCost)
		{
			tempTotalCost = t->GetCostF();
			tempTile = t;
		}
	}

	return tempTile;
}

void Astar::SetPathcList()
{
	_pathList.clear();
	list<Vector2> path;

	while (_currentTile->GetParentNode() != nullptr)
	{
		_currentTile = _currentTile->GetParentNode();
		path.push_front(_currentTile->GetCenter());
	}
	_pathList = path;
}
