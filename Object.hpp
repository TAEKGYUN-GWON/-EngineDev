#pragma once
#include "Object.h"
template<typename T>
T* Object::AddComponent()
{
    Component* component = new T();

    component->setGameObject(this);
    component->Init();
    if (dynamic_cast<DrawComponent*>(component))
        _draw.push_back((DrawComponent*)component);
    _components.push_back(component);

    return (T*)component;
}
template<typename T>
vector<T*> Object::GetComponents()
{
    vector<T*> componentsList;
    for (auto c : _components)
    {
        if (dynamic_cast<T*>(c))
            componentsList.push_back((T*)c);
    }
    return componentsList;
}


template<typename T>
inline T* Object::GetComponent()
{
    for (Component* c : _components)
    {
        if (dynamic_cast<T*>(c))
            return (T*)c;
    }
    return nullptr;
}

template<typename T>
T* Object::CreateObject(Object* parent)
{
    Object* Obj = new T();

    if (parent == nullptr)
        //Obj->SetParent(SCENEMANAGER->GetNowScene());
        Obj->SetParent(sceneManager::getSingleton()->GetNowScene());
    else
        Obj->SetParent(parent);

    return (T*)Obj;
}