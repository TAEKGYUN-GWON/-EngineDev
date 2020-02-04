#pragma once
#include "Scene.h"
#include "Tile.h"
#include <commdlg.h> //OPENFILENAME을 위한 헤더

//#define SAMPLE_TILE_X_NUM 8//32
//#define SAMPLE_TILE_Y_NUM 10//20

#define SAMPLE_TILE_X_NUM 4
#define SAMPLE_TILE_Y_NUM 6

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

    //vector<Vector2> vStartPos;
    //vector<Vector2> vSize;

    Vector2 startPos;
    Vector2 size;

    Vector2 startPos2;
    Vector2 size2;

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

//typedef struct tagCoordinate
//{
//   vector<Vector2> vStartPos;
//   vector<Vector2> vSize;
//}vCoordinate;

struct tagTile
{
    string imgKey;
    //Attribute attribute;
    string attribute;

    //vector<Vector2> vStartPos;
    //vector<Vector2> vSize;

    //vCoordinate vCoord;

    Vector2 startPos;
    Vector2 startPos2;
    Vector2 size;
    Vector2 size2;

    bool isFrame;
    int frameX;
    int frameY;
    PIVOT pivot;

    tagTile()
    {
        //imgKey.clear();
        imgKey = "empty";
        //attribute = "None";
        isFrame = false;
        frameX = 1;
        frameY = 1;
        //pivot = PIVOT::RIGHT_BOTTOM;
        pivot = PIVOT::CENTER;

        //vStartPos.clear();
        //vSize.clear();
        //
        //vCoord.vStartPos.clear();
        //vCoord.vSize.clear();

        startPos = Vector2(1, 1);
        size = Vector2(1, 1);
        startPos2 = Vector2(1, 1);
        size2 = Vector2(1, 1);
    }

    //vCoordinate Setting(Vector2* startPos, Vector2* size, int arrLen)
    //{
    //   for (int i = 0; i < arrLen; ++i)
    //   {
    //      vCoord.vStartPos.push_back(startPos[i]);
    //      vCoord.vSize.push_back(size[i]);
    //   }
    //}

    tagTile* Clone(string imgKey, string attribute, bool isFrame, int frameX, int frameY, PIVOT pivot, Vector2 startPos, Vector2 size, Vector2 startPos2, Vector2 size2)
        //tagTile* Clone(string imgKey, string attribute, bool isFrame, int frameX, int frameY, PIVOT pivot, vector<Vector2> startPos, vector<Vector2> size)
        //tagTile* Clone(string imgKey, string attribute, bool isFrame, int frameX, int frameY, PIVOT pivot)
    {
        tagTile* tile = new tagTile;
        tile->imgKey = imgKey;
        tile->attribute = attribute;
        tile->isFrame = isFrame;
        tile->frameX = frameX;
        tile->frameY = frameY;
        tile->pivot = pivot;

        //tile->vStartPos.clear();
        //tile->vSize.clear();

        tile->startPos = startPos;
        tile->size = size;
        tile->startPos2 = startPos2;
        tile->size2 = size2;

        return tile;
    }

    tagTile* Clone(string imgKey, string attribute, bool isFrame, int frameX, int frameY, PIVOT pivot, Vector2 startPos, Vector2 size)
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
        tile->startPos2 = Vector2(1, 1);
        tile->size2 = Vector2(1, 1);

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
    tagSampleTile _sampleTile[SAMPLE_TILE_X_NUM * SAMPLE_TILE_Y_NUM];
    Tile* _tiles[TILENUMX * TILENUMY];
    tagTile _tagTiles[TILENUMX * TILENUMY];

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
