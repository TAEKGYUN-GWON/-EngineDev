#pragma once
class ProgressBar
{
private:
	Vector2 pos;
	float _width;

	Graphic* _progressBar;			//게이지 앞에 이미지
	
public:
	ProgressBar() {};
	~ProgressBar() {};

	void Init(Vector2 pos, string key);
	void Release();
	void Update();
	void Render();

	void SetGauge(float currentGauge, float maxGauge);
	
	void SetPos(Vector2 pos) { this->pos = pos; }
};

