#pragma once
#include "Object.h"

class PlayerState;

enum class CursorWhere
{
	Left,
	Right,
	None,
};

class Player : public Object
{
private:
	Sprite* _sprite;
	PhysicsBody* _physics;

	Object* _body;
	Object* _legs;
	Object* _arms;

	shared_ptr<PlayerState> _state;

	CursorWhere _cw;

	float _armsAngle;

private:
	void DirectionSprite();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeState(shared_ptr<PlayerState> state);

	Object* GetBody() { return _body; }
	Object* GetLegs() { return _legs; }
	Object* GetArms() { return _arms; }

	//PlayerState* GetState() { return _state; }

	shared_ptr<PlayerState> GetState() { return _state; }
	PlayerState* GetStateToPointer() { return _state.get(); }

	PhysicsBody* GetPhysicsBody() { return _physics; }

	CursorWhere GetCursorWhere() { return _cw; }
};

