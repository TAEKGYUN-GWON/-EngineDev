#include "stdafx.h"
#include "EnemyState.h"
//#include "Hp.h"
//#include "SlimeEnemy.h"
//#include "GolemEnemy.h"
//#include "MintPotEnemy.h"
//#include "Boss.h"
//
//
//
//EnemyIdle* EnemyIdle::instance;
//EnemyMove* EnemyMove::instance;
//EnemyAttack* EnemyAttack::instance;
//EnemyHit* EnemyHit::instance;
//EnemyDead* EnemyDead::instance;
//
////hp가 0이면 죽어라
//
//
//void EnemyBasic::Update(Enemy* _sEnemy)
//{
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	if (_sEnemy->GetAtk()) SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//}
//
////■■■■■■■■■■■■ Idle ■■■■■■■■■■■■■■
//EnemyIdle* EnemyIdle::GetInstance()
//{
//
//	//instance가 null이면 
//	if (instance == nullptr)
//	{
//		//enemy상태는 idle
//		instance = new EnemyIdle();
//	}
//	//instance = new EnemyIdle(); 라고 해줬으니까 EnemyIdle로 들어감
//	//위에 state->Update(this); 걸어줬으니까 Idle instance를 실행함
//	return instance;
//}
//
//void EnemyIdle::Init(Enemy* _sEnemy)
//{
//	//sprite 세팅?
//	cout << "왜 안들어와?" << endl;
//}
//
//void EnemyIdle::Update(Enemy* _sEnemy)
//{
//	//if (KEYMANAGER->isOnceKeyDown('0'))
//		//hp 가 0이면
//	EnemyBasic::Update(_sEnemy);
//	Release(_sEnemy);
//	cout << "들어오냐?" << endl;
//
//}
//void EnemyIdle::Release(Enemy* _sEnemy)
//{
//	cout << "move로 가!!!" << endl;
//
//	//if 플레이어가 있으면
//	// else if 체력이 0 이면 죽어라!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	else
//		SetEnemyState(_sEnemy, EnemyMove::GetInstance());
//}
////■■■■■■■■■■■■ Move ■■■■■■■■■■■■■
//EnemyMove* EnemyMove::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyMove();
//	}
//
//	return new EnemyMove();
//}
//
//void EnemyMove::Init(Enemy* _sEnemy)
//{
//	cout << "move 들어옴?" << endl;
//	//a*? bool값조정.?
//	_sEnemy->SetMove(true);
//	timer = 0;
//}
//
//void EnemyMove::Update(Enemy* _sEnemy)
//{
//	EnemyBasic::Update(_sEnemy);
//
//	if (_sEnemy->GetMove())
//		_sEnemy->SetMove(false);
//	if (_sEnemy->GetPath().size())
//	{
//		Vector2 dir = *_sEnemy->GetPath().begin() - _sEnemy->GetTrans()->GetPos();
//		Vector2 pos = _sEnemy->GetTrans()->GetPos();
//		_sEnemy->SetAngle(Vector2::GetAngle(pos, *_sEnemy->GetPath().begin()));
//		_sEnemy->GetTrans()->SetPos(pos + dir.Nomalized() * _sEnemy->GetSpeed() * TIMEMANAGER->getElapsedTime());
//	}
//	_sEnemy->GetPhysics()->SetBodyPosition();
//	//cout << "여기는 무브 오예 두둠칫" << endl;
//	//loat a = RND->getFloat(10000000);
//	//if(a<30)
//	timer += TIMEMANAGER->getElapsedTime();
//	if (timer > 3)
//		Release(_sEnemy);
//
//}
//
//void EnemyMove::Release(Enemy* _sEnemy)
//{
//
//	//if 범위에 플레이어가 있으면 공격하고
//	//SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//	// else if 범위에 플레이어가 없으면 다시 무브
//	//SetEnemyState(_sEnemy, EnemyMove::GetInstance());
//	cout << "다시 무브?" << endl;
//	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
//	// else if 체력이 0 이면 죽어라!
//
//	//if (_sEnemy->GetHP()->IsDead())
//	//{
//	//	SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	//}
//	//else SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//}
////■■■■■■■■■■■ Attack ■■■■■■■■■■■■
//EnemyAttack* EnemyAttack::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyAttack();
//	}
//
//	return instance;
//}
//
//void EnemyAttack::Init(Enemy* _sEnemy)
//{
//
//	//cout << "공격 들어왔니?" << endl;
//}
//
//void EnemyAttack::Update(Enemy* _sEnemy)
//{
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	_sEnemy->Attack();
//	//cout << "여기는 공격!" << endl;
//
//	Release(_sEnemy);
//}
//
//void EnemyAttack::Release(Enemy* _sEnemy)
//{
//	_sEnemy->SetAtk(false);
//	//if 플레이어한테 맞으면 맞는 상태로 가라
//	SetEnemyState(_sEnemy, EnemyHit::GetInstance());
//	// else if 아니면 idle로 가라
//	//SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
//	// else if 체력이 0 이면 죽어라!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//}
////■■■■■■■■■■■■ Hit ■■■■■■■■■■■■■
//
//EnemyHit* EnemyHit::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyHit();
//	}
//
//	return instance;
//}
//
//void EnemyHit::Init(Enemy* _sEnemy)
//{
//	//cout << "여기는 맞았다고 하는 부분" << endl;
//}
//
//void EnemyHit::Update(Enemy* _sEnemy)
//{
//	EnemyBasic::Update(_sEnemy);
//	//cout << "플레이어한테 맞았나?" << endl;
//	Release(_sEnemy);
//}
//
//void EnemyHit::Release(Enemy* _sEnemy)
//{
//	// if 맞았으면 idle로 가라
//	// else if 안맞았으면 다시 때려라
//	// else if 체력이 0 이면 죽어라!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//
//}
////■■■■■■■■■■■■ Dead ■■■■■■■■■■■■
//
//EnemyDead* EnemyDead::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyDead();
//	}
//
//	return instance;
//}
//
//void EnemyDead::Init(Enemy* _sEnemy)
//{
//	//Item::CreateItem(_sEnemy->GetTrans()->GetPos());
//	//cout << "여기는 죽은 상태" << endl;
//}
//
//void EnemyDead::Update(Enemy* _sEnemy)
//{
//	//	cout << "죽었니?" << endl;
//	Release(_sEnemy);
//}
//
//void EnemyDead::Release(Enemy* _sEnemy)
//{
//	//if (_sEnemy->GetHP()->IsDead())
//	//cout << "죽었다 ㅠㅠ" << endl;
////	_sEnemy->Release();
//}
