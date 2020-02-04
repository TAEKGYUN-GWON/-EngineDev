#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Tile.h"

class PlayerMove : public PlayerState
{
private:

public:
	PlayerMove(Player* obj) : PlayerState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

