#pragma once
#include"Object.h"

#define TILEWIDTH 30
#define TILEHEIGHT 30

class Tile : public Object
{
private:
	int _idX;
	int _idY;

	Vector2 _center;

	//F = G + H
	float _totalCost;		//�� ���
	float _costFromStart;	//������ġ�κ��� ���� ���
	float _costToGoal;		//���� ���κ��� ���������� ��κ��

	bool _isOpen;

	Tile* _parent;

	string _attribute;	//Ÿ�ϼӼ�

	ColorF::Enum _color;

public:
	Tile() :_totalCost(0), _costFromStart(0),
		_costToGoal(0), _idX(0), _idY(0) {}
	~Tile() {};

	static Vector2 tileSize;


	virtual void Init(int idX, int idY);
	virtual void Release();
	virtual void SetParentNode(Tile* p) { _parent = p; }
	virtual Tile* GetParentNode() { return _parent; }

	int GetIdX() { return _idX; }
	int GetIdY() { return _idY; }

	void SetCenter(Vector2 center) { _center = center; }
	Vector2 GetCenter() { return _center; }

	void SetAttribute(string str) { _attribute = str; }
	string GetAttribute() { return _attribute; }

	void SetTotalCost(float totalCost) { _totalCost = totalCost; }
	float GetTotalCost() { return _totalCost; }

	void SetCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float GetCostFromStart() { return _costFromStart; }

	void SetCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float GetCostToGoal() { return _costToGoal; }

	void SetIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool GetIsOpen() { return _isOpen; }

	void SetColor(ColorF::Enum color) { _color = color; }
	void SetFrameXY(int x, int y);
};
