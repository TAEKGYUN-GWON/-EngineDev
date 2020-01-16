#include "stdafx.h"
#include "Astar.h"

Astar::Astar()
{
}


Astar::~Astar()
{
}

void Astar::Init()
{
	_mTotalList.clear();
	SetTiles();

}

void Astar::SetTiles()
{
	//시작 타일


	//전체 타일 돌아서
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_mTotalList[Vector2(j, i)] = new Tile;
			_mTotalList[Vector2(j, i)]->Init(j, i);
		}
	}
	int a;
}

void Astar::InitTotalList()
{
	for (auto it = _mTotalList.begin(); it != _mTotalList.end(); it++)
	{
		(*it).second->SetCostF(-1);
		(*it).second->SetCostG(0);
		(*it).second->SetCostH(0);
		(*it).second->SetIsClose(0);
		(*it).second->SetIsOpen(0);
		(*it).second->SetParentNode(nullptr);

	}

	_OpenList.clear();
	_ClosedList.clear();
}


vector <Tile*> Astar::GetDirList(Vector2 idx)
{
	vector<Tile*> dirList;
	vector<Tile*> nodeList;

	_miTotalList = _mTotalList.find(Vector2(idx.x - (int)1, idx.y));
	if (CanOpenLeft(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x + (int)1, idx.y));
	if (CanOpenRight(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x, idx.y- (int)1));
	if (CanOpenUp(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x, idx.y+ (int)1));
	if (CanOpenDown(idx))
		nodeList.push_back(_miTotalList->second);

	for (Tile* t : nodeList)
	{
		_miTotalList = _mTotalList.find(Vector2(idx.x, idx.y));
		if (SetCost(t, 10, _miTotalList->second))
			dirList.push_back(t);
	}

	nodeList.clear();


	_miTotalList = _mTotalList.find(Vector2(idx.x+ (int)1, idx.y + (int)1));
	if (CanOpenRight(idx) && CanOpenDown(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x - (int)1, idx.y + (int)1));
	if (CanOpenLeft(idx) && CanOpenDown(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x + (int)1, idx.y - (int)1));
	if (CanOpenRight(idx) && CanOpenUp(idx))
		nodeList.push_back(_miTotalList->second);


	_miTotalList = _mTotalList.find(Vector2(idx.x - (int)1, idx.y - (int)1));
	if (CanOpenLeft(idx) && CanOpenUp(idx))
		nodeList.push_back(_miTotalList->second);

	for (Tile* t : nodeList)
	{
		_miTotalList = _mTotalList.find(Vector2(idx.x, idx.y));
		if (SetCost(t, 14, _miTotalList->second))
			dirList.push_back(t);
	}

	return dirList;
}

list<Vector2> Astar::pathFinder(Vector2 start, Vector2 end)
{

	Vector2 startId((int)(start.x / TILEWIDTH),	(int)(start.y / TILEHEIGHT));
	Vector2 endId((int)(end.x / TILEWIDTH),	(int)(end.y / TILEHEIGHT));

	_miTotalList = _mTotalList.find(startId);
	_startTile = _miTotalList->second;
	_startTile->SetAttribute("start");

	_miTotalList = _mTotalList.find(endId);
	_endTile = _miTotalList->second;
	_endTile->SetAttribute("end");
	_currentTile = _startTile;
	AddOpenList(_currentTile);
	while (true)
	{
		for (Tile* t : GetDirList(Vector2(_currentTile->GetIdX(), _currentTile->GetIdY())))
		{

			if (t == _endTile)
			{
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

void Astar::Release()
{
}

void Astar::Update()
{
	
	
}

void Astar::Render()
{
	
	for (_miTotalList = _mTotalList.begin(); _miTotalList!= _mTotalList.end(); ++_miTotalList)
	{
		_miTotalList->second->Render();
	}
}

bool Astar::CanOpenLeft(Vector2 idx)
{
	_miTotalList = _mTotalList.find(Vector2(idx.x - (int)1, idx.y));
	if (_miTotalList->second == nullptr) return false;
	if (idx.x - (int)1 < 0) return false;
	return true;
}

bool Astar::CanOpenRight(Vector2 idx)
{
	_miTotalList = _mTotalList.find(Vector2(idx.x + (int)1, idx.y));
	if (_miTotalList->second == nullptr) return false;
	if (idx.x - (int)1 < 0) return false;
	return true;
}

bool Astar::CanOpenUp(Vector2 idx)
{
	_miTotalList = _mTotalList.find(Vector2(idx.x, idx.y- (int)1));

	if (_miTotalList->second == nullptr) return false;
	if (idx.x - (int)1 < 0) return false;
	return true;
}

bool Astar::CanOpenDown(Vector2 idx)
{
	_miTotalList = _mTotalList.find(Vector2(idx.x , idx.y+ (int)1));

	if (_miTotalList->second == nullptr) return false;
	if (idx.x - (int)1 < 0) return false;
	return true;
}

bool Astar::SetCost(Tile* node, float cost, Tile* parent)
{
	if (node == nullptr || node->GetAttribute() == "wall" || node->GetIsClose() || node->GetIsOpen()) return false;

	float valH = 0;
	cost += node->GetCostG();
	int x = abs(_endTile->GetIdX() - node->GetIdX());
	int y = abs(_endTile->GetIdY() - node->GetIdY());
	valH = (x + y) * 10;

	if (node->GetCostF() < 0 || node->GetCostG() > cost)
	{
		node->SetCostG(cost);
		node->SetCostH (valH);
		node->SetCostF(cost + valH);
		node->SetParent (parent);
	}

	return true;
}

void Astar::AddOpenList(Tile * node)
{
	if (node == nullptr || node->GetAttribute() == "wall") return;

	if (node->GetIsClose()) return;
	if (node->GetIsOpen()) return;


	node->SetIsOpen(true);

	_OpenList.push_back(node);

}

void Astar::AddCloseList(Tile * node)
{

	if (node == NULL) return;
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

Tile * Astar::GetMinFNode()
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

	while (_currentTile->GetParent() != NULL)
	{
		_currentTile = _currentTile->GetParentNode();
		_pathList.push_front(_currentTile->GetCenter());
	}
}
