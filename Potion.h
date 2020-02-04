#pragma once

#include "Item.h"

class Potion : public Item
{
private:

	typedef Item super;

	int _healRate = 0;

public:

	Potion() {}
	~Potion() {}

	virtual void Init();


	int GetHealRate() { return _healRate; }

	void SetHealRate(int healRate);


};

