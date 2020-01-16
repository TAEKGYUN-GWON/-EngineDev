#pragma once
#include"Object.h"

#define TILENUMX (1335 / TILEWIDTH)
#define TILENUMY (1100 / TILEHEIGHT)

#define TILEWIDTH 30
#define TILEHEIGHT 30

class Tile : public Object
{
private:
	int _idX;
	int _idY;

	//F = G + H
	float _f;		//총 비용
	float _g;	//시작위치로부터 현재 노드
	float _h;		//현재 노드로부터 도착점까지 경로비용

	bool _isOpen;
	bool _isClose;

	Tile* _parent;

	string _attribute;	//타일속성

	ColorF::Enum _color;

public:
	Tile() :_f(0), _g(0),
		_h(0), _idX(0), _idY(0) 
	{
		_attribute.clear();
	}

	~Tile() {};

	static Vector2 tileSize;


	virtual void Init(int idX, int idY);
	virtual void Release();
	void SetParentNode(Tile* p) { _parent = p; }
	Tile* GetParentNode() { return _parent; }

	int GetIdX() { return _idX; }
	int GetIdY() { return _idY; }

	void SetCenter(Vector2 center) { _trans->pos = center; }
	Vector2 GetCenter() { return _trans->pos; }

	void SetAttribute(string str) { _attribute = str; }
	string GetAttribute() { return _attribute; }

	void SetCostF(float totalCost) { _f = totalCost; }
	float GetCostF() { return _f; }

	void SetCostG(float costFromStart) { _g = costFromStart; }
	float GetCostG() { return _g; }

	void SetCostH(float costToGoal) { _h = costToGoal; }
	float GetCostH() { return _h; }

	void SetIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool GetIsOpen() { return _isOpen; }
	
	void SetIsClose(bool isClose) { _isClose = isClose; }
	bool GetIsClose() { return _isClose; }

	void SetColor(ColorF::Enum color) { _color = color; }
	void SetFrameXY(int x, int y);
};

