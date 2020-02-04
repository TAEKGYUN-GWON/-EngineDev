#pragma once

#include "Item.h"

class ETC : public Item
{
protected:

	typedef Item super;

public:

	ETC() {}	//생성자에 가격 넣기
	~ETC() {}

	virtual void Init();
};