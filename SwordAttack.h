#pragma once
#include "PlayerAttack.h"
#include "Player.h"

class SwordAttack : public PlayerAttack
{
private:
	Object* _atkArea;

public:
	SwordAttack(Player* obj) : PlayerAttack(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

