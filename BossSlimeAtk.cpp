#include "stdafx.h"
#include "BossSlimeAtk.h"
#include "BossIdle.h"
#include "SlimeEnemy.h"


void BossSlimeAtk::Enter()
{
	_Bstate = "Attack";

	timer = Ctiemr = 0;

}

void BossSlimeAtk::Update()
{
	timer += TIMEMANAGER->getElapsedTime();
	Ctiemr += TIMEMANAGER->getElapsedTime();

	if (Ctiemr > 0.5f) 
	{
		Ctiemr = 0;
		SlimeEnemy* slime = Object::CreateObject<SlimeEnemy>(_boss);
		slime->Init(Vector2(_boss->GetTrans()->GetPos() + Vector2::down * (_boss->GetTrans()->GetScale() / 2) + Vector2(0, 20)));

		_boss->GetEnemys()->push_back(slime);
	}

	if (timer > 5) _boss->SetState(new BossIdle(_boss));
}

void BossSlimeAtk::Exit()
{
	
}
