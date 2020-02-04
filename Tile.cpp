#include "stdafx.h"
#include "Tile.h"
Vector2 Tile::tileSize = Vector2(TILEWIDTH, TILEHEIGHT);

void Tile::Init(int idX, int idY)
{
	Object::Init();

	_tag = "Tile";

	//_sprite->Init();
	//_sprite->Stop();
	_color = ColorF::Enum::Gray;

	_trans->pos = Vector2(idX * TILEWIDTH + (TILEWIDTH / 2),
		idY * TILEHEIGHT + (TILEHEIGHT / 2));
	_trans->SetScale(TILEWIDTH, TILEHEIGHT);

	_idX = idX;
	_idY = idY;

	_f = -1;
	_g = _h = _isOpen = _isClose = 0;
	_parent = nullptr;

}

void Tile::SetFrameXY(int x, int y)
{
}
