#include "stdafx.h"
#include "Smithy.h"
#include "Component.h"
#include "ETCS.h"

void Smithy::Init(Inventory* inven)
{
	_back = GRAPHICMANAGER->AddImage("backGround", L"resource/img/Smithy/S_Back.png");
	_blackSmith = GRAPHICMANAGER->AddImage("blackSmith", L"resource/img/Smithy/BlackSmith.png");
	_anvil = GRAPHICMANAGER->AddImage("anvil", L"resource/img/Smithy/Anvil.png");
	_title = GRAPHICMANAGER->AddImage("titleBass", L"resource/img/Smithy/Title_Bass.png");
	_itemName = GRAPHICMANAGER->AddImage("nameBass", L"resource/img/Smithy/Name_Bass.png");
	_upgradable = GRAPHICMANAGER->AddImage("upgradable", L"resource/img/Smithy/Upgradable.png");
	_notUpgradeble = GRAPHICMANAGER->AddImage("notUpgradable", L"resource/img/Smithy/NotUpgradable.png");
	_upgradeRecipe = GRAPHICMANAGER->AddImage("upgradeRecipe", L"resource/img/Smithy/Upgrade.png");
	_itemList = GRAPHICMANAGER->AddImage("itemList", L"resource/img/Smithy/Reinforce_ItemList.png");
	_pSword = GRAPHICMANAGER->AddImage("pSword", L"resource/img/Smithy/Will's_Sword.png");
	_pocket = GRAPHICMANAGER->AddImage("pocket", L"resource/img/Smithy/Gold5.png");
	_pocketCircle = GRAPHICMANAGER->AddImage("pocketCicle", L"resource/img/Smithy/Pocket_Circle.png");


	_material1 = GRAPHICMANAGER->AddImage("crystal_Energy", L"resource/img/Smithy/material1.png");
	_material2 = GRAPHICMANAGER->AddImage("reinforced_Steel_G", L"resource/img/Smithy/material2.png");
	_material3 = GRAPHICMANAGER->AddImage("golem_Core", L"resource/img/Smithy/material3.png");
	
	_mOn1 = GRAPHICMANAGER->AddImage("onCheck1", L"resource/img/Smithy/Upgradable.png");
	_mOn2 = GRAPHICMANAGER->AddImage("onCheck2", L"resource/img/Smithy/Upgradable.png");
	_mOn3 = GRAPHICMANAGER->AddImage("onCheck3", L"resource/img/Smithy/Upgradable.png");

	_coin = GRAPHICMANAGER->AddImage("coin", L"resource/img/Smithy/Coin.png");

	//_recipePrice = 100;
	_upgradeGap = 10;

	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");

	//_inven = new Inventory();
	_inven = inven;
	//_inven->Init();
	_inven->AddMoney(135948788);
	_inven->SetATK(30);

	_recipePrice = _inven->GetATK() / 10 * 0.4 * 2316;

	_m1Count = 2;
	_m2Count = 2;
	_m3Count = 2;


	/*for (int i = 0; i < 3; i++)
	{
		_mRecipe.insert(make_pair(new Graphic(), 2));
	}*/



	_isShow = false;
}

void Smithy::Update()
{
	KeyInput();
}

void Smithy::Release()
{
	
}

void Smithy::Render()
{
	if (_isShow)
	{
		ShowImage();
		ShowUI();
	}

}

void Smithy::KeyInput()
{
	if (KEYMANAGER->isOnceKeyDown('J') && _isPlayerIn)
	{
		_isShow = !_isShow;
	}

	if (_isShow)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_inven->DeductionMoney(5000);
		}

		if (KEYMANAGER->isOnceKeyDown('U'))
		{
			Buy();
		}

		if (KEYMANAGER->isStayKeyDown('Y'))
		{
			Item* i = Item::CreateItem<Crystal_Energy>(Vector2(0, 0));
			_inven->Insert(i);

			i = Item::CreateItem<Crystal_Energy>(Vector2(0, 0));
			_inven->Insert(i);

			i = Item::CreateItem<Golem_Core>(Vector2(0, 0));
			_inven->Insert(i);

			i = Item::CreateItem<Reinforced_Steel_G>(Vector2(0, 0));
			_inven->Insert(i);

			//_inven->Insert());
		}
	}
}

/*bool Smithy::CheckPlayerPos()
{
	if (_player->GetTrans()->GetPos().x < _smithPos.x - 80 && _player->GetTrans()->GetPos().y >= _smithPos.y + 50)
	{
		return true;
	}

	return false;
}*/

void Smithy::UpdateMaterial()
{
	_vMaterialCount.clear();

	//재료 이미지 키값, 체크 활성화 키값, 필요개수, 소지량
	_vMaterialCount.push_back(make_tuple(_material3->GetImageKey(), _mOn3->GetImageKey(), _m3Count, _inven->FindItemSome(_material3->GetImageKey())));
	_vMaterialCount.push_back(make_tuple(_material2->GetImageKey(), _mOn2->GetImageKey(), _m2Count, _inven->FindItemSome(_material2->GetImageKey())));
	_vMaterialCount.push_back(make_tuple(_material1->GetImageKey(), _mOn1->GetImageKey(), _m1Count, _inven->FindItemSome(_material1->GetImageKey())));
}

void Smithy::ShowImage()
{

	UpdateMaterial();

	_back->Render(Vector2(0,0), 0.8f, PIVOT::LEFT_TOP, false);
	_blackSmith->Render(Vector2(250, WINSIZEY / 2), 1, PIVOT::CENTER, false);
	_anvil->Render(Vector2(WINSIZEX / 2, WINSIZEY - 150), 1, PIVOT::CENTER, false);
	_title->Render(Vector2(WINSIZEX / 2, 50), 1, PIVOT::CENTER, false);
	_itemName->Render(Vector2(WINSIZEX - 200, 40), 1, PIVOT::CENTER, false);
	_upgradeRecipe->Render(Vector2(WINSIZEX - 200, WINSIZEY / 2 + 30), 1, PIVOT::CENTER, false);
	_itemList->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2 - 80), 1, PIVOT::CENTER, false);
	_pSword->Render(Vector2(WINSIZEX - 115, 110), 1, PIVOT::CENTER, false);
	_pocketCircle->Render(Vector2(60, 60), 1, PIVOT::CENTER, false);
	_pocket->Render(Vector2(60, 60), 1, PIVOT::CENTER, false);

	_coin->Render(Vector2(110, 140), 1, PIVOT::CENTER, false);


	for (int i = 2; i >= 0; i--)
	{
		GRAPHICMANAGER->FindImage(get<0>(_vMaterialCount[i]))->Render(Vector2(WINSIZEX - 300, WINSIZEY - (-10 + (i + 1) * 90)), 1, PIVOT::CENTER, false);
	}

	//크리스탈
	if (get<2>(_vMaterialCount[2]) <= get<3>(_vMaterialCount[2]))
	{
		GRAPHICMANAGER->FindImage(get<1>(_vMaterialCount[2]))->Render(Vector2(WINSIZEX - 89.5, WINSIZEY - 262.5), 1, PIVOT::CENTER, false);
	}

	//강철
	if (get<2>(_vMaterialCount[1]) <= get<3>(_vMaterialCount[1]))
	{
		GRAPHICMANAGER->FindImage(get<1>(_vMaterialCount[1]))->Render(Vector2(WINSIZEX - 89.5, WINSIZEY - 176.5), 1, PIVOT::CENTER, false);
	}

	//코어
	if (get<2>(_vMaterialCount[0]) <= get<3>(_vMaterialCount[0]))
	{
		GRAPHICMANAGER->FindImage(get<1>(_vMaterialCount[0]))->Render(Vector2(WINSIZEX - 89.5, WINSIZEY - 90.5), 1, PIVOT::CENTER, false);
	}

}

void Smithy::ShowUI()
{

	ColorF* color = new ColorF(0xecddc0, 1.0f);

	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2 - 80, 30), L"벌컨의 대장간", 25, 200, 50, *color, TextPivot::LEFT_TOP, L"나눔스퀘어라운드");

	standardStr = to_string(_inven->GetATK());
	standardStr += " -> ";
	standardStr += to_string(_upgradeGap + _inven->GetATK());
	printStr.assign(standardStr.begin(), standardStr.end());

	GRAPHICMANAGER->Text(Vector2(WINSIZEX - 370, 180), printStr, 30, 300, 50, *color, TextPivot::RIGHT_BOTTOM);

	color = new ColorF(0x191919, 1.f);
	GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2 - 50, WINSIZEY / 2 - 100), L"강화하기", 50, 100, 50, *color, TextPivot::CENTER, L"나눔스퀘어라운드");

	GRAPHICMANAGER->Text(Vector2(WINSIZEX - 350, WINSIZEY / 2 + 10), L"레시피", 25, 100, 50, *color, TextPivot::CENTER, L"나눔스퀘어라운드");

	standardStr = to_string(_recipePrice);
	printStr.assign(standardStr.begin(), standardStr.end());
	GRAPHICMANAGER->Text(Vector2(WINSIZEX - 200, WINSIZEY / 2 + 10), printStr, 25, 100, 50, *color, TextPivot::CENTER, L"나눔스퀘어라운드");

	standardStr = to_string(_inven->GetMoney());
	printStr.assign(standardStr.begin(), standardStr.end());
	color = new ColorF(0xffffff, 1.f);
	GRAPHICMANAGER->Text(Vector2(10, 125), printStr, 15, 100, 25, *color, TextPivot::CENTER, L"나눔스퀘어라운드");

	PrintRecipe();
	
}

void Smithy::Buy()
{
	if (_inven->GetMoney() >= _recipePrice && CheckMaterial())
	{
		_inven->DeductionMoney(_recipePrice);
		_inven->SetATK(_inven->GetATK() + _upgradeGap);
		   
		for (int i = 0; i < _vMaterialCount.size(); i++)
		{
			_inven->Remove(get<0>(_vMaterialCount[i]), get<2>(_vMaterialCount[i]));
		}

		Upgrade();
	}

}

bool Smithy::CheckMaterial()
{
	//크리스탈
	if (get<2>(_vMaterialCount[2]) <= get<3>(_vMaterialCount[2]))
	{
		//강철
		if (get<2>(_vMaterialCount[1]) <= get<3>(_vMaterialCount[1]))
		{
			//코어
			if (get<2>(_vMaterialCount[0]) <= get<3>(_vMaterialCount[0]))
			{
				return true;
			}
			else
				return false;
		}
		else 
			return false;
	}
	else
		return false;

}

void Smithy::Upgrade()
{
	_recipePrice = _inven->GetATK() / 10 * 0.4 * 2316;
	_upgradeGap *= 1.15;

	
	_m1Count = _inven->GetATK() / 8 *  1.18;
	_m2Count = _inven->GetATK() /  12*  1.45;
	_m3Count = _inven->GetATK() / 9 *  1.23;

}

void Smithy::PrintRecipe()
{
	ColorF* color = new ColorF(0x191919, 1.f);

	for (int i = 0; i <= 2; i++)
	{
		//GRAPHICMANAGER->FindImage(get<0>(_vMaterialCount[i]))->Render(Vector2(WINSIZEX - 300, WINSIZEY - (-10 + (i + 1) * 90)), 1, PIVOT::CENTER, false);

		GRAPHICMANAGER->Text(Vector2(WINSIZEX - 280, WINSIZEY - 30 - ((i+1) * 90)), L"필요:", 20, 100, 50, *color, TextPivot::CENTER, L"나눔스퀘어라운드");
		GRAPHICMANAGER->Text(Vector2(WINSIZEX - 280, WINSIZEY - ((i+1) * 90)), L"소지:", 20, 100, 50, *color, TextPivot::CENTER, L"나눔스퀘어라운드");

		standardStr = to_string(get<3>(_vMaterialCount[i]));
		printStr.assign(standardStr.begin(), standardStr.end());
		GRAPHICMANAGER->Text(Vector2(WINSIZEX - 230, WINSIZEY - (-10 + (i + 1) * 90)), printStr, 20, 100, 25, *color, TextPivot::RIGHT_CENTER, L"나눔스퀘어라운드");
		
		standardStr = to_string(get<2>(_vMaterialCount[i]));
		printStr.assign(standardStr.begin(), standardStr.end());
		GRAPHICMANAGER->Text(Vector2(WINSIZEX - 230, WINSIZEY - (20 + (i + 1) *90)), printStr, 20, 100, 25, *color, TextPivot::RIGHT_CENTER, L"나눔스퀘어라운드");
	}
}