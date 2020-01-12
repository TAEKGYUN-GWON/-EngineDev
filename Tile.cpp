#include "stdafx.h"
#include "Tile.h"
#include"Transform.h"
Vector2 Tile::tileSize = Vector2(TILEWIDTH, TILEHEIGHT);

void Tile::Init(int idX, int idY)
{
	_color = Brush_type::Enum::GRAY;

	_center = Vector2(idX * TILEWIDTH + (TILEWIDTH / 2),
		idY * TILEHEIGHT + (TILEHEIGHT / 2));
	_trans->pos = _center;
	_trans->SetScale(TILEWIDTH, TILEHEIGHT);
	_idX = idX;
	_idY = idY;
	Object::Init();
}

void Tile::Release()
{
}

void Tile::Update()
{

}

void Tile::Render()
{
	GRAPHICMANAGER->DrawFillRect(_center, Tile::tileSize, 0, _color);
	Object::Render();
	char buffer[128];
	sprintf_s(buffer, "%d, %d", _idX, _idY);
	Vector2 pos(_trans->pos.x - TILEWIDTH / 3, _trans->pos.y - TILEHEIGHT / 2);
	GRAPHICMANAGER->DrawTextD2D(pos, buffer, 10, D2D1::ColorF::White);
}
