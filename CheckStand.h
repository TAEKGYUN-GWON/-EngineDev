#pragma once
#include "Object.h"
//#include "Npc.h"

class CheckStand :public Object
{
private:
	bool _isInUse;
	//Npc* _npc;

public:

	virtual void Init()override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetStandisInUse(bool isinuse) { _isInUse = isinuse; }
	bool GetStandisInUse() { return _isInUse; }
	//void SetNpc(Npc* npc) { _npc = npc; }

	
};

