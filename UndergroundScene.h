#pragma once
#include "Scene.h"

class Player;
class Tile;
class ProgressBar;

class UndergroundScene : public Scene
{
private:
	Player* _player;
	vector<Tile*> _vTiles;
	bool _isShowRect;
	ProgressBar* _bar;
	float current, max;

private:
	void MapLoad();
	void AddImage();
	void DirectorySearch(string folderPath, int maxFrameX = 1, int maxFrameY = 1);

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<Tile*> GetTiles() { return _vTiles; }
};

