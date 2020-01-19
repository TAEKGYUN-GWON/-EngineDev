#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Transform.h"
//¡÷ºÆ
Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Vector2 pos)
{
	Object::Init();

	AddComponent<Sprite>();
	_trans->pos = pos;
	_trans->scale = Vector2(100,100);
}

void Player::Update()
{
	Object::Update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_trans->SetPos(_trans->pos + Vector2::left * 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_trans->SetPos(_trans->pos + Vector2::right * 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_trans->SetPos(_trans->pos + Vector2::up * 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_trans->SetPos(_trans->pos + Vector2::down * 3);
	}
}

