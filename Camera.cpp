#include "stdafx.h"
#include "Camera.h"
#include <math.h>

HRESULT Camera::init()
{
	UpdateMatrix();

	return S_OK;
}

void Camera::Update()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_pos += Vector2(-_speed, 0.f) * TIMEMANAGER->getElapsedTime();
		UpdateMatrix();
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_pos += Vector2(_speed, 0.f) * TIMEMANAGER->getElapsedTime();
		UpdateMatrix();
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_pos += Vector2(0.f, -_speed) * TIMEMANAGER->getElapsedTime();
		UpdateMatrix();

	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_pos += Vector2(0.f, _speed) * TIMEMANAGER->getElapsedTime();
		UpdateMatrix();
	}

	if (!_isMoving)
	{
		UpdateMatrix();
		return;
	}

	_lerpCount += 1.0f / 60 / _moveTime;
	_pos = Vector2::Lerp(_startPos, _endPos, _lerpCount);

	if (_lerpCount >= 1)
	{
		_isMoving = false;
		_lerpCount = 0;
	}

	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	_matrix = Matrix3x2F::Identity();
	//_matrix = _matrix * Matrix3x2F::Scale(SizeF(_scale.x, _scale.y));
	//_matrix = _matrix * Matrix3x2F::Translation(-_pos.x,-_pos.y);

	_matrix = _matrix * _scaleMatrix * Matrix3x2F::Translation(-_pos.x, -_pos.y);
}

void Camera::SetPosition(Vector2 pos)
{
	_pos.x = pos.x - WINSIZEX / 2;
	_pos.y = pos.y - WINSIZEY / 2;

	if (_pos.x <= 0) _pos.x = 0;
	if (_pos.y <= 0) _pos.y = 0;

	if (_pos.x + WINSIZEX >= GRAPHICMANAGER->FindImage("bg")->GetWidth()) _pos.x = GRAPHICMANAGER->FindImage("bg")->GetWidth() - WINSIZEX;
	if (_pos.y + WINSIZEY >= GRAPHICMANAGER->FindImage("bg")->GetHeight()) _pos.y = GRAPHICMANAGER->FindImage("bg")->GetHeight() - WINSIZEY;
	UpdateMatrix();
}

void Camera::SetScale(Vector2 scale)
{
	_scale += scale;
	float a = Clamp(_scale.x, 0.01f, 2.5f);

	_scale = Vector2(a, a);

	_scaleMatrix = Matrix3x2F::Scale(_scale.x, _scale.y, Point2F(WINSIZEX / 2, WINSIZEY / 2));

	UpdateMatrix();
}

void Camera::MoveTo(Vector2 endPos, float time)
{
	_startPos = _pos;
	//_endPos = endPos;
	_endPos.x = endPos.x - WINSIZEX / 2;
	_endPos.y = endPos.y - WINSIZEY / 2;
	_moveTime = time;
	_isMoving = true;
}

bool Camera::IsMoving()
{
	if (_isMoving) return true;
	else return false;
}
