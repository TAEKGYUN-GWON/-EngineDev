#pragma once
#include"Object.h"

#define TILEWIDTH 30
#define TILEHEIGHT 30

#define SET_TILEWIDTH 60
#define SET_TILEHEIGHT 60

//#define TILENUMX (1335 / TILEWIDTH)
//#define TILENUMY (1100 / TILEHEIGHT)

#define TILENUMX 100
#define TILENUMY 100


enum type {


};

class Tile : public Object
{
private:
    int _idX;
    int _idY;

    int _id;

    //F = G + H
    float _f;      //총 비용
    float _g;   //시작위치로부터 현재 노드
    float _h;      //현재 노드로부터 도착점까지 경로비용

    bool _isOpen;
    bool _isClose;

    bool _isFrame;

    Tile* _parent;

    string _attribute;   //타일속성

    string _imgName;   //타일속성
    PIVOT _pivot;
    ColorF::Enum _color;
    RECT _rc;

public:
    Tile() :_f(0), _g(0),
        _h(0), _idX(0), _idY(0)
    {
        _attribute.clear();
    }

    ~Tile() {};

    //virtual void Render() { return; }


    static Vector2 tileSize;


    virtual void Init(int idX, int idY);
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

    void SetRect(RECT rc) { _rc = rc; }
    RECT GetRect() { return _rc; }

    void SetId(int id) { _id = id; }
    int GetId() { return _id; }

    void SetImgName(string name) { _imgName = name; }
    string GetImgName() { return _imgName; }

    void SetIsFrame(bool active) { _isFrame = active; }
    bool GetIsFrame() { return _isFrame; }

    void SetPivot(PIVOT pivot) { _pivot = pivot; }
    PIVOT GetPivot() { return _pivot; }
};
