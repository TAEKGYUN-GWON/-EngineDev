#include "stdafx.h"
#include "Tile.h"

Vector2 Tile::tileSize = Vector2(TILE_WIDTH, TILE_HEIGHT);

void Tile::Init(int idX, int idY)
{
	Object::Init();
	
	_tag = "Tile";

	_trans->pos = Vector2(idX * TILE_WIDTH + (TILE_WIDTH / 2),
		idY * TILE_HEIGHT + (TILE_HEIGHT / 2));
	_trans->SetScale(TILE_WIDTH, TILE_HEIGHT);

	_idX = idX;
	_idY = idY;
	_node = nullptr;
	_f = -1;
	_g = _h = _isOpen = _isClose = 0;
	_parent = nullptr;
	_sprite = AddComponent<Sprite>();
	_sprite->Init();
	_sprite->SetShowRect(false);
	_imgName = "None";
	_attribute = TAttribute::NONE;
}

void Tile::Render()
{
	Object::Render();
}

void Tile::SetPhysics()
{
	if (_physics) return;

	_physics = AddComponent<PhysicsBody>();

	_physics->Init(BodyType::STATIC, 1, 1);
}

void Tile::SetImgName(string imgKey)
{
	_imgName = imgKey;
}
