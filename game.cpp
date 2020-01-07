#include "stdafx.h"
#include "game.h"


HRESULT game::init()
{




	return S_OK;
}

void game::release()
{
}

void game::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("StartScene");

	OBJECTMANAGER->Update("Start");
}

void game::render()
{
	OBJECTMANAGER->Render("Start");
}
