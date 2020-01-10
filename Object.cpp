#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "Sprite.h"

#include"Scene.h"

Object::Object()
{
	_trans = AddComponent<Transform>();
	_trans->SetPos(Vector2::zero);
	_trans->SetScale(Vector2(1,1));
	_sprite = AddComponent<Sprite>();
}

void Object::Init()
{
	for (Object* child : _children) child->Init();

	if (!_allawInit) return;

	for (Component* c : _components) c->Init();

	_allawInit = false;
}

void Object::Update()
{
	if (!_isActive) return;

	for (int i = 0; i<_components.size();i++)
		_components[i]->Update();

	for (Object* child : _children)
	{
		if (child->GetAllawInit()) child->Init();
		child->Update();
	}

}

void Object::Release()
{
	if (_parent)
		_parent->RemoveChild(this);
	for (Object* child : _children)
	{
		child->Release();
	}
	for (int i = _components.size()-1; i >= 0; i--)
	{
		_components[i]->Release();
	}
	delete this;
}

bool Compare(Object* a, Object* b)
{

	Transform* aT = a->GetComponent<Transform>();
	Transform* bT = b->GetComponent<Transform>();

	if (!aT)
		return false;
	else if (!bT)
		return true;

	return aT->bottomPos.y < bT->bottomPos.y;
}

void Object::Render()
{
	if (_sprite == nullptr || !_isActive) return;

	_sprite->Render();

	sort(_children.begin(), _children.end(), Compare);

	for (Object* child : _children)
	{
		if (child->GetGraphic() == nullptr) continue;

		child->Render();
	}

}

Object* Object::CreateObject(Object* parent)
{
	Object* Obj = new Object();

	if (parent == nullptr)
		Obj->_parent = SCENEMANAGER->GetNowScene();
	else
		Obj->_parent = parent;
		
	return Obj;
}



void Object::AddChild(Object * child)
{
	_children.push_back(child);
	child->_parent->RemoveChild(child);
	child->_parent = this;
	if (_allawInit)
		child->Init();
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

void Object::RemoveChild(Object * child)
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

Object * Object::GetChildFromName(string name)
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

void Object::SetParent(Object * parent)
{
	this->_parent = parent;
	parent->_children.push_back(this);
}

