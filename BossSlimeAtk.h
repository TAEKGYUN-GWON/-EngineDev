#pragma once
#include "Boss.h"
#include "BossAttack.h"

class BossSlimeAtk : public BossAttack
{
private:
	
	
	float timer = 0;
	float Ctiemr = 0;

public:
	BossSlimeAtk(Boss* boss) : BossAttack(boss) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

