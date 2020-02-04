#pragma once
#include "Boss.h"
#include "BossRoom.h"

//enum class HANDATK
//{
//	ON,
//	OFF
//};
enum class HANDSTATE
{
	SHADOW,
	HAND,
	END
};


class BossHand : public Object
{
protected:
	Sprite* _sprite;
	PhysicsBody* _physics;

	BossState* _Bstate;	//필요한가?

	Boss* _boss;
	Player* _player;
	//HANDATK Hatk;
	HANDSTATE _state;

	float _angle;
	float _speed;
	float timer = 0;
	int _count = 0;
	bool changeImg;

	Vector2 _target;
	//int changeImg; //보스에? 그림자에서 손으로 이동시?
public:
	BossHand();
	~BossHand();

	void Init();
	void Update();
	void Render();
	void Release();
	void Attack();

	PhysicsBody* GetPhysics() { return _physics; }
	Sprite* GetSprite() { return _sprite; }
	Player* GetPlayer() { return _player; }
	Boss* GetBoss() { return _boss; }

	void SetPlayer(Player* player) { _player = player; }

	BossState* GetState() { return _Bstate; }
	//void SetState(BossState* state);
	void SetTarget(Vector2 target) { _target = target; }
};


