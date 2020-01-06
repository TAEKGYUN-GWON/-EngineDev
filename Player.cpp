#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Transform.h"
//�ּ�
Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Vector2 pos)
{
	_sprite->Init(true, true);
	_sprite->SetImgName("number");
	_sprite->SetFPS(0.1f);

	_trans->pos = pos;
	_trans->scale = Vector2(_sprite->GetGraphic()->GetFrameWidth(), _sprite->GetGraphic()->GetFrameHeight());

	_sprite->GetGraphic()->SetFlip(true);
}

void Player::Update()
{
	super::Update();
}
