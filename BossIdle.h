#pragma once
#include "BossState.h"
#include "Boss.h"

class BossIdle : public BossState
{
private:

	int _count = 0;
	float timer = 0;
	float ExitTime;
public:
	BossIdle(Boss* _boss) : BossState(_boss) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

