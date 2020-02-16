#pragma once
#include "Object.h"
#include "Probe.h"
#define MAP_MAX_WIDTH 5000
#define MAP_MAX_HEIGHT 3000

struct RoomObjectInfo
{
	int some;
	Vector2 pos;
	RoomObjectInfo(int some, Vector2 pos) { this->some = some; this->pos = pos; }
	RoomObjectInfo(Vector2 pos) { this->some = 1; this->pos = pos; }

};

class Room : public Object
{
public:
	typedef multimap<string, RoomObjectInfo>::iterator mROIter;
private:
	PhysicsBody* _physics;
	bool _isMainRoom;
	bool _isSubRoom;
	bool _isHubForBossRoom;
	multimap<string, RoomObjectInfo> _roomObjects;

public:
	virtual void Init();
	virtual void Update();

	PhysicsBody* GetPhysics() { return _physics; }

	bool GetIsMainRoom() { return _isMainRoom; }
	bool GetIsSubRoom() { return _isSubRoom; }
	bool GetHubForBossRoom() { return _isHubForBossRoom; }
	void SetIsMainRoom(bool active) { _isMainRoom = active; }
	void SetIsSubRoom(bool active) { _isSubRoom = active; }
	void SetHubForBossRoom(bool active) { _isHubForBossRoom = active; }
	void SetObject();

	multimap<string, RoomObjectInfo> GetRoomObjects() { return _roomObjects; }

};