#pragma once
#include "Object.h"
#include<queue>

class Bullet : public Object
{
private:
	Object* _owner;
	Sprite* _sprite;
	PhysicsBody* _physics;
	float _speed;
	//오브젝트풀 변수로....
	bool _isColision;
	int _atk;

public:
	void Init(string imgKey, string tag, string name, Object* obj,int atk);
	virtual void Update(); //move
	void Fire(Vector2 pos, float angle, float speed);	
	void Move(); 
	Object* GetOwner() { return _owner; }
	void SetOwner(Object* obj) { _owner = obj; }
	Sprite* GetSprite() { return _sprite; }
	bool GetCollision() { return _isColision; }
	void SetCollision(bool active) { _isColision = active; }
	int GetAttackPoint() { return _atk; }
};

//■■■■■■■■■ bullet objpool ■■■■■■■■■■■■■
class BulletObjPool
{
	priority_queue<Bullet*> pool;
	//queue<Object*> pool;
	vector<Bullet*> ActivePool;
public:
	BulletObjPool();
	~BulletObjPool();
	void InssertPool(int num);
	void InssertActiveObject();

	inline Bullet* GetPoolObject() { return pool.top(); }
	inline Bullet* GetActivePoolObject(int num) { return ActivePool[num]; }
	inline int GetPoolSize() { return pool.size(); }
	inline int GetActivePoolSize() { return ActivePool.size(); }
	inline priority_queue<Bullet*> GetPool() { return pool; }
	inline vector<Bullet*> GetActivePool() { return ActivePool; }
	void Init(int size, string imgKey, string tag, string name, Object* obj = nullptr, int atk = 0);
};
