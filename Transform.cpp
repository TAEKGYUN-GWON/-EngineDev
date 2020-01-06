#include "stdafx.h"
#include "Transform.h"

void Transform::Init()
{
	SetRect();
}

void Transform::Update()
{
	SetRect();
}

void Transform::SetRect()
{
	RectMakeCenter(pos.x, pos.y, scale.x, scale.y);
}
