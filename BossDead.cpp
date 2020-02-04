#include "stdafx.h"
#include "BossDead.h"

void BossDead::Enter()
{
	_Bstate = "Dead";

	//죽는 이미지가 두개로 나눠져 있음....어떻게 하지?
	//두번째 죽는 이미도 41프레임
	_boss->GetSprite()->SetImgName("deadBoss1");
	_boss->GetSprite()->SetMaxFrameX(41);
	_boss->GetSprite()->SetFrameX(0);
	_boss->GetSprite()->SetFPS(1.0f);
	_boss->GetSprite()->SetIsLoop(false); //true 안해줘도 되겠지..?
	_boss->GetSprite()->SetPosition(_boss->GetTrans()->GetPos());

	//if (setmaxframex가 마지막이면
	// _boss->GetSprite()->SetImgName(deadBoss2);
	// 이러면 될까...?
}

void BossDead::Update()
{
}

void BossDead::Exit()
{
}
