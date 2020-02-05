#include "stdafx.h"
#include "Tile.h"
Vector2 Tile::tileSize = Vector2(TILEWIDTH, TILEHEIGHT);

void Tile::Init(int idX, int idY)
{
	Object::Init();

	_tag = "Tile";

	//_sprite->Init();
	//_sprite->Stop();

	_trans->pos = Vector2(idX * TILEWIDTH + (TILEWIDTH / 2),
		idY * TILEHEIGHT + (TILEHEIGHT / 2));
	_trans->SetScale(TILEWIDTH, TILEHEIGHT);

	_idX = idX;
	_idY = idY;

	_f = -1;
	_g = _h = _isOpen = _isClose = 0;
	_parent = nullptr;
	_isActive = false;
	_sprite = AddComponent<Sprite>();
	_sprite->Init();
}

void Tile::SetPhysics()
{
	_physics = AddComponent<PhysicsBody>();

	_physics->Init(BodyType::STATIC, 1, 1);
}

void Tile::SetImgName(string imgKey)
{
	_imgName = imgKey;
	_sprite->SetImgName(imgKey);
}
