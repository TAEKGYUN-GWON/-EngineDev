#include "stdafx.h"
#include "Enemy1.h"
#include "Transform.h"

void Enemy1::Init(Vector2 pos)
{
	AddComponent<Sprite>();
	_trans->pos = pos;
	_trans->scale = Vector2(30, 30);
	GetComponent<Sprite>()->SetRectColor(ColorF::Green);
	GetComponent<Sprite>()->SetStrokeWidth(3.f);
}

void Enemy1::Update()
{
	if (path.size())
	{

	/*	if (path.begin()->x > _trans->pos.x)_trans->SetPos(_trans->pos + Vector2::right);
		else  _trans->SetPos(_trans->pos + Vector2::left);
		if (path.begin()->y > _trans->pos.y)_trans->SetPos(_trans->pos + Vector2::down);
		else _trans->SetPos(_trans->pos + Vector2::up);*/

		Vector2 a = *path.begin() -  _trans->pos;
		_trans->pos += a.Nomalized() * 70 * TIMEMANAGER->getElapsedTime();

		if ((int)Vector2::Distance(*path.begin(), _trans->pos) < (int)5)
			path.erase(path.begin());
	}


}

void Enemy1::SetPath(list<Vector2> path)
{
	this->path.clear();
	this->path = path; 
}
