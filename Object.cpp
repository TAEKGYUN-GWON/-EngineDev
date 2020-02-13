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

	for (Object* c : _removeList)
	{
	if (c->GetComponent<PhysicsBody>())
		{
			SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(c->GetComponent<PhysicsBody>()->GetBody());
		}
		c->Release();
	}
	_removeList.clear();

	for (int i = 0; i < _components.size(); i++)
		_components[i]->Update();

	for (Object* child : _activeList)
	{
		if (child->GetAllowInit()) child->Init();
		child->Update();
	}

}

void Object::Release()
{
	//cout << "������ѤѤѤ�" << endl;
	if (_parent != nullptr)
	{
		if (GetComponent<PhysicsBody>())
		{
			SetIsRelese();
			return;
		}
		if (_isActive)
			_parent->RemoveToActiveList(this);
		else
			_parent->RemoveToUnActiveList(this);

		_parent->RemoveChild(this);
	}

	auto _children = this->_children;

	for (Object* child : _children)
	{
		child->Release();
	}

	if(_components.size())
		for (int i = _components.size() - 1; i >= 0; i--)
		{
			_components[i]->Release();
		}
	delete this;
}



void Object::Render()
{
	if (_allowRender)
		for (auto d : _draw)
			d->Render();

	for (Object* child : _activeList)
	{
		child->Render();
	}

}

void Object::SetIsActive(bool active)
{
	_isActive = active;

	if (!_isActive)
	{
		_parent->RemoveToActiveList(this);
		_parent->_unActiveList.push_back(this);
	}
	else
	{
		_parent->RemoveToUnActiveList(this);
		_parent->_activeList.push_back(this);
	}
	if (GetComponent<PhysicsBody>())
	{
		GetComponent<PhysicsBody>()->SetBodyActive(_isActive);
	}
}



void Object::SetIsRelese()
{
	if (_isActive)
	{
		if (GetComponent<PhysicsBody>())
		{
			auto p = GetComponent<PhysicsBody>();
			p->SetBodyActive(false);

		}
		_parent->RemoveToActiveList(this);
		_parent->RemoveChild(this);
	}
	else
	{
		if (GetComponent<PhysicsBody>())
		{
			auto p = GetComponent<PhysicsBody>();
			p->SetBodyActive(false);
		}
		_parent->RemoveToUnActiveList(this);
		_parent->RemoveChild(this);
	}
		_parent->_removeList.push_back(this);

}

void Object::AddChild(Object* child)
{
	_children.push_back(child);

	if (child->GetIsActive())
	{
		_activeList.push_back(child);
		child->_parent->RemoveToActiveList(child);
	}
	else
	{
		_unActiveList.push_back(child);
		child->_parent->RemoveToUnActiveList(child);
	}

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

void Object::RemoveToActiveList(Object* child)
{
	for (int i = 0; i < _activeList.size(); i++)
	{
		if (_activeList[i] == child)
		{
			_activeList.erase(_activeList.begin() + i);
			break;
		}
	}

}

void Object::RemoveToUnActiveList(Object* child)
{
	for (int i = 0; i < _unActiveList.size(); i++)
	{
		if (_unActiveList[i] == child)
		{
			_unActiveList.erase(_unActiveList.begin() + i);
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
	vector<Object*>children;

	for (Object* child : _children)
	{
		if (child->GetTag() == tag) children.push_back(child);
	}

	return children;
}

void Object::SetParent(Object* parent)
{
	_parent = parent;

	parent->_children.push_back(this);

	if (_isActive)
		parent->_activeList.push_back(this);
	else
		parent->_unActiveList.push_back(this);
}

void Object::DelParent()
{
	if (_isActive)
		_parent->RemoveToActiveList(this);
	else
		_parent->RemoveToUnActiveList(this);

	_parent->RemoveChild(this);
	
	_parent = nullptr; 
}

