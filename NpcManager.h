#pragma once
#include "Npc.h"
#include "Astar.h"
#include "ShopScene.h"

class ShopStandManager;
class CheckStand;
class ShopScene;

enum DESTINATION
{
	DES_WINDOW,
	DES_STAND1,
	DES_STAND2,
	DES_STAND3,
	DES_STAND4,
	DES_CHECKSTAND,
	DES_DOOR,
	DES_END
};
class NpcManager
{
private:
	Npc* _npc;
	vector<Npc*> _vNpc;
	ShopStandManager* _shopStandMgr;
	CheckStand* _checkStand;

	Vector2 _positions[DESTINATION::DES_END];

	Astar* _ast;

	int _counter; //이 시간만큼 흐른 뒤 새로운 엔피씨 입장함
	int _timer;

public:
	void Init(ShopScene* parent);
	void Update();
	void Release();
	

	void MakeNpc();
	void SetAstar(); //목적지 정해주는것임
	void AstarFunction(int i, int asttar); //astar 돌아가는 곳

	void CheckStandCollision(); //계산대랑 충돌
	void ShopStandCollision(); //가판대랑 충돌

	void SetCheckStandLink(CheckStand* checkstand) { _checkStand = checkstand; }
	void SetShopStandMgrLink(ShopStandManager* shopstsandmgr) { _shopStandMgr = shopstsandmgr; }
	vector<Npc*> GetNpcVector() { return _vNpc; }

};

