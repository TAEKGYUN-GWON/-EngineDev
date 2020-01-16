#pragma once
#include "Component.h"
#include"Matrix3x3.h"
class Matrix3x3;

class Transform : public Component
{
private:
	
	float _rotate;
	RECT _rc;

	Matrix3x3 scaleMatrix;
	Matrix3x3 rotateMatrix;
	Matrix3x3 translateMatrix;
	Matrix3x3 localToWorldMatrix;

	void UpdateMatrix();

public:
	typedef Component super;
	Vector2 pos;
	Vector2 bottomPos;
	Vector2 scale;
	Transform();

	virtual void Init() override;

	virtual void Update() override;

	//Vector2 타입 좌표 가져오기
	inline Vector2 GetPos() { return pos; }

	Vector2 GetWorldPosition();

	//Vector2 타입 사이즈 가져오기
	inline Vector2 GetScale() { return scale; }


	//디그리 값으로 회전값 가져오기
	inline float GetRotateDegree() { return _rotate * RadToDeg; }

	//라디안 값으로 회전값 가져오기
	inline float GetRotateRadian() { return _rotate; }

	//Vector2 타입으로 좌표 설정하기
	inline void SetPos(Vector2 pos) { this->pos = pos; }

	//float 타입으로 좌표 설정하기
	inline void SetPos(float x, float y) { pos = Vector2(x, y); }

	void SetWorldPos(Vector2 pos);

	//Vector2 타입으로 사이즈 설정하기
	inline void SetScale(Vector2 scale) { this->scale = scale; }

	//float 타입으로 사이즈 설정하기
	inline void SetScale(float w, float h) { scale = Vector2(w, h); }

	//라디안값으로 회전값 세팅
	inline void SetRotateToRadian(float rotate) { _rotate = rotate; }

	//디그리 값으로 회전값 세팅
	inline void SetRotateToDegree(float rotate) { _rotate = rotate * RadToDeg; }

	inline RECT GetRect() { return _rc; }

	inline void SetRect(RECT rc) { _rc = rc; }

	Matrix3x3 GetLocalToWorldMatrix() { return localToWorldMatrix; };

	D2D_MATRIX_3X2_F GetLocalToWorldMatrixTo_D2D_MATRIX() { return localToWorldMatrix.To_D2D1_Matrix_3x2_F(); };

	void SetRect();
};

