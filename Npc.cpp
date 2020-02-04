#include "stdafx.h"
#include "Npc.h"
#include "NpcShopState.h"

void Npc::Init(string imgkey, Vector2 pos)
{
	Object::Init();

	_tag = "Npc";

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName(imgkey);

	_npcShopState = new NpcIdle(this);
	_npcShopState->Enter();

	
	_trans->SetPos(pos.x, pos.y); //문 밖에 생성
	_trans->SetScale(Vector2(
		//GRAPHICMANAGER->FindImage(imgkey)->GetFrameWidth()+15,
		//GRAPHICMANAGER->FindImage(imgkey)->GetFrameHeight()+15));
		GRAPHICMANAGER->FindImage(imgkey)->GetFrameWidth(),
		GRAPHICMANAGER->FindImage(imgkey)->GetFrameHeight()));

	_sprite->SetPosition(_trans->GetPos());
	_timer = 0;

	_isAstarOn = true;	//astar 받아야하는 상태인지

	_npcThought = NPCTHOUGHT::WINDOW;
	_npcNowPosition = NPCNOWPOSITION::POS_ENTER;
}

void Npc::Release()
{
	Object::Release();
}

void Npc::Update()
{

	Object::Update();
	//위로 움직이라고 명령 중
	//if (_trans->GetPos() >= Vector2(392, 500))
	//_trans->SetPos(Vector2(_trans->GetPos()+Vector2::up));


	//Astar 용 함수
	//SetPath(list<Vector2> lpath);
	Move();

	//npc 그림 띄우기
	_sprite->SetPosition(_trans->GetPos()); 

	_npcShopState->Update();

}

void Npc::Render()
{
	Object::Render();

	//이거 안하면 자꾸 정체불명의 동그라미가 엔피씨처럼 움직임.. erase할때 false 해줌
	/*if (_isActive)
	{
		if(SCENEMANAGER->GetNowScene()->GetName() == )
		GRAPHICMANAGER->DrawEllipse(
			_trans->GetPos().x, 
			_trans->GetPos().y, 
			_trans->GetScale().x / 2, 
			_trans->GetScale().y / 2);
	}*/

	wchar_t buffer[128];
	swprintf(buffer, 128, L"x: %1.f, y:%1.f", _trans->GetPos().x , _trans->GetPos().y);
	GRAPHICMANAGER->Text(Vector2(_trans->GetPos().x - CAMERA->GetPosition().x, _trans->GetPos().y - CAMERA->GetPosition().y), buffer, 20, 500, 300, ColorF::White);
}

void Npc::SetPath(list<Vector2> lpath)
{
	this->_lPath.clear();
	this->_lPath = lpath;
}

void Npc::ChangeState(NpcShopState* state)
{
	_npcShopState->Exit();
	_npcShopState = state;
	_npcShopState->Enter();

}

void Npc::Move()
{
	if (_lPath.size())
	{
		if (!_isAstarOn) //갈곳이 있으면 false 상태
		{

			Vector2 a = *_lPath.begin() - _trans->GetPos(); // 가야할위치에서 내위치를 빼면, 가야되는 다음 노드가 나옴
			float b = Vector2::GetAngle(_trans->GetPos(), *_lPath.begin());

			_trans->SetPos(_trans->GetPos() + Vector2(cosf(b), -sinf(b)) * 50 * TIMEMANAGER->getElapsedTime());

			if ((int)Vector2::Distance(*_lPath.begin(), _trans->GetPos()) < (int)2)//조건 느슨하게 예외처리 해주는 부분
				_lPath.pop_front(); //가장 첫번째 목적지 지우기, 다음 노드를 넣기 위해		}
		}
	}
	else //갈곳이 없으면 true 만들어
	{
		_timer += TIMEMANAGER->getElapsedTime();
		if (_timer > 2)
		{
			_isAstarOn = true;
			_timer = 0;
		}
	}
}


