#pragma once

class Boss;

class BossState abstract
{
protected:
	Boss* _boss;
	string _Bstate;

public:
	BossState() {}
	BossState(Boss* boss) : _boss(boss) {}

	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}

	string GetState() { return _Bstate; }
};

