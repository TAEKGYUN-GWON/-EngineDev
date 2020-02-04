#pragma once
#include "PlayerAttack.h"
#include "Player.h"
#include "Bullet.h"

class BowAttack : public PlayerAttack
{
private:
	bool _isFire;
public:
	BowAttack(Player* obj) : PlayerAttack(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

