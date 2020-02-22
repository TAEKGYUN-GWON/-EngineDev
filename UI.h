#pragma once

class ProgressBar;
class Player;

class UI
{
private:
	Object* _statusbar;
	ProgressBar* _hpBar;
	Player* _player;
	Graphic* _pistolBg;
	vector<Graphic*> _pistol;

public:
	void Init();
	void Release();
	void Update();
	void Render();
};

