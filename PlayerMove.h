#pragma once
#include "PlayerState.h"

class Player;

class PlayerMove : public PlayerState
{
private:
	float _speed;
	float _angle;

public:
	PlayerMove(Player* obj) : PlayerState(obj) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

