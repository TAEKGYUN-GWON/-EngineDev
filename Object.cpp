#include "stdafx.h"
#include "Object.h"

#include"Scene.h"

Object::Object()
{
	_trans = AddComponent<Transform>();
}

void Object::Init()
{
	for (Object* child : _children) child->Init();

	if (!_allowInit) return;

	for (Component* c : _components) c->Init();

	_allowInit = false;
}

void Object::Update()
{
	if (!_isActive) return;

	for (int i = 0; i < _components.size(); i++)
		_components[i]->Update();

	for (Object* child : _children)
	{
		if (child->GetAllowInit()) child->Init();
		child->Update();
	}

}

void Object::Release()
{
	if (_parent != nullptr)
		_parent->RemoveChild(this);
	for (Object* child : _children)
	{
		child->Release();
	}


	for (int i = _components.size() - 1; i >= 0; i--)
	{
		_components[i]->Release();
	}
	delete this;
}


void Object::Render()
{

	if (!_isActive) return;

	if (_allowRender)
		for (auto d : _draw)
			d->Render();

	for (Object* child : _children)
	{
		child->Render();
	}

}



void Object::AddChild(Object* child)
{
	_children.push_back(child);
	child->_parent->RemoveChild(child);
	child->_parent = this;
	if (_allowInit)
		child->Init();
}

void Object::RemoveComponent(Component* component)
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

void Object::RemoveChild(Object* child)
{
	for (int i = 0; i < _children.size(); i++)
	{
		if (_children[i] == child)
		{
			_children.erase(_children.begin() + i);
			break;
		}
	}

}

Object* Object::GetChildFromName(string name)
{
	for (Object* child : _children)
	{
		if (child->GetName() == name) return child;
	}


	return nullptr;
}

vector<Object*> Object::GetChildrenFromTag(string tag)
{
	vector<Object*>childs;
	for (Object* child : _children)
	{
		if (child->GetTag() == tag) childs.push_back(child);
	}

	return childs;
}

void Object::SetParent(Object* parent)
{
	_parent = parent;
	parent->_children.push_back(this);
}

