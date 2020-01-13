#include "stdafx.h"
#include "Astar.h"
#include"Transform.h"

Astar::Astar()
{
}


Astar::~Astar()
{
}

void Astar::Init()
{
	SetTiles();

	_start = _count = 0;
}

void Astar::SetTiles()
{
	//���� Ÿ��
	_startTile = new Tile;

	_startTile->Init(4, 12);
	_startTile->SetAttribute("start");

	_endTile = new Tile;
	_endTile->Init(22, 2);
	_endTile->SetAttribute("end");

	_currentTile = _startTile;

	//��ü Ÿ�� ���Ƽ�
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			//����Ÿ���� �ε����� ���� Ÿ���̸� == ����Ÿ��
			if (j == _startTile->GetIdX() && i == _startTile->GetIdY())
			{
				_startTile->SetColor(Brush_type::AQUAMARINE);
				_vTotalList.push_back(_startTile);
				continue;
			}

			//����Ÿ���� �ε����� ���� Ÿ���̸� == ����Ÿ��
			if (j == _endTile->GetIdX() && i == _endTile->GetIdY())
			{
				_endTile->SetColor(Brush_type::MAGENTA);
				_vTotalList.push_back(_endTile);
				continue;
			}

			Tile* node = new Tile;
			node->Init(j, i);
			node->SetIsOpen(true);

			_vTotalList.push_back(node);
		}
	}
}

vector<Tile*> Astar::AddOpenList(Tile * currentTile)
{
	int startX = currentTile->GetIdX() - 1;
	int startY = currentTile->GetIdY() - 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Tile* Node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			if (!Node->GetIsOpen()) continue;
			if (Node->GetAttribute() == "start") continue;
			if (Node->GetAttribute() == "wall") continue;

			//���� Ÿ�Ϸ� ��� ����
			Node->SetParent(_currentTile);

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == Node)
				{
					addObj = false;
					break;
				}
			}

			if (Node->GetAttribute() != "end") Node->SetColor(Brush_type::GREEN);
			if (!addObj) continue;

			_vOpenList.push_back(Node);
		}
	}
	return _vOpenList;
}

void Astar::pathFinder(Tile * currentTile)
{

	//������ ��κ�밪 ����
	float tempTotalCost = 5000;
	Tile* tempTile = NULL;

	//���� ���� ���� �̾ƺ��ô� ���? �� �� �ִ� Ÿ�� �߿���
	for (int i = 0; i < AddOpenList(currentTile).size(); ++i)
	{
		//F = G + H
		_vOpenList[i]->SetCostToGoal(
			(abs(_endTile->GetIdX() - _vOpenList[i]->GetIdX()) +
				abs(_endTile->GetIdY() - _vOpenList[i]->GetIdY())) * 10);

		Vector2 center1 = _vOpenList[i]->GetParent()->GetCenter();
		Vector2 center2 = _vOpenList[i]->GetCenter();

		_vOpenList[i]->SetCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH ? 14 : 10);

		_vOpenList[i]->SetTotalCost(_vOpenList[i]->GetCostToGoal() +
			_vOpenList[i]->GetCostFromStart());

		if (tempTotalCost > _vOpenList[i]->GetTotalCost())
		{
			tempTotalCost = _vOpenList[i]->GetTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;

		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}


		_vOpenList[i]->SetIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}

	if (tempTile->GetAttribute() == "end")
	{
		while (_currentTile->GetParent() != NULL)
		{
			_currentTile->SetColor(Brush_type::RED);
			_currentTile = _currentTile->GetParent();
		}

		return;
	}

	_vClosedList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//����Լ� ȣ��
	//���� �Լ����ο��� �� �Լ��� �� ȣ���ϴ� ���� ����
	//���� : �ڵ尡 �ص��� ª����
	//���� : �� �� ȣ���Ҷ����� �ҷ��� �޸𸮰� ���̴µ� 1.2�ް��� �ѱ�� ����
	//�������� Stack overFlow��� ��

	//�ٵ� ȸ�翡 ���µ� ����� ������ ������ ���� 

	//pathFinder(_currentTile);

}

void Astar::Release()
{
}

void Astar::Update()
{
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_start = true;
	}

	if (_start)
	{
		_count++;

			pathFinder(_currentTile);
			_count = 0;
	}

	

}

void Astar::Render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->Render();
	}
}
