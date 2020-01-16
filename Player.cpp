#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Transform.h"
//ÁÖ¼®
Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Vector2 pos)
{
	_sprite->Init();
	_sprite->SetImgName("eagle");

	_trans->pos = pos;
	_trans->scale = Vector2(_sprite->GetGraphic()->GetFrameWidth(), _sprite->GetGraphic()->GetFrameHeight());

}
