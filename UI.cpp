#include "stdafx.h"
#include "UI.h"
#include "ProgressBar.h"
#include "Player.h"

void UI::Init()
{
	GRAPHICMANAGER->AddImage("statusbar", L"Resource/UI/_sb statusbar.png");
	GRAPHICMANAGER->AddImage("pistol_bg", L"Resource/UI/pistol_bg.png");
	GRAPHICMANAGER->AddImage("a_pistol", L"Resource/UI/a_pistol.png");

	_statusbar = Object::CreateObject<Object>();
	_statusbar->Init();
	_statusbar->GetTrans()->SetPos(WINSIZEX / 2, WINSIZEY - 24);
	Sprite* s = _statusbar->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("statusbar");
	s->SetScale(Vector2(1.5f, 1.5f));
	//s->SetCameraEffected(false);

	_hpBar = new ProgressBar;
	_hpBar->Init("health_line", "hp_bg", L"Resource/UI/", L"Resource/UI/", _statusbar->GetTrans()->GetPos() + Vector2(-192.f, -6.0f));
	_hpBar->SetScale(Vector2(1.5f, 1.5f));

	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Player");

	_pistolBg = GRAPHICMANAGER->FindImage("pistol_bg");
}

void UI::Release()
{
	_statusbar->Release();
	//_hpBar->Release();
}

void UI::Update()
{
	_hpBar->SetGauge(_player->GetAbility()->GetCurrentHP(), _player->GetAbility()->GetMaxHP());

	_statusbar->GetTrans()->SetPos(CAMERA->GetPosition().x + WINSIZEX / 2, CAMERA->GetPosition().y + WINSIZEY - 24);
	_statusbar->GetComponent<Sprite>()->SetPosition(_statusbar->GetTrans()->GetPos());
}

void UI::Render()
{
	_statusbar->Render();
	_hpBar->Render();
	_pistolBg->Render(Vector2(WINSIZEX / 2 + 50, WINSIZEY - 22), 1.0f, PIVOT::CENTER, false);
}
