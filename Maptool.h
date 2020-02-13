#pragma once
#include "Scene.h"
#include <commdlg.h> //OPENFILENAME을 위한 헤더

class PaletteBtn;
class Player;

#define SET_TILE_WIDTH 64
#define SET_TILE_HEIGHT 64

#define SET_TILE_NUM_X 4
#define SET_TILE_NUM_Y 6

enum class SamplePage
{
    Terrain_1,
    Terrain_2,
    Object,
    PAGE_END,
};

enum class EraserType
{
    Single,
    Group,
    NoDeleteImage,
    OnlyDeleteImage,
    End,
};

struct tagTile
{
    string imgKey;
    TAttribute attribute;

};

class Tile;

class Maptool : public Scene
{
private:
    Player* _player;

    PaletteBtn* _currentTile;
    vector<PaletteBtn*> _vSetTer_1;
    vector<PaletteBtn*> _vSetTer_2;
    vector<PaletteBtn*> _vSetObj;

    vector<Tile*> _vTiles;
    vector<tagTile> _vTagTiles;

    Vector2 _startPos;
    Vector2 _endPos;

    SamplePage _page;
    EraserType _eraser;

    int _ctrSelect;

    int index;

    POINT _prevMouse;

    RECT _rcLoad;
    RECT _rcSave;

    RECT _rcEraserType;

private:
    void ClassificationAttribute();

public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void Save();
    void Load();

    void SetUp();
    void SetMap();
    void ClickSetTile();
    void RemoveObject();
    void SetAttribute(int curIdx, PaletteBtn& palett);

    void SetPage();
};
