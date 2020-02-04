#include "stdafx.h"
#include "Enemy.h"
#include "Ability.h"
#include "Bullet.h"
#include "Item.h"
#include "EnemyScript.h"
#include "ETCS.h"
#include "Player.h"
#include "Inventory.h"
//#include "Player.h"
//전방선언 같은 거...?



EnemyIdle* EnemyIdle::instance;
EnemyMove* EnemyMove::instance;
EnemyAttack* EnemyAttack::instance;
EnemyHit* EnemyHit::instance;
EnemyDead* EnemyDead::instance;


Enemy::Enemy()
{

	SetState(EnemyIdle::GetInstance());

	//cout << "생성자부분 아이들" << endl;
	
}

Enemy::~Enemy()
{
}
//처음 에너미 상태 세팅부분 따로 Enemy::Init()에서 세팅 안해줌
void Enemy::SetState(EnemyBasic* state)
{

	state->Init(this);
	if (dynamic_cast<EnemyMove*>(this->state) || dynamic_cast<EnemyAttack*>(this->state)) delete this->state;
	this->state = state;
}

void Enemy::Init()
{
	Object::Init();

	_tag = "enemy";
	maxFrameX = 0;
	frameY = 0;
	_sprite = AddComponent<Sprite>();
	_sprite->SetMaxFrameX(maxFrameX);
	_sprite->SetFrameY(frameY);
	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");

	AddComponent<EnemyScript>();
}

void Enemy::Update()
{
	Object::Update();
	
	 //이미지를 바꿔주는데 뭐...currentimg(y) 이런거?
	 //if (angle > (3 * PI) / 4 && angle < (5 * PI) / 4) _dir = DIRECTION::LEFT;
	 //if (angle > (4 * PI) / 4 && angle < (7 * PI) / 4) _dir = DIRECTION::RIGHT;
	 //if (angle > PI / 4 && angle < (3 * PI) / 4) _dir = DIRECTION::TOP;
	 //if (angle > PI / 4 && angle < (7 * PI) / 4) _dir = DIRECTION::BOTTOM;

	//상태 Update 걸어줌
	state->Update(this);

	if (_angle >= 45 * DegToRad && _angle < 135 * DegToRad)_dir = DIRECTION::TOP;
	else if (_angle >= 135 * DegToRad && _angle < 180 * DegToRad)_dir = DIRECTION::LEFT;
	else if (_angle <= -135 * DegToRad && _angle > -180 * DegToRad)_dir = DIRECTION::LEFT;

	else if (_angle <= -45 * DegToRad && _angle > -135 * DegToRad)_dir = DIRECTION::BOTTOM;

	else if (_angle <= 0 * DegToRad && _angle > -45 * DegToRad)_dir = DIRECTION::RIGHT;
	else if (_angle >= 0 * DegToRad && _angle < 45 * DegToRad)_dir = DIRECTION::RIGHT;


	if (!dynamic_cast<EnemyAttack*>(state))
	{
		if (GetPath().size())
		{
			if (_changePos)
			{
				_changePos = false;
				_angle = (int)  Vector2::GetAngle(_trans->GetPos(), *_path.begin());
			}
			Vector2 dir = *_path.begin() - _trans->GetPos();
			Vector2 pos = _trans->GetPos();
			_trans->SetPos(pos + dir.Nomalized() * _speed * TIMEMANAGER->getElapsedTime());

			if (Vector2::Distance(*_path.begin(), _trans->GetPos()) <= 15.5f)
			{
				_changePos = true;
				_path.erase(_path.begin());
			}
		}
		switch (_dir)
		{
		case DIRECTION::LEFT:
			_sprite->SetFrameY(0);
			break;
		case DIRECTION::RIGHT:
			_sprite->SetFrameY(1);
			break;
		case DIRECTION::TOP:
			_sprite->SetFrameY(2);
			break;
		case DIRECTION::BOTTOM:
			_sprite->SetFrameY(3);
			break;
		}
	}
	_physics->SetBodyPosition();


	if (GetHP()->IsDead())
	{
		SetState(EnemyDead::GetInstance());
	}

}

void Enemy::Render()
{
	Object::Render();
	wchar_t buffer[128];
	swprintf(buffer, 128, L"Angle : %f", Vector2::GetAngle(_trans->GetPos(), _player->GetTrans()->GetPos()) * Rad2Deg);
	GRAPHICMANAGER->Text(_trans->GetPos() - Vector2::down * 20, buffer, 20, 300, 50, ColorF::Azure, TextPivot::CENTER, L"맑은고딕", true);

}

void Enemy::SetPath(list<Vector2> _path)
{
	this->_path.clear();
	this->_path = _path;
}




#include "SlimeEnemy.h"
#include "GolemEnemy.h"
#include "MintPotEnemy.h"

void EnemyBasic::Update(Enemy* _sEnemy)
{
	/*if (_sEnemy->GetHP()->IsDead())
	{
		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
	}*/
	if (_sEnemy->GetAtk()) SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
}

//■■■■■■■■■■■■ Idle ■■■■■■■■■■■■■■
EnemyIdle* EnemyIdle::GetInstance()
{

	//instance가 null이면 
	if (instance == nullptr)
	{
		//enemy상태는 idle
		instance = new EnemyIdle();
	}
	//instance = new EnemyIdle(); 라고 해줬으니까 EnemyIdle로 들어감
	//위에 state->Update(this); 걸어줬으니까 Idle instance를 실행함
	return instance;
}

void EnemyIdle::Init(Enemy* _sEnemy)
{
	//cout << "왜 안들어와?" << endl;
}

void EnemyIdle::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);
	Release(_sEnemy);
	//cout << "들어오냐?" << endl;
}
void EnemyIdle::Release(Enemy* _sEnemy)
{
//	cout << "move로 가!!!" << endl;
	//  체력이 0 이면 죽어라
	
	
		SetEnemyState(_sEnemy, EnemyMove::GetInstance());
}
//■■■■■■■■■■■■ Move ■■■■■■■■■■■■■
EnemyMove* EnemyMove::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyMove();
	}

	return new EnemyMove();
}

void EnemyMove::Init(Enemy* _sEnemy)
{
	//cout << "move 들어옴?" << endl;
	_sEnemy->SetMove(true);
	timer = 0;
}

void EnemyMove::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);


	switch (_sEnemy->GetDir())
	{
	case DIRECTION::LEFT:
		_sEnemy->GetSprite()->SetFrameY(0);
		break;
	case DIRECTION::RIGHT:
		_sEnemy->GetSprite()->SetFrameY(1);
		break;
	case DIRECTION::TOP:
		_sEnemy->GetSprite()->SetFrameY(2);
		break;
	case DIRECTION::BOTTOM:
		_sEnemy->GetSprite()->SetFrameY(3);
		break;
	}
	
	//cout << "여기는 무브 오예 두둠칫" << endl;
	//loat a = RND->getFloat(10000000);
	//if(a<30)
	_sEnemy->SetMove(false);

	timer += TIMEMANAGER->getElapsedTime();

	if (timer >0.5f) {
		_sEnemy->SetMove(true);
		timer = 0;
	}

}

void EnemyMove::Release(Enemy* _sEnemy)
{

	//if 범위에 플레이어가 있으면 공격하고
	//SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
	// else if 범위에 플레이어가 없으면 다시 무브
	//SetEnemyState(_sEnemy, EnemyMove::GetInstance());
	//cout << "다시 무브?" << endl;
	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
	
}
//■■■■■■■■■■■ Attack ■■■■■■■■■■■■
EnemyAttack* EnemyAttack::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyAttack();
	}

	return new EnemyAttack();
}

void EnemyAttack::Init(Enemy* _sEnemy)
{
	//cout << "공격 들어왔니?" << endl;
}

void EnemyAttack::Update(Enemy* _sEnemy)
{
	
	if (_sEnemy->GetAtk())
	{
		_sEnemy->Attack();
		_sEnemy->SetAtk(false);
	}
	_sEnemy->SetAngle(Vector2::GetAngle(_sEnemy->GetTrans()->GetPos(), _sEnemy->GetPlayer()->GetTrans()->GetPos()));
	//cout << "여기는 공격!" << endl;
	if (_sEnemy->GetName() == "Golem")
	{
		if (_sEnemy->GetSprite()->GetCurrentFrameX() == 6) _sEnemy->Attack();
		if(_sEnemy->GetSprite()->GetCurrentFrameX() >= _sEnemy->GetSprite()->GetMaxFrameX())
			Release(_sEnemy);
	}
	//여기서 민트항아리 공격
	else if (_sEnemy->GetName() == "Pot")
	{
		if(_sEnemy->GetSprite()->GetCurrentFrameX() >= _sEnemy->GetSprite()->GetMaxFrameX())
			Release(_sEnemy);
	}
}

void EnemyAttack::Release(Enemy* _sEnemy)
{
	_sEnemy->AttackEnd();
	//if 플레이어한테 맞으면 맞는 상태로 가라
	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
	if (_sEnemy->GetName() == "Golem")
	{
		_sEnemy->GetSprite()->SetImgName("Golem");
	}
	if (_sEnemy->GetName() == "Pot")
	{
		_sEnemy->GetSprite()->SetImgName("enemyPot");
	}
}
//■■■■■■■■■■■■ Hit ■■■■■■■■■■■■■

EnemyHit* EnemyHit::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyHit();
	}

	return instance;
}

void EnemyHit::Init(Enemy* _sEnemy)
{
	//cout << "여기는 맞았다고 하는 부분" << endl;
}

void EnemyHit::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);
	//cout << "플레이어한테 맞았나?" << endl;
	Release(_sEnemy);
}

void EnemyHit::Release(Enemy* _sEnemy)
{
	// if 맞았으면 idle로 가라
	// else if 안맞았으면 다시 때려라
	// else if 체력이 0 이면 죽어라!
	

}
//■■■■■■■■■■■■ Dead ■■■■■■■■■■■■

EnemyDead* EnemyDead::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyDead();
	}

	return instance;
}

void EnemyDead::Init(Enemy* _sEnemy)
{

	
	//cout << "여기는 죽은 상태" << endl;
}

void EnemyDead::Update(Enemy* _sEnemy)
{
	//	cout << "죽었니?" << endl;
	Release(_sEnemy);
}

void EnemyDead::Release(Enemy* _sEnemy)
{
	

	//if (_sEnemy->GetHP()->IsDead())
	//cout << "죽었다 ㅠㅠ" << endl;
	_sEnemy->SetIsActive(false);
	if (SCENEMANAGER->GetNowScene()->GetName() == "BossRoom")return;
	Player* player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
	if (player->GetInventory()->GetInventorySize()>=20)return;

	int some = RND->getInt(3);
	//int some = 1;

	for (int i = 0; i < some; i++)
	{
		int rand =  RND->getInt(10);
		switch (rand)
		{
		case 0: Item::CreateItem<Vine>(_sEnemy->GetTrans()->GetPos()); break;
		case 1: Item::CreateItem<Crystal_Energy>(_sEnemy->GetTrans()->GetPos()); break;
		case 2: Item::CreateItem<amulet_ring>(_sEnemy->GetTrans()->GetPos()); break;
		case 3: Item::CreateItem<Treated_Wood>(_sEnemy->GetTrans()->GetPos()); break;
		case 4: Item::CreateItem<Broken_Sword>(_sEnemy->GetTrans()->GetPos()); break;
		case 5: Item::CreateItem<Energy_Crystal>(_sEnemy->GetTrans()->GetPos()); break;
		case 6: Item::CreateItem<Naja_Note>(_sEnemy->GetTrans()->GetPos()); break;
		case 7: Item::CreateItem<Reinforced_Steel_G>(_sEnemy->GetTrans()->GetPos()); break;
		case 8: Item::CreateItem<Golem_Core>(_sEnemy->GetTrans()->GetPos()); break;
		case 9: Item::CreateItem<Familiar_Egg>(_sEnemy->GetTrans()->GetPos()); break;
		case 10: Item::CreateItem<Reinforced_Steel_Y>(_sEnemy->GetTrans()->GetPos()); break;
		}
	}
}
