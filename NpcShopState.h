#pragma once
#include "ShopStand.h"
#include "CheckStand.h"
#include "ShopStandManager.h"

class Npc;

class NpcShopState
{
protected:
	
	string _state;
	Npc* _npc;

	ShopStandManager* _shopStandMgr; //써야될거같아서 넣어둠
	CheckStand* _checkStand;

public :
	NpcShopState() {}
	//NpcShopState(Npc* npc) : _npc(npc {}
	NpcShopState(Npc* npc) { _npc = npc; }

	void SetCheckStandLink(CheckStand* checkstand) { _checkStand = checkstand; }
	void SetShopStandLink(ShopStandManager* shopstandmgr) { _shopStandMgr = shopstandmgr; }

	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}

	string GetState() { return _state; }
};

class NpcIdle : public NpcShopState
{
private:

public:
	NpcIdle(Npc* npc) : NpcShopState(npc) {}
	
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

class NpcMove : public NpcShopState
{
private:

public:
	NpcMove(Npc* npc) : NpcShopState(npc) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

class NpcHome : public NpcShopState
{
private:

public:
	NpcHome(Npc* npc) : NpcShopState(npc) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};