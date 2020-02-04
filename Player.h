#pragma once
#include "Object.h"
#include "Bullet.h"
//#include "ParticleManager.h"

class Ability;
class Inventory;
class PlayerState;

typedef enum class Direction
{
	Right = 0,
	Right_Up,
	Up,
	Left_Up,
	Left,
	Left_Down,
	Down,
	Right_Down,
}Dir;

enum class AttackType : byte
{
	Sword,
	Bow,
};

class Player : public Object
{
private:
	Inventory* _inven;
	Ability* _ability;
	Sprite* _sprite;
	PhysicsBody* _physics;

	PlayerState* _state;
	Direction _dir;
	AttackType _atkType;
	BulletObjPool* _pool;

	//ParticleManager* _particleMgr;
	vector<Tile*> _tiles;

	int _mapTileMax_X;
	int _mapTileMax_Y;


	float _speed;
	bool _isInter;

public:
	Player();
	~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void ReturnBullets();
	void ChangeState(PlayerState* state);
	void SetDirection(Direction dir) { _dir = dir; }
	void SetAttackType(AttackType type) { _atkType = type; }
	void SetIsInteraction(bool isTrue) { _isInter = isTrue; }

	void SetTiles(vector<Tile*> tiles, int maxX, int maxY);
	vector<Tile*> GetTiles() { return _tiles; }
	int GetMaxX() { return _mapTileMax_X; }
	int GetMaxY() { return _mapTileMax_Y; }

	bool GetIsInteraction() { return _isInter; }
	float GetSpeed() { return _speed; }
	Sprite* GetSprite() { return _sprite; }
	PhysicsBody* GetPhysics() { return _physics; }
	Inventory* GetInventory() { return _inven; }
	Direction GetDirection() { return _dir; }
	AttackType GetAttackType() { return _atkType; }
	Ability* GetAbility() { return _ability; }
	PlayerState* GetState() { return _state; }
	BulletObjPool* GetBulletPool() { return _pool; }
	//ParticleManager GetParticle() { return *_particleMgr; }
};

