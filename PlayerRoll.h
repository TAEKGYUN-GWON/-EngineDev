#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRoll : public PlayerState
{
private:
	float _rollSpeed;
	float _friction;

public:
	PlayerRoll(Player* obj) : PlayerState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

