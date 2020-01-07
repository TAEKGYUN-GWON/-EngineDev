#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "Sprite.h"


Object::Object()
{
	_trans = AddComponent<Transform>();
	_trans->SetPos(Vector2::zero);
	_trans->SetScale(Vector2(1,1));
	_sprite = AddComponent<Sprite>();
}

void Object::Update()
{
	if (!_isActive)return;
	for (int i = 0; i<_components.size();i++)
		_components[i]->Update();

}

void Object::Release()
{
	for (int i = _components.size()-1; i >= 0; i--)
	{
		_components[i]->Release();
	}
	delete this;
}

void Object::Render()
{
	_sprite->Render();
}

void Object::RemoveComponent(Component * component)
{
	for (auto iter = _components.begin(); iter != _components.end(); iter++)
	{
		if (component != *iter)
			continue;
		_components.erase(iter);
		delete(component);
		return;
	}
}
