#pragma once
#include"GraphicComponent.h"

template<typename T>
void ObjectPool::Init(int size, Object obj)
{
	ActivePool.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Object* newObj = new T;
		newObj->Init();
		newObj->SetTag(obj.GetTag());
		newObj->SetName(obj.GetName());
		newObj->GetGraphic()->SetImgName(obj.GetGraphic()->GetImgKey());
		newObj->SetIsActive(false);
		pool.push(newObj);

	}
}