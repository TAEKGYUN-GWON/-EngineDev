#include "stdafx.h"
#include "Tile.h"
Vector2 Tile::tileSize = Vector2(TILEWIDTH, TILEHEIGHT);

void Tile::Init(int idX, int idY)
{
	//_sprite->Init();
	//_sprite->Stop();
	_color = ColorF::Enum::Gray;

	_center = Vector2(idX * TILEWIDTH + (TILEWIDTH / 2),
		idY * TILEHEIGHT + (TILEHEIGHT / 2));
	_trans->pos = _center;
	_trans->SetScale(TILEWIDTH, TILEHEIGHT);
	_trans->SetRect();
	_idX = idX;
	_idY = idY;

}

void Tile::Release()
{
}

void Tile::SetFrameXY(int x, int y)
{
	_sprite->SetFrameX(x);
	_sprite->SetFrameY(y);
}
