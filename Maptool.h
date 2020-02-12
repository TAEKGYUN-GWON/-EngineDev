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

    Vector2 startPos;
    Vector2 size;

    bool isFrame;
    int frameX;
    int frameY;
    PIVOT pivot;

    tagTile()
    {
        imgKey = "empty";
        attribute = TAttribute::NONE;
        isFrame = false;
        frameX = 1;
        frameY = 1;
        pivot = PIVOT::CENTER;

        startPos = Vector2(1, 1);
        size = Vector2(1, 1);
    }

    tagTile* Clone(string imgKey, TAttribute attribute, bool isFrame, int frameX, int frameY, PIVOT pivot, Vector2 startPos, Vector2 size)
    {
        tagTile* tile = new tagTile;
        tile->imgKey = imgKey;
        tile->attribute = attribute;
        tile->isFrame = isFrame;
        tile->frameX = frameX;
        tile->frameY = frameY;
        tile->pivot = pivot;

        tile->startPos = startPos;
        tile->size = size;

        return tile;
    }
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

    SamplePage _page;
    EraserType _eraser;

    int _ctrSelect;

    POINT _prevMouse;

    RECT _rcLoad;
    RECT _rcSave;

    RECT _rcEraserType;

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
