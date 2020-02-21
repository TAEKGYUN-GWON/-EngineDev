#pragma once
#include "Object.h"

class PlayerState;

typedef enum class Direction
{
	Left = 180,
	Down = 270,
	Right = 0,
	Up = 90,
}Dir;

enum class CursorWhere : byte
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
	PhysicsBody* _floorPhysics;

	Object* _body;
	Object* _legs;
	Object* _arms;

	Object* _judgingFloor;

	shared_ptr<PlayerState> _state;

	CursorWhere _cw;
	Dir _dir;

	float _armsAngle;
	float _slopAngle;
	float _distance;

	bool _isLadderCol;

	Vector2 _ladderPos;


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
	Object* GetJudgingFloor() { return _judgingFloor; }

	//PlayerState* GetState() { return _state; }

	shared_ptr<PlayerState> GetState() { return _state; }
	PlayerState* GetStateToPointer() { return _state.get(); }

	Sprite* GetSprite() { return _sprite; }
	PhysicsBody* GetPhysicsBody() { return _physics; }

	void SetSlopAngle(float angle) { _slopAngle = angle; }
	void SetDirection(Dir dir) { _dir = dir; }

	float GetSlopAngle() { return _slopAngle; }
	CursorWhere GetCursorWhere() { return _cw; }
	Direction GetDirection() { return _dir; }

	void SetIsLadderCollider(bool isCol) { _isLadderCol = isCol; }
	bool GetIsLadderCollider() { return _isLadderCol; }

	void SetLadderPosition(Vector2 pos) { _ladderPos = pos; }
	Vector2 GetLadderPosition() { return _ladderPos; }
};

