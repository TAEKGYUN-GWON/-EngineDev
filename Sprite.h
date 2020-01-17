#pragma once
#include"DrawComponent.h"

class Object;

class Sprite : public DrawComponent
{
private:
	bool _isFlipX;

	bool _isFrame;
	bool _isLoop;
	bool _isPlay;

	int _curFrameX;
	int _curFrameY;

	int _maxFrameX;

	float _count;
	float _FPS;
	float _strokeWidth;

	float _alpha;

	string _imgKey;
	Graphic* _graphic;

	ColorF::Enum _color;
	PIVOT _pivot;

public:
	Sprite();
	virtual void Init(BOOL isFrame = false, BOOL isLoop = false);
	virtual void Render();
	virtual void Update() override;

	inline void SetFlipX(bool value) { _isFlipX = value; }
	inline void SetFrameX(int frameX) { _curFrameX = frameX; }
	inline void SetFrameY(int frameY) { _curFrameY = frameY; }
	inline void SetFPS(float time) { _FPS = 1.0f / time; }
	inline void SetAlpha(float alpha) { _alpha = alpha; }

	inline string GetImgKey() { return _imgKey; }
	inline bool GetFlipX() { return _isFlipX; }
	inline float GetAlpha() { return _alpha; }

	void Start();
	void Stop();
	void Pause();
	void Resume();

	void SetImgName(string key);
	void SetMaxFrameX(int maxFrameX) { _maxFrameX = maxFrameX - 1; }
	inline void SetRectColor(ColorF::Enum color) { _color = color; }
	inline void SetStrokeWidth(float strokeWidth) { _strokeWidth = strokeWidth; }
	inline void SetPivot(PIVOT pivot) { _pivot = pivot; }

	bool IsFrameEnd();
	inline Graphic* GetGraphic() { return _graphic; }
};

