#include "stdafx.h"
#include "NpcShopState.h"
#include "Npc.h"

//IDLE==========================
void NpcIdle::Enter()
{
	_state = "Idle";
	

}

void NpcIdle::Update()
{
	//창문으로 가고싶은 상태면(입장직후는 무조건 이거)
	if (_npc->GetNpcThought() == NPCTHOUGHT::WINDOW)
	{
		_npc->ChangeState(new NpcMove(_npc));
	}
	//물건을 구경하러 판매대로 가고싶다
	if (_npc->GetNpcThought() == NPCTHOUGHT::CHOOSE)
	{
		_npc->ChangeState(new NpcMove(_npc));
	}
	//물건을 가격비교 해보고 사고싶은 상태면
	if (_npc->GetNpcThought() == NPCTHOUGHT::BUY)
	{
		_npc->ChangeState(new NpcMove(_npc));
	}
	//물건 비교해보고 안사고싶으면
	if (_npc->GetNpcThought() == NPCTHOUGHT::NOTBUY)
	{
		_npc->ChangeState(new NpcMove(_npc));
	}
	//집에 가고 싶으면
	if (_npc->GetNpcThought() == NPCTHOUGHT::GOHOME)
	{
		_npc->ChangeState(new NpcMove(_npc));
	}
}

void NpcIdle::Exit()
{

}

//MOVE==========================
void NpcMove::Enter()
{
	_state = "Move";
}

void NpcMove::Update()
{
	//여기서 POS_ENTER가 나올일은 없다! 입장한 이후로 ENTER에서 IDLE이 될일은 없음
	//도착했으면 IDLE로 바꿔줘야함
	
	//해당 좌표에 도착했으면 IDLE로 바꿔줘라
	if (_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_WINDOW)
	{
		_npc->ChangeState(new NpcIdle(_npc)); //IDLE 로 바꿔줘
	}
	if (_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_STAND1 ||
		_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_STAND2 ||
		_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_STAND3 ||
		_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_STAND4)
	{
		_npc->ChangeState(new NpcIdle(_npc)); 
	}
	if (_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_CHECKSTAND)
	{
		_npc->ChangeState(new NpcIdle(_npc));
	}
	if (_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_DOOR) //문앞에 있으면
	{
		_npc->ChangeState(new NpcHome(_npc)); //집으로 가..
	}
}

void NpcMove::Exit()
{
}

//HOME==========================
void NpcHome::Enter()
{
	_state = "Home";
}

void NpcHome::Update()
{
	if (_npc->GetNpcNowPosition() == NPCNOWPOSITION::POS_DOOR) //나가는문 앞인데
	{
		if (_npc->GetNpcThought() == NPCTHOUGHT::GOHOME) //집에 가고싶어하면
		{
			_npc->SetIsActive(false); //이렇게 해두면 매니저가 지움

		}
	}
}

void NpcHome::Exit()
{
}
