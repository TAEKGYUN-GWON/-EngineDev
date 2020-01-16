#pragma once
#include "Scene.h"
#include "Tile.h"

#define SAMPLE_TILE_X_NUM 32
#define SAMPLE_TILE_Y_NUM 20

enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

enum OBJECT
{
	OBJ_WALL,
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//벽돌 등 오브젝트
	OBJ_PLAYER,
	OBJ_ENEMY1, OBJ_ENEMY2,
	OBJ_ENEMY3, OBJ_ENEMY4,
	OBJ_NONE,							//나중에 지울용도
};

class Maptool : public Scene
{
private:
	Tile* _currentTile;
	Tile* _sampleTile[SAMPLE_TILE_X_NUM * SAMPLE_TILE_Y_NUM];
	Tile* _tiles[TILENUMX * TILENUMY];

	int _ctrSelect;

	Object* _btn1;
	Object* _STGround;

public:
	virtual void Init();
	virtual void Update();

	void SetUp();
	void SetMap();
};

