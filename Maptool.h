#pragma once
#include "Scene.h"
#include "Tile.h"
#include <commdlg.h> //OPENFILENAME을 위한 헤더

#define SET_TILE_WIDTH 60
#define SET_TILE_HEIGHT 60

#define SET_TILE_NUM_X 4
#define SET_TILE_NUM_Y 6

#pragma region 잠시보류

enum CTRL
{
    CTRL_SAVE,
    CTRL_LOAD,
    CTRL_TERRAINDRAW,
    CTRL_OBJDRAW,
    CTRL_ERASER,
    CTRL_END
};

struct tagCurrentTile
{
    string imgKey;
    bool isFrame;

    Vector2 startPos;
    Vector2 size;

    PIVOT pivot;
};

struct tagSampleTile
{
    Vector2 pos;
    string imgKey;
};

#pragma endregion

enum class SamplePage
{
    TOWN,
    DUNGEON,
    PAGE_END,
};

enum Attribute
{
    NONE_MOVE,
    DESTRUCTION,
    CLIFF,
    TERRAIN_DESTRUCTION,
    NONE,
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
    Attribute attribute;

    Vector2 startPos;
    Vector2 size;

    bool isFrame;
    int frameX;
    int frameY;
    PIVOT pivot;

    tagTile()
    {
        imgKey = "empty";
        attribute = Attribute::NONE;
        isFrame = false;
        frameX = 1;
        frameY = 1;
        pivot = PIVOT::CENTER;

        startPos = Vector2(1, 1);
        size = Vector2(1, 1);
    }

    tagTile* Clone(string imgKey, Attribute attribute, bool isFrame, int frameX, int frameY, PIVOT pivot, Vector2 startPos, Vector2 size)
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

class Maptool : public Scene
{
private:
    typedef map<string, tagTile*> mapTileList;
    typedef map<string, tagTile*>::iterator mapTileIter;

private:
    tagCurrentTile _currentTile;
    vector<tagSampleTile> _vSetTile;
    vector<Tile*> _vTiles;
    vector<tagTile> _vTagTiles;

    mapTileList _mTileList;

    SamplePage _page;
    EraserType _eraser;

    int _ctrSelect;

    POINT _prevMouse;

    RECT _rcLoad;
    RECT _rcSave;

    RECT _rcEraserType;

    Object* obj;

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
    //void FindIndex(int curIdx, Vector2 size);
    void SetAttribute(int curIdx, Vector2 StartPos, Vector2 size, Vector2 StartPos2, Vector2 size2, string attribute);

    tagTile* FindTile(string imgKey);

    void TileSetting();
    void SetPage();
};
