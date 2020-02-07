#pragma once
#include "Object.h"

class Room : public Object
{
private:
	PhysicsBody* _physics;
	Room* _leftNode;
	Room* _rightNode;
	
public:

	virtual void Init();
	virtual void Update() { return; }

	PhysicsBody* GetPhysics() { return _physics; }
	void SetLeftNode(Room* node) { _leftNode = node; }
	void SetRightNode(Room* node) { _rightNode = node; }
};

