#include "stdafx.h"
#include "Bullet.h"
#include "BulletScript.h"

void Bullet::Init(string imgKey, string tag, string name, Object* obj, int atk)
{
	_tag = tag;
	_name = name;
	_owner = obj;
	_sprite = AddComponent<Sprite>();
	_atk = atk;
	 AddComponent<BulletScript>();
	_sprite->Init(true, true);
	_sprite->SetImgName(imgKey);
	_trans->scale = Vector2(_sprite->GetGraphic()->GetFrameWidth(),
		_sprite->GetGraphic()->GetFrameHeight());

	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f, 1.0f, 0.0f, true, true);

	_physics->GetBody()->SetFixedRotation(true);
	_physics->GetBody()->SetActive(false);
	_isActive = false;
}

void Bullet::Update()
{
	if (!_isActive)return;
	Object::Update();

	Move();
	if (_name != "Arrow") _trans->pos = _physics->GetBodyPosition();
}

void Bullet::Fire(Vector2 pos, float angle, float speed)
{
	_speed = speed;
	_trans->pos = pos;
	_physics->SetBodyPosition();
	_trans->SetRotateToRadian(angle + (PI / 2));
	
	_physics->SetBodyActive(true);
	_sprite->SetPosition(_trans->GetPos());
	_isActive = true;
	
	_physics->GetBody()->SetTransform(b2Vec2(_physics->GetBody()->GetPosition().x, _physics->GetBody()->GetPosition().y), _trans->GetRotateRadian());
}

void Bullet::Move()
{
	if (!_isActive)return;
	_physics->GetBody()->SetLinearVelocity(b2Vec2(cosf(_trans->GetRotateRadian() - (PI / 2)), -sinf(_trans->GetRotateRadian() - (PI / 2)))
		* _speed * TIMEMANAGER->getElapsedTime());

	if (_owner != nullptr)
	{
		if (Vector2::Distance(_trans->GetPos(), _owner->GetTrans()->GetPos()) > 1300)
		{
			_isActive = false;
		}
	}
	_sprite->SetPosition(_trans->GetPos());
}


BulletObjPool::BulletObjPool()
{
}

BulletObjPool::~BulletObjPool()
{
}

void BulletObjPool::InssertPool(int num)
{
	ActivePool[num]->SetIsActive(false);
	ActivePool[num]->GetComponent<PhysicsBody>()->SetBodyActive(false);
	pool.push(ActivePool[num]);
	ActivePool.erase(ActivePool.begin() + num);
}


void BulletObjPool::InssertActiveObject()
{
	pool.top()->SetIsActive(true);
	pool.top()->GetComponent<PhysicsBody>()->SetBodyActive(true);
	ActivePool.push_back(pool.top());
	pool.pop();
}

void BulletObjPool::Init(int size, string imgKey, string tag, string name, Object* obj, int atk)
{
	ActivePool.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Bullet* newObj = Object::CreateObject<Bullet>();
		newObj->Init(imgKey, tag, name,obj, atk);
		newObj->SetIsActive(false);
		pool.push(newObj);

	}
}


