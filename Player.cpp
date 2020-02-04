#include "stdafx.h"
#include "Player.h"
#include "Inventory.h"
#include "PlayerState.h"
#include "PlayerIdle.h"
#include "ETCS.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Object::Init();

	GRAPHICMANAGER->AddFrameImage("will_dungeon", L"resource/img/Player/will_dungeon.png", 10, 13);
	GRAPHICMANAGER->AddFrameImage("will_sword", L"resource/img/Player/will_sword.png", 11, 4);
	GRAPHICMANAGER->AddFrameImage("will_bow", L"resource/img/Player/will_bow.png", 9, 4);
	GRAPHICMANAGER->AddImage("spark", L"spark.png");
	GRAPHICMANAGER->AddFrameImage("arrow_left", L"resource/img/Player/arrow_left.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage("arrow_up", L"resource/img/Player/arrow_up.png", 1, 1);
	GRAPHICMANAGER->AddFrameImage("arrow_down", L"resource/img/Player/arrow_down.png", 1, 1);

	_tag = "Player";
	_name = "Will";

	_trans->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	_trans->SetScale(Vector2(36, 25));

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("will_dungeon");
	_sprite->SetPosition(_trans->GetPos() + Vector2(0, -14));

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f,0.3f);
	_physics->GetBody()->SetFixedRotation(true);

	_ability = new Ability(100, 100, 10);

	_speed = 300.0f;

	_dir = Dir::Down;
	_atkType = AttackType::Sword;

	_inven = new Inventory;
	_inven->Init();

	_state = new PlayerIdle(this);
	_state->Enter();

	//_particleMgr = new ParticleManager;
	//_particleMgr->Init(10, ParticleType::TRIANGLE, Vector2(), Vector2(10, 10),"spark");
	//_particleMgr->SetMinAngle(PI / 4);
	//_particleMgr->SetMaxAngle(3 * PI / 4);
	//_particleMgr->SetMinSpeed(150.0f);
	//_particleMgr->SetMaxSpeed(200.0f);

	_isInter = false;

	_pool = new BulletObjPool;
	_pool->Init(20, "arrow_down", "Arrow", "Arrow", this, 5);
}

void Player::Update()
{
	_inven->Update();
	if (_inven->GetActive()) return;

	if (KEYMANAGER->isStayKeyDown('P')) _ability->DamageHP(10);
	else if (KEYMANAGER->isStayKeyDown('O')) _ability->HealHP(10);

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		CAMERA->ShakingSetting(CAMERA->GetPosition(), 0.3f, 2.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_isInter = !_isInter;
	}

	if (_state->GetState() != "Attack")
	{
		if (KEYMANAGER->isOnceKeyDown('Z')) _atkType = (AttackType)(((int)_atkType + 1) % 2);
	}

	Object:: Update();

	_state->Update();

	ReturnBullets();
	
	_sprite->SetPosition(_trans->GetPos() + Vector2(0, -14));
}

void Player::Render()
{
	Object::Render();

	wchar_t buffer[128];
	swprintf(buffer, 128, L"%1.f / %1.f", _ability->GetCurrentHP(), _ability->GetMaxHP());
	GRAPHICMANAGER->Text(_trans->GetPos() + Vector2(-(_trans->GetScale().x + 10.0f), 22.f) - CAMERA->GetPosition(), buffer, 20, 90, 30, ColorF::LawnGreen, TextPivot::RIGHT_TOP);

	swprintf(buffer, 128, L"%1.f / %1.f", _trans->GetPos().x, _trans->GetPos().y);
	GRAPHICMANAGER->Text(_trans->GetPos() + Vector2(-(_trans->GetScale().x + 10.0f), 50.f) - CAMERA->GetPosition(), buffer, 20, 90, 30, ColorF::LawnGreen, TextPivot::RIGHT_TOP);

	if (_ability->IsDead()) GRAPHICMANAGER->Text(_trans->GetPos() + Vector2(-(_trans->GetScale().x - (_trans->GetScale().x * 0.5f) + 4.0f), -52.f) - CAMERA->GetPosition(), L"Dead", 20, 100, 30, ColorF::Red);

	int a = (int)_dir;
	Vector2 test((_trans->GetPos() + Vector2(0, -10)) + Vector2(cosf(a * 45.0f * Deg2Rad), -sinf(a * 45.0f * Deg2Rad)) * 50);
	GRAPHICMANAGER->DrawLine(_trans->GetPos() + Vector2(0, -10) - CAMERA->GetPosition(), test - CAMERA->GetPosition(), ColorF::AntiqueWhite);

	char str[128];
	if(_atkType == AttackType::Sword) sprintf_s(str, "Attack Type : Sword\nState Type : %s", _state->GetState().c_str());
	else if (_atkType == AttackType::Bow) sprintf_s(str, "Attack Type : Bow\nState Type : %s", _state->GetState().c_str());

	GRAPHICMANAGER->DrawTextD2D(Vector2(WINSIZEX - 230, 2), str, 20, 200, 70, ColorF::AntiqueWhite, TextPivot::RIGHT_BOTTOM);
}

void Player::Release()
{
	_inven->Release();
	Object::Release();
}

void Player::ReturnBullets()
{
	// 무언가와 충돌했을 때
	for (int i = 0; i < _pool->GetActivePoolSize(); i++)
	{
		if (_pool->GetActivePool()[i]->GetCollision())
		{
			_pool->GetActivePool()[i]->SetCollision(false);
			_pool->InssertPool(i);
			break;
		}
	}

	//if(_pool->GetActivePoolSize()) _particleMgr->SetPos(_pool->GetActivePool()[0]->GetTrans()->GetPos());
	//_particleMgr->Update();

	// 그 무엇과도 충돌하지 않았을 때
	for (int i = 0; i < _pool->GetActivePoolSize(); i++)
	{
		if (!_pool->GetActivePool()[i]->GetIsActive())
		{
			_pool->GetActivePool()[i]->GetComponent<PhysicsBody>()->GetBody()->SetActive(false);
			_pool->InssertPool(i);
		}
	}
}

void Player::ChangeState(PlayerState* state)
{
	_state->Exit();
	_state = state;
	_state->Enter();
}

void Player::SetTiles(vector<Tile*> tiles, int maxX, int maxY)
{
	_tiles = tiles;
	_mapTileMax_X = maxX;
	_mapTileMax_Y = maxY;
	int a;
}
