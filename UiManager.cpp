#include "stdafx.h"
#include "UiManager.h"

void UiManager::Init()
{
	_coin =			GRAPHICMANAGER->AddImage("coin", L"resource/img/UI/coin.png");
	_bag =			GRAPHICMANAGER->AddImage("moneyBag", L"resource/img/UI/moneyBag.png");
	_bagButton =	GRAPHICMANAGER->AddImage("UI_Bag", L"resource/img/UI/UI_Bag.png");
	_potionButton = GRAPHICMANAGER->AddImage("UI_Potion", L"resource/img/UI/UI_Potion.png");
	_heart =		GRAPHICMANAGER->AddImage("heart", L"resource/img/UI/heart.png");
	_hp =			GRAPHICMANAGER->AddImage("hp", L"resource/img/UI/PlayerHp.png");
	hpMaxX = _hp->GetWidth();
	hpMaxY = _hp->GetHeight();
	//_heart =		GRAPHICMANAGER->AddImage("heart", L"resource/img/UI/heart.png");
	_weapon =		GRAPHICMANAGER->AddFrameImage("UI_WeaponSwap", L"resource/img/UI/UI_WeaponSwap.png",4,2);

	//_coin = UiObject::CreateUiObject<UiObject>();
	//_bag = UiObject::CreateUiObject<UiObject>();
	//_bagButton = UiObject::CreateUiObject<UiObject>();
	//_potionButton = UiObject::CreateUiObject<UiObject>();
	//_heart = UiObject::CreateUiObject<UiObject>();
	//_weapon = UiObject::CreateUiObject<UiObject>();

	/*_coin->GetTrans()->SetPos(Vector2(25.5f, 114));
	_bag->GetTrans()->SetPos(Vector2(54, 58.5f));
	_bagButton->GetTrans()->SetPos(Vector2(1210, 207));
	_potionButton->GetTrans()->SetPos(Vector2(1243.5, 30));
	_heart->GetTrans()->SetPos(Vector2(132, 46));
	_weapon->GetTrans()->SetPos(Vector2(1150.f, 103));

	_coin->SetSprite("coin");
	_bag->SetSprite("moneyBag");
	_bagButton->SetSprite("UI_Bag");
	_potionButton->SetSprite("UI_Potion");
	_heart->SetSprite("heart");
	_weapon->SetSprite("UI_WeaponSwap",true);
	_weapon->GetSprite()->Stop();*/
	player = (Player*) SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
	inven = player->GetInventory();
}

void UiManager::Update()
{
}

void UiManager::Render()
{
	wchar_t buffer[128];
	swprintf(buffer, 128, L"%d", inven->GetMoney());
	GRAPHICMANAGER->Text(Vector2(43, 100), buffer, 20, 300, 50, ColorF::White);


	_bag->Render(Vector2(54, 58.5f), 1, PIVOT::CENTER, false);
	_heart->Render(Vector2(132, 40), 1, PIVOT::CENTER, false);
	_hp->Render(Vector2(170, 30), Vector2((hpMaxX+60) / (player->GetAbility()->GetMaxHP() / player->GetAbility()->GetCurrentHP()), hpMaxY), 0, false, 0.7f, PIVOT::LEFT_TOP, false);
//	GRAPHICMANAGER->DrawRect(Vector2(180, 46), Vector2(200 / (player->GetAbility()->GetMaxHP() / player->GetAbility()->GetCurrentHP()), 10), 0.3f, ColorF(0xff3851, 0.7f), PIVOT::LEFT_TOP, 50, false);
	_coin->Render(Vector2(25.5f, 114), 1, PIVOT::CENTER, false);
	_potionButton->Render(Vector2(1243.5, 30), 1, PIVOT::CENTER, false);
	_bagButton->Render(Vector2(1210, 207), 1, PIVOT::CENTER, false);
	_weapon->FrameRender(Vector2(1150.f, 103), 0, 0, 1, PIVOT::CENTER, false);
}
