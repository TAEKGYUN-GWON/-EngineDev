#pragma once
#include "Scene.h"
#include "Player.h"
#include "NpcManager.h"
#include "CheckStand.h"
#include "NpcShopState.h"
#include "ShopStandManager.h"
#include "Maptool.h"
#include "ShopDoor.h"
#include "UiManager.h"
#define SHOPTILEMAXX 22
#define SHOPTILEMAXY 28

class NpcManager;

class ShopScene : public Scene
{
private:
	typedef enum PlayerPosition : byte
	{
		Up,
		Down,
	}PP;

private:
	Player* _player;
	NpcManager* _npcMgr;			 //npc 매니저
	CheckStand* _checkStand;		 //계산대
	NpcShopState* _npcShopState;	 //Npc 상태
	ShopStandManager* _shopStandMgr; //가판대 매니저
	ShopDoor* _shopDoor;			 //상점 출입문
	vector<Tile*> _tiles;
	tagTile _tagTiles[SHOPTILEMAXX * SHOPTILEMAXY];
	PP _pp;
	UiManager* UI;

public:
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render()override;
	void SetUp();

	vector<Tile*>GetTiles() { return _tiles; }
	
};

