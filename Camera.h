#pragma once
#include "Component.h"

class Camera : public Component
{
private:
	D2D1_MATRIX_3X2_F	_matrix;

	Matrix3x2F			_scaleMatrix;

	Vector2				_scale;
	Vector2				_pos;
	Vector2				_startPos;
	Vector2				_endPos;

	Vector2				_shakeUpPos;
	Vector2				__shakeDownPos;

	float				_angle;
	float				_speed;
	float				_lerpCount;
	float				_moveTime;
	float				_prevDistance;
	bool				_isMoving;
	bool				_isMain;

public:
	Camera()
	{
		_scaleMatrix = Matrix3x2F::Identity();
		_scale = Vector2(1, 1);
		_pos = Vector2().zero;
		_angle = 0.0f;
		_speed = 300.f;
		_lerpCount = 0;
		_isMoving = false;
	};
	~Camera() {};

	HRESULT init();
	void Update();
	//void release();

	void UpdateMatrix();

	void SetScale(Vector2 scale);// { _scale = scale; };
	//void SetAngle(float angle) { _angle = angle; };
	void SetPosition(Vector2 pos);
	void SetMainCamera(bool active) { _isMain = active; }
	void MoveTo(Vector2 endPos, float time);

	Vector2 GetPosition() { return _pos; }
	Vector2 GetScale() { return _scale; }
	bool IsMoving();

	D2D1_MATRIX_3X2_F GetMatrix() { return _matrix; }
};

