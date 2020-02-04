#pragma once
#include "Enemy.h"

class GolemEnemy : public Enemy
{
protected:
	float _atkRange;
	Object* _lAtk;
	Object* _rAtk;
	Object* _tAtk;
	Object* _bAtk;
	vector<Object*> _atks;
	

	void AtkPosUpdate();
public:
	GolemEnemy();
	~GolemEnemy();
	int maxFrameX;
	int frameY;
	static float GetAtkRange() { return 100; }
	virtual void Init(Vector2 pos);
	virtual void Update();
	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void Release();
	virtual void Render();


	PhysicsBody* GetLeftAtk() {		return _lAtk->GetComponent<PhysicsBody>(); }
	PhysicsBody* GetRightAtk() {	return _rAtk->GetComponent<PhysicsBody>(); }
	PhysicsBody* GetTopAtk() {		return _tAtk->GetComponent<PhysicsBody>(); }
	PhysicsBody* GetBottomAtk() {	return _bAtk->GetComponent<PhysicsBody>(); }
};

