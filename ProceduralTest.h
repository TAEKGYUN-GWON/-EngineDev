#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Room.h"
#define CREATE_ROOM_MAX 150
#define SELECT_ROOM 40

#define TILE
class ProceduralTest : public Scene
{
private:
	vector<Tile*> tiles;
	vector<Room*> rooms;
	vector<Room*> selRooms;
	Room* currentRoom;
	float maxY;
	float timer;
	bool endPush;
	bool endCreate;
	bool startDel;
	int count;
	
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
	void CreateRoom();
	void PushRoom();
	void SelRoom();
	void DelRoom();
	void SetTile();
};

