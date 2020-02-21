#pragma once

class ProgressBar
{
private:
	Graphic* _img;

public:
	void Init();
	void Release();
	void Update();
	void Render(string imgKey, Vector2 pos, Vector2 scale, float angle, float alpha, bool isCameraEffect);
};

