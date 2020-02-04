#pragma once
#include "Boss.h"
#include "BossState.h"

class BossDead : public BossState
{
private:

public:
	BossDead(Boss* boss) : BossState(boss) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

