#pragma once
#include"Object.h"

#define TILE_WIDTH 30
#define TILE_HEIGHT 30

#define TILE_NUM_X 100
#define TILE_NUM_Y 100

enum Attribute
{
    START,
    END,
    NONE_MOVE,
    WALL,
    NPC_NONE,
    DESTRUCTION,
    CLIFF,
    TERRAIN_DESTRUCTION,
    NONE,
};



class Tile : public Object
{
private:
    int _idX;
    int _idY;

    int _id;

    //F = G + H
    float _f;      //�� ���
    float _g;   //������ġ�κ��� ���� ���
    float _h;      //���� ���κ��� ���������� ��κ��

    bool _isOpen;

    bool _isClose;

    bool _isFrame;

    Tile* _node;

    Attribute _attribute;   //Ÿ�ϼӼ�

    string _imgName;   //Ÿ�ϼӼ�

    PIVOT _pivot;

    PhysicsBody* _physics;

    Sprite* _sprite;
public:
    Tile() :_f(0), _g(0),
        _h(0), _idX(0), _idY(0) { }

    ~Tile() {};
    virtual void Init(int idX, int idY);
    virtual void Update() { return; }
    
    virtual void Render();


    static Vector2 tileSize;


    void SetParentNode(Tile* p) { _node = p; }
    Tile* GetParentNode() { return _node; }

    int GetIdX() { return _idX; }
    int GetIdY() { return _idY; }

    void SetCenter(Vector2 center) { _trans->SetPos(center); }
    Vector2 GetCenter() { return _trans->GetPos(); }

    void SetAttribute(Attribute str) { _attribute = str; }
    Attribute GetAttribute() { return _attribute; }

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

    void SetPhysics();


    void SetId(int id) { _id = id; }
    int GetId() { return _id; }

    void SetImgName(string name);
    string GetImgName() { return _imgName; }

    void SetIsFrame(bool active) { _isFrame = active; }
    bool GetIsFrame() { return _isFrame; }

    void SetPivot(PIVOT pivot) { _pivot = pivot; }
    PIVOT GetPivot() { return _pivot; }

    Sprite* GetSprite() { return _sprite; }
};
