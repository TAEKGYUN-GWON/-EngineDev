#include "stdafx.h"
#include "Transform.h"

void Transform::UpdateMatrix()
{
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;

	rotateMatrix.m[0][0] = cos(_rotate*Deg2Rad);
	rotateMatrix.m[0][1] = -sin(_rotate*Deg2Rad);
	rotateMatrix.m[1][0] = sin(_rotate*Deg2Rad);
	rotateMatrix.m[1][1] = cos(_rotate*Deg2Rad);

	translateMatrix.m[2][0] = pos.x;
	translateMatrix.m[2][1] = pos.y;

	localToWorldMatrix = scaleMatrix * rotateMatrix * translateMatrix;

	Object* parent = _object->GetParent();
	while (true)
	{
		if (parent == nullptr)
			break;
		localToWorldMatrix = localToWorldMatrix * parent->GetTrans()->GetLocalToWorldMatrix();
		parent = parent->GetParent();
	}
}

Transform::Transform()
{
	pos = Vector2::zero;
	scale = Vector2(1, 1);

	scaleMatrix = Matrix3x3::identity;
	rotateMatrix = Matrix3x3::identity;
	translateMatrix = Matrix3x3::identity;
	localToWorldMatrix = Matrix3x3::identity;
}

void Transform::Init()
{
	SetRect();
	UpdateMatrix();

}

void Transform::Update()
{
	SetRect();
	UpdateMatrix();
}

void Transform::SetWorldPos(Vector2 pos)
{
	Object* parent = _object->GetParent();
	Vector2 worldPos = Vector2::zero;

	while (parent != nullptr)
	{
		worldPos += parent->GetTrans()->GetPos();
		parent = parent->GetParent();
	}
	this->pos = pos - worldPos;
}

void Transform::SetRect()
{
	_rc = RectMakeCenter(pos.x, pos.y, scale.x, scale.y);
	bottomPos = Vector2(pos.x, pos.y + scale.y / 2);
}

Vector2 Transform::GetWorldPosition()
{
	Object* parent = _object->GetParent();
	Vector2 position = this->pos;

	while (true)
	{
		if (parent == nullptr)
			return position;
		position += parent->GetTrans()->GetPos();
		parent = parent->GetParent();
	}
}
