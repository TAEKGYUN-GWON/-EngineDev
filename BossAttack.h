#pragma once
#include "BossState.h"
#include "Boss.h"

	//보스 공격 기본 틀
class BossAttack : public BossState
{
protected:
	//여기에 뭐 주지.......
	int _count;
	float _timer;
	float _angle;

	Object* _area;

public:
	BossAttack(Boss* boss) : BossState(boss) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

