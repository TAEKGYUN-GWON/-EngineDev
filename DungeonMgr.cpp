#include "stdafx.h"
#include "DungeonMgr.h"

void DungeonMgr::Init(Player* player)
{
	_player = player;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Dungeon* room = new Dungeon;
			room->Init(Vector2(i * TILEWIDTH * Dungeon_X, j * TILEHEIGHT * Dungeon_Y));
			_rooms.push_back(room);
		}
	}
}

void DungeonMgr::Update()
{
	for (Dungeon* d : _rooms)
	{
		if (_player->GetTrans()->GetBottomPos() > d->GetTrans()->GetPos() &&
			_player->GetTrans()->GetBottomPos() < d->GetTrans()->GetPos() + Vector2(TILEWIDTH * Dungeon_X, TILEHEIGHT * Dungeon_Y))
		{
			if (!d->GetRoomActive())
			{
				d->SetRoom();
			}
			if(CAMERA->GetPosition() != d->GetTrans()->GetPos() - Vector2(55, 0))
				CAMERA->MoveTo(d->GetTrans()->GetPos() - Vector2(55,0), 1,false);
			
		}
		else d->CloseRoom();
		d->Update();
	}
}

void DungeonMgr::Render()
{
	wchar_t buffer[128];

	for (Dungeon* d : _rooms)
	{
		d->Render();
		swprintf(buffer, 128, L"X : %f\nY : %f", d->GetTrans()->GetPos().x, d->GetTrans()->GetPos().y);
		GRAPHICMANAGER->Text(d->GetTrans()->GetPos(), buffer, 40, 300, 50, ColorF::Azure, TextPivot::LEFT_TOP, L"¸¼Àº°íµñ",true);
	}
}
