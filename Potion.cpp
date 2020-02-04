#include "stdafx.h"
#include "Potion.h"

void Potion::Init()
{
	super::Init();

	_tag = "Potion";
	_type = EItemType::useable;
	_maxCount = 5;
}

void Potion::SetHealRate(int healRate)
{
	_healRate = healRate;

}