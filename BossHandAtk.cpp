#include "stdafx.h"
//#include "BossHandAtk.h"
//#include "BossIdle.h"
//#include "Player.h"
//
//void BossHandAtk::Enter()
//{
//	_Bstate = "Attack";
//	_obj = _boss->GetHand();
//	//_state = HANDSTATE::SHADOW;
//	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
//	_obj = Object::CreateObject<BossHand>();
//	_obj->GetTrans()->SetPos(_player->GetTrans()->GetPos());
//}
//
//void BossHandAtk::Update()
//{
//
////	if ()
//	timer += TIMEMANAGER->getElapsedTime();
//
//	if (timer >= 0.1f)
//	{
//		switch (_state)
//		{
//		case HANDSTATE::SHADOW:
//			//player 따라다님
//			//이ㅣㅁ지가 그림자임
//			//physic flase인상태
//			break;
//		case HANDSTATE::HAND:
//			//img 바꿔주기 손으로 
//			//physic true인상태
//			break;
//		case HANDSTATE::END:
//			//physic flase인상태
//			//아이들로 바꾸기
//			break;
//		}
//		timer = 0;
//		_count++;
//	}
//
//	//if (_count == rocks.size() && _state == ROCKATK::END)
//	//	_boss->SetState(new BossIdle(_boss));
//}
//
//void BossHandAtk::Exit()
//{
//}
