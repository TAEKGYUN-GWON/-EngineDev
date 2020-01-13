#pragma once
#define TILEWIDTH 32
#define TILEHEIGHT 32
class Tile
{
private:
	int _idX;
	int _idY;

	Vector2 _center;

	//F = G + H
	float _totalCost;		//총 비용
	float _costFromStart;	//시작위치로부터 현재 노드
	float _costToGoal;		//현재 노드로부터 도착점까지 경로비용

	bool _isOpen;

	Tile* _parent;

	string _attribute;	//타일속성

	Brush_type::Enum _color;

public:
	Tile() :_totalCost(0), _costFromStart(0),
		_costToGoal(0), _idX(0), _idY(0) {}
	~Tile() {};

	static Vector2 tileSize;


	virtual void Init(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render();
	virtual void SetParent(Tile* p) { _parent = p; }
	virtual Tile* GetParent() { return _parent; }

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

	void SetColor(Brush_type::Enum color) { _color = color; }

};

