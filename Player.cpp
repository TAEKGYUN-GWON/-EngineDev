#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Transform.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Vector2 pos)
{
	_graphic->Init(true, true);
	_graphic->SetImgName("number");
	_graphic->SetFPS(0.1f);

	_trans->pos = pos;
	_trans->scale = Vector2(_graphic->GetGraphic()->GetFrameWidth(), _graphic->GetGraphic()->GetFrameHeight());

	_graphic->GetGraphic()->SetFlip(true);
}

void Player::Update()
{
	super::Update();
}
