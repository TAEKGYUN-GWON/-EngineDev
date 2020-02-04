#include "stdafx.h"
#include "ETC.h"

void ETC::Init()
{
	Item::Init();

	_tag = "ETC";
	_type = EItemType::etc;
	_maxCount = 10;
}

